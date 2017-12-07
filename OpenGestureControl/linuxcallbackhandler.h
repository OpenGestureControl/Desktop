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

//#ifdef Q_OS_LINUX
#include "abstractcallbackhandler.h"

#include <X11/Xlib.h>
#include <X11/keysym.h>
#include <X11/Xutil.h>
#undef Bool // Needed because of weird Xlib C library

class LinuxCallbackHandler : public AbstractCallbackHandler
{
public:
    LinuxCallbackHandler();

private:
    /*! \brief This function creates an XKeyEvent.*/
    XKeyEvent createKeyEvent(Display *display, Window &win, Window &winRoot, bool press, int keycode, int modifiers);

    /*! \brief This function translates a keyname to the Linux OS representation.*/
    static int lookupKeyLinux(QString keyname /*!< A QString reference to the keyname to be found. */);

    void retrieveFocusWindowInfo() override;
    void restoreFocusWindow() override;
    void parseKey(QStringList hotkey) override;
    void close() override;

    Display *display;                   /*!< A Display (An Xlib X server handle) pointer to the Xlib X server. */
    Window winRoot;                     /*!< A Window (An Xlib window handle) reference to the root window of the application. */
    Window lastProcess;                 /*!< A Window (An Xlib window handle) reference to the last foreground application. */

};

#endif // Q_OS_LINUX
#endif // LINUXCALLBACKHANDLER_H
