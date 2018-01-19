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

#ifndef WINDOWINFORMATION_H
#define WINDOWINFORMATION_H

#include <QObject>
#include <QDebug>
#include <QtGlobal>

#ifdef Q_OS_LINUX
#include <X11/Xlib.h>
#include <X11/keysym.h>
#include <X11/Xutil.h>
#undef Bool // Needed because of weird Xlib C library
#endif // Q_OS_LINUX

#ifdef Q_OS_WIN32
#include <windows.h>
#include <tchar.h>
#include <psapi.h>
#endif // Q_OS_WIN32

static bool errorThrown;

class WindowInformation : public QObject
{
    Q_OBJECT
public:
    explicit WindowInformation(QObject *parent = nullptr);
    QString GetWindowTitle();
    void RestoreWindow();

private:
    void GetWindowInformation();

#ifdef Q_OS_LINUX
    Window FocusWindow; /*!< A Window (An Xlib window handle) reference to the last foreground application. */
#endif // Q_OS_LINUX
#ifdef Q_OS_WIN32
    HWND FocusWindow; /*!< A HWND (A Windows window handle) reference to the last foreground application. */
    HANDLE HProcess;
#endif // Q_OS_WIN32

signals:

public slots:
};

#endif // WINDOWINFORMATION_H
