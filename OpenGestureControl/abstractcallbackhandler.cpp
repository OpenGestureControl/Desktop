#include "abstractcallbackhandler.h"

AbstractCallbackHandler::AbstractCallbackHandler(QObject *parent) : QObject(parent)
{

}

ModuleOptionsListModel *AbstractCallbackHandler::getOptions()
{
    // Clear the list of items
    this->moduleOptions->clear();

    // Set return_options on stack to call
    lua_getglobal(L, "return_options"); /* function to be called */

    // Call return_options
    int result = lua_pcall(L, 0, 1, 0);
    if (result) {
        fprintf(stderr, "Failed to run script: %s\n", lua_tostring(L, -1));
        exit(1);
    }

    // Prepare table vars
    const char* luatypename;
    const char* key;
    const char* value;
    ModuleOption* moduleOption;

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
                        moduleOption->setIcon(QString(value));
                    }
                } else {
                    qWarning() << "Value was not a valid type (expected string, got " << luatypename << ")";
                }

                lua_pop(L, 1);
            }
        }

        this->moduleOptions->addOption(moduleOption);

        lua_pop(L, 1);
    }

    lua_pop(L, 1);  /* Take the returned value out of the stack */

    return this->moduleOptions;
}

void AbstractCallbackHandler::close()
{
    lua_close(L);           // Close Lua
}