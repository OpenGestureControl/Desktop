#include "abstractcallbackhandler.h"

AbstractCallbackHandler::AbstractCallbackHandler(QObject *parent) : QObject(parent)
{

}

bool AbstractCallbackHandler::init(const QDir modulePath)
{
    this->modulePath = modulePath;

    if (modulePath == QDir::currentPath()) {
        return false;
    }

    qWarning() << "Return lua values";
    int status = luaL_dofile(L, modulePath.filePath("main.lua").toStdString().c_str());
    if (status) {
        fprintf(stderr, "Couldn't load file: %s\n", lua_tostring(L, -1));
        return false;
    }

    this->initialized = true;
    return true;
}

ModuleOptionsListModel *AbstractCallbackHandler::getOptions() const
{
    ModuleOptionsListModel *moduleOptions = new ModuleOptionsListModel();

    if (!this->initialized)
        return moduleOptions;

    // Set return_options on stack to call
    lua_getglobal(L, "return_options"); /* function to be called */

    // Call return_options
    int result = lua_pcall(L, 0, 1, 0);
    if (result) {
        fprintf(stderr, "Failed to run script: %s\n", lua_tostring(L, -1));
        return moduleOptions;
    }

    // Prepare table vars
    const char* luatypename;
    const char* key;
    const char* value;
    ModuleOption* moduleOption;
    qWarning() << "iconDirpath" << this->modulePath;
    QDir iconDir = this->modulePath;
    iconDir.cd("icons");

    // Get the resulting table of entries
    lua_pushvalue(L, -1);
    lua_pushnil(L);

    // For each entry in the table
    while (lua_next(L, -2)) {
        // Get the index
        luatypename = lua_typename(L, lua_type(L, -2));

        if (strcmp(luatypename, "number") == 0) {
            moduleOption = new ModuleOption();
            moduleOption->setIndex(lua_tonumber(L, -2));
        } else {
            qWarning() << "Index was not a valid type (expected number, got " << luatypename << ")";
        }

        if(lua_istable(L, -1)) {
            lua_pushnil(L);

            while (lua_next(L, -2)) {
                key = value = ""; // Reset key and value
                luatypename = lua_typename(L, lua_type(L, -2));
                if (strcmp(luatypename, "string") == 0) {
                    key = lua_tostring(L, -2);
                } else {
                    qWarning() << "Key was not a valid type (expected string, got " << luatypename << ")";
                }
                luatypename = lua_typename(L, lua_type(L, -1));
                if (strcmp(luatypename, "string") == 0) {
                    value = lua_tostring(L, -1);
                    if (strcmp(key, "name") == 0) {
                        moduleOption->setName(QString(value));
                    } else if (strcmp(key, "icon") == 0) {
                        moduleOption->setIcon(iconDir.filePath(QString(value)));
                    }
                } else {
                    qWarning() << "Value was not a valid type (expected string, got " << luatypename << ")";
                }
                lua_pop(L, 1);
            }
        }
        moduleOptions->addOption(moduleOption);

        lua_pop(L, 1);
    }
    lua_pop(L, 1);  /* Take the returned value out of the stack */

    return moduleOptions;
}

void AbstractCallbackHandler::close() const
{
    lua_close(L);           // Close Lua
}
