/*
   Copyright (c) 2017 ICT Group

   Permission is hereby granted, free of charge, to any person obtaining a copy
   of this software and associated documentation files (the "Software"), to deal
   in the Software without restriction, including without limitation the rights
   to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
   copies of the Software, and to permit persons to whom the Software is
   furnished to do so, subject to the following conditions:

   The above copyright notice and this permission notice shall be included in all
   copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
   AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
   OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
   SOFTWARE.
*/

#ifndef CALLBACKHANDLER_H
#define CALLBACKHANDLER_H

#include <QtGlobal>

#ifdef Q_OS_WIN32
#include <windows.h>
#include <tchar.h>
#include <psapi.h>
#endif

#include <QDebug>
#include <QDir>
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
 *
 *  Note: This class is currently only usable in Windows. It will compile in other OSes but will not work accordingly.
 */

class CallbackHandler : public QObject
{
    Q_OBJECT
public:
    /*! \brief The constructor.
     *
     *  This constructor instantiates this class.
     *  When this constructor is called it requests the name of the current foreground application.
     *  It uses this name to define which Lua module to call (currently only browser and music module).
     */
    explicit CallbackHandler(QObject *parent = 0 /*!< [in] optional parameter, a QObject pointer to the parent of this class.*/);
    /*! \brief This function returns all options defined within the active Lua module.*/
    ModuleOptionsModel* getOptions();
    /*! \brief This function closes the Lua interpreter.*/
    void close();

private:
    /*! \brief This function parses the string representation of the key and sends the keys to the windows OS.
     *
     *  This parse splits the keys on the '+' sign and sends each key to the lookupkey function.
     *  It remembers the order of modifiers and sends the keys in correct order to the Windows OS.
     */
    static void parseKey(QStringList hotkey);
    /*! \brief This function allows the Lua module to send a key sequence to the windows OS.
     *
     *  The Lua module has to send a single key sequence as a string.
     *  This sequence should be formatted as follows: [modifier] + [keyname].
     *  Examples: "Ctrl+T" or "Ctrl+Shift+T" or "T".
     */
    static int ModuleHelperSendKeyboardKey(lua_State* L /*!< An lua_State pointer to the active Lua instance (the module, the interpreter etc). */);
#ifdef Q_OS_WIN32
    /*! \brief This function translates a keyname to the Windows OS representation.*/
    static WORD lookupKey(QString keyname /*!< A QString reference to the keyname to be found. */);
#endif

    QString exeTitle; /*!< An QString reference to the name of the last application executable on the foreground. */
    ModuleOptionsModel *moduleOptions; /*!< An ModuleOptionsModel pointer to the model containing all piemenu options. */
    lua_State *L; /*!< An lua_State pointer to the menu options pointers from the piemenu. */
#ifdef Q_OS_WIN32
    HWND lastProcess; /*!< An HWND (A Windows window handle) reference to the last foreground application. */
#endif // Q_OS_WIN32
signals:

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

#endif // CALLBACKHANDLER_H
