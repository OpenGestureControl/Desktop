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

#ifndef LINUXCALLBACKHANDLER_H
#define LINUXCALLBACKHANDLER_H

#include <QtGlobal>

#ifdef Q_OS_LINUX
#include "abstractcallbackhandler.h"

#include <X11/Xlib.h>
#include <X11/keysym.h>
#include <X11/Xutil.h>
#undef Bool // Needed because of weird Xlib C library

static Display *XDisplay;  /*!< A Display (An Xlib X server handle) pointer to the Xlib X server. */
static Window WinRoot;     /*!< A Window (An Xlib window handle) reference to the root window of the application. */
static Window LastProcess; /*!< A Window (An Xlib window handle) reference to the last foreground application. */

class LinuxCallbackHandler : public AbstractCallbackHandler
{
    Q_OBJECT
public:
    explicit LinuxCallbackHandler(QObject *parent = 0);

private:
    /*! \brief This function translates a keyname to the Linux OS representation.*/
    static int lookupKey(QString keyname /*!< A QString reference to the keyname to be found. */);

    /*! \brief This function creates a fake keypressevent and send it.*/
    static void parseKey(QStringList hotkey);

    /*! \brief This function allows the Lua module to send a key sequence to the OS.
     *
     *  The Lua module has to send a single key sequence as a string.
     *  This sequence should be formatted as follows: [modifier] + [keyname].
     *  Examples: "Ctrl+T" or "Ctrl+Shift+T" or "T".
     */
    static int ModuleHelperSendKeyboardKey(lua_State* L /*!< An lua_State pointer to the active Lua instance (the module, the interpreter etc). */);

protected:
    void retrieveFocusWindowInfo() override;
    void restoreFocusWindow() override;
    void close() override;

public slots:
    /*! \brief This function handles a selected piemenu option.
     *
     *  This function is called when an option in the piemenu is selected.
     *  It retrieves the action to execute from the Lua module with the given option name.
     *  It retrieves the last application on the foreground, brings it to back to the foreground and executes the action on it.
     *  It return true when successful.
     */
    virtual bool handle(QString optionName /*!< [in] parameter, a QString reference to the option to be executed.*/);

};

#endif // Q_OS_LINUX
#endif // LINUXCALLBACKHANDLER_H
