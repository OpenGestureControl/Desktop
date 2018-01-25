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

#include "appswitcher.h"

AppSwitcher::AppSwitcher(QObject *parent) : QObject(parent)
{
}

void AppSwitcher::open()
{
    Display *XDisplay = XOpenDisplay(NULL);
    if(XDisplay == NULL) {
        qWarning() << "No X server connection established!" << endl;
        return;
    }

    Atom a = XInternAtom(XDisplay, "_NET_CLIENT_LIST" , true);
    Atom actualType;
    int format;
    unsigned long bytesAfter;
    unsigned char *data =0;
    Window root = XDefaultRootWindow(XDisplay);
    int status = XGetWindowProperty(XDisplay,
                                root,
                                a,
                                0L,
                                (~0L),
                                false,
                                AnyPropertyType,
                                &actualType,
                                &format,
                                &numItems,
                                &bytesAfter,
                                &data);

    if (status >= Success && numItems)
    {
        // success - we have data: Format should always be 32:
        Q_ASSERT(format == 32);
        // cast to proper format, and iterate through values:
        windowList = (quint32*) data;
    }
}

void AppSwitcher::close() const
{
    QStringList stringList;
    stringList.append(QString("alt"));
#ifdef Q_OS_LINUX
    LinuxCallbackHandler().sendKey(stringList);
#endif // Q_OS_LINUX
}

void AppSwitcher::switchApp()
{
    if(currentwindow >= numItems) currentwindow = 0;
    qWarning() << "currposition" << currentwindow;

    Display *XDisplay = XOpenDisplay(NULL);
    if(XDisplay == NULL) {
        qWarning() << "No X server connection established!" << endl;
        return;
    }

    XRaiseWindow(XDisplay, (Window) windowList[currentwindow]);
    currentwindow++;
    //XSetInputFocus(XDisplay, FocusWindow, RevertToNone, CurrentTime);
    //XRaiseWindow(XDisplay, FocusWindow);
    //XFree(data);
}
