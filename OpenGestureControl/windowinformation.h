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
    HANDLE HProcess; /*!< A HANDLE (A Windows process handle) reference to the last foreground process. */
#endif // Q_OS_WIN32

signals:

public slots:
};

#endif // WINDOWINFORMATION_H
