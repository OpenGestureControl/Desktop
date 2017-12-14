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

class WindowInformation : public QObject
{
    Q_OBJECT
public:
    static QString GetWindowTitle();
    static void RestoreWindow();

private:
    explicit WindowInformation(QObject *parent = nullptr);

    static void GetWindowInformation();

#ifdef Q_OS_LINUX
    static Display *XDisplay;  /*!< A Display (An Xlib X server handle) pointer to the Xlib X server. */
    //static Window WinRoot;     /*!< A Window (An Xlib window handle) reference to the root window of the application. */
    static Window FocusWindow; /*!< A Window (An Xlib window handle) reference to the last foreground application. */
#endif // Q_OS_LINUX
#ifdef Q_OS_WIN32
    static HWND FocusWindow; /*!< A HWND (A Windows window handle) reference to the last foreground application. */
    //static DWORD ProcessID;
    static HANDLE HProcess;
#endif // Q_OS_WIN32

signals:

public slots:
};

#endif // WINDOWINFORMATION_H
