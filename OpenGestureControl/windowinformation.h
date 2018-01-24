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

/*! \brief A helper class which retrieves information about the currently active windows on both Linux and Windows.
 *
 *  This class retrieves the vital information required to retrieve modules and send keys to the different programs.
 */
class WindowInformation : public QObject
{
    Q_OBJECT
public:
    /*! \brief The constructor.
     *
     *  This constructor instantiates this class.
     */
    explicit WindowInformation(QObject *parent = nullptr /*!< [in] optional parameter, a QObject pointer to the parent of this class.*/);
    /*! \brief This function returns the name of the window or prcess currently running on the foreground.*/
    QString GetWindowTitle();
    /*! \brief This function restores a window to the foreground if it isn't there anymore.*/
    void RestoreWindow();

private:
    /*! \brief This function gets a required information about the currently running foreground process.*/
    void GetWindowInformation();

#ifdef Q_OS_LINUX
    Window FocusWindow; /*!< A Window (An Xlib window handle) reference to the last foreground application. */
    XClassHint *classProp = XAllocClassHint(); /*!< A place to store all the class properties. */
#endif // Q_OS_LINUX
#ifdef Q_OS_WIN32
    HWND FocusWindow; /*!< A HWND (A Windows window handle) reference to the last foreground application. */
    HANDLE HProcess; /*!< A HANDLE (A Windows process handle) reference to the last foreground process. */
#endif // Q_OS_WIN32

signals:

public slots:
};

#endif // WINDOWINFORMATION_H
