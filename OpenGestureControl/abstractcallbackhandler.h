#ifndef ABSTRACTCALLBACKHANDLER_H
#define ABSTRACTCALLBACKHANDLER_H

#include <QtGlobal>

#include <QDebug>
#include <QList>
#include <QObject>
#include <QString>
#include <QUrl>
#include <QDesktopServices>

#include <lua.hpp>

#include <functional>
#include <sstream>

#include "moduleoptionsmodel.h"
#include "moduleoption.h"

/*! \brief A class which handles callbacks from the piemenu.
 *
 *  This class is created to be attached to an options in the piemenu.
 *  When that option is selected this class is activated to execute the selected option.
 *  The action to perform for each option is retrieved from the Lua module.
 */

class AbstractCallbackHandler : public QObject
{
    Q_OBJECT
public:
    /*! \brief The constructor.
     *
     *  This constructor instantiates this class.
     *  When this constructor is called it requests the name of the current foreground application.
     *  It uses this name to define which Lua module to call (currently only browser and music module).
     */
    explicit AbstractCallbackHandler(QObject *parent = 0 /*!< [in] optional parameter, a QObject pointer to the parent of this class.*/);

    /*! \brief This function returns all options defined within the active Lua module.*/
    ModuleOptionsModel* getOptions();

    /*! \brief This function closes the Lua interpreter.*/
    void close();

    QString exeTitle;                   /*!< A QString reference to the name of the last application executable on the foreground. */
    ModuleOptionsModel *moduleOptions;  /*!< A ModuleOptionsModel pointer to the model containing all piemenu options. */
    lua_State *L;                       /*!< A lua_State pointer to the menu options pointers from the piemenu. */

private:
    /*! \brief This function allows the Lua module to send a key sequence to the OS.
     *
     *  The Lua module has to send a single key sequence as a string.
     *  This sequence should be formatted as follows: [modifier] + [keyname].
     *  Examples: "Ctrl+T" or "Ctrl+Shift+T" or "T".
     */
    static int ModuleHelperSendKeyboardKey(lua_State* L /*!< An lua_State pointer to the active Lua instance (the module, the interpreter etc). */);
    virtual void retrieveFocusWindowInfo() = 0;
    virtual void restoreFocusWindow() = 0;
    virtual void parseKey(QStringList hotkey) = 0;

public slots:
    /*! \brief This function handles a selected piemenu option.
     *
     *  This function is called when an option in the piemenu is selected.
     *  It retrieves the action to execute from the Lua module with the given option name.
     *  It retrieves the last application on the foreground, brings it to back to the foreground and executes the action on it.
     *  It return true when successful.
     */
    bool handle(QString optionName /*!< [in] parameter, a QString reference to the option to be executed.*/);
};

#endif // ABSTRACTCALLBACKHANDLER_H
