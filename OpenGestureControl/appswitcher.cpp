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
    XDisplay = XOpenDisplay(NULL);
    if(XDisplay == NULL) {
        qWarning() << "No X server connection established!" << endl;
        return;
    }
}

void AppSwitcher::open()
{
    // TODO: Filter out bad Windows? We seem to get X errors later
    Atom a = XInternAtom(XDisplay, "_NET_CLIENT_LIST_STACKING" , true);
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
        windowList = (long*) data;
    }

    currentwindow = numItems - 1;

    connect(switchTimer, SIGNAL(timeout()), this, SLOT(switchApp()));
    switchTimer->start(500);
}

void AppSwitcher::close() const
{
    switchTimer->stop();
}

void AppSwitcher::switchApp()
{
    // TODO: Make sure it works everywhere
    // On KDE: Set focus stealing prevention to None
    // On other desktops: simply doesn't work
    if (currentwindow == 0) {
        currentwindow = numItems - 1;
    } else {
        currentwindow--;
    }
    qWarning() << "currposition" << currentwindow;
    Window newWindow = (Window) windowList[currentwindow];

    XSetInputFocus(XDisplay, newWindow, RevertToParent, CurrentTime);
    XFlush(XDisplay);
    XRaiseWindow(XDisplay, newWindow);
    XFlush(XDisplay);
    //XFree(data);
}
