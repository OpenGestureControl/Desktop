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

#ifndef WINDOWSCALLBACKHANDLER_H
#define WINDOWSCALLBACKHANDLER_H

#include <QtGlobal>

#ifdef Q_OS_WIN32
#include "abstractcallbackhandler.h"

#include <windows.h>
#include <tchar.h>
#include <psapi.h>

class WindowsCallbackHandler : public AbstractCallbackHandler
{
    Q_OBJECT
public:

    explicit WindowsCallbackHandler(QObject *parent = 0);
    ModuleOptionsModel* getOptions();
    void close();

private:

    static int ModuleHelperSendKeyboardKey(lua_State* L /*!< An lua_State pointer to the active Lua instance (the module, the interpreter etc). */);

    /*! \brief This function translates a keyname to the Windows OS representation.*/
    static WORD lookupKey(QString keyname /*!< A QString reference to the keyname to be found. */);

    HWND lastProcess; /*!< A HWND (A Windows window handle) reference to the last foreground application. */

    void retrieveFocusWindowInfo() override;
    void restoreFocusWindow() override;
    static void parseKey(QStringList hotkey);

    /*! \brief This function allows the Lua module to send a key sequence to the OS.
     *
     *  The Lua module has to send a single key sequence as a string.
     *  This sequence should be formatted as follows: [modifier] + [keyname].
     *  Examples: "Ctrl+T" or "Ctrl+Shift+T" or "T".
     */
    static int ModuleHelperSendKeyboardKey(lua_State* L /*!< An lua_State pointer to the active Lua instance (the module, the interpreter etc). */);

public slots:
    /*! \brief This function handles a selected piemenu option.
     *
     *  This function is called when an option in the piemenu is selected.
     *  It retrieves the action to execute from the Lua module with the given option name.
     *  It retrieves the last application on the foreground, brings it to back to the foreground and executes the action on it.
     *  It return true when successful.
     */
    virtual bool handle(QString optionName /*!< [in] parameter, a QString reference to the option to be executed.*/);
}
#endif // Q_OS_WIN32

#endif // WINDOWSCALLBACKHANDLER_H
