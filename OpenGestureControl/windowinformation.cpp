#include "windowinformation.h"

WindowInformation::WindowInformation(QObject *parent) : QObject(parent)
{
    errorThrown = false;
}

#ifdef Q_OS_LINUX
// XLib fatal error catcher
int catcher( Display *disp, XErrorEvent *xe )
{
    qWarning() << "Error in X:" << xe->error_code;
    errorThrown = true;
    return 0;
}
#endif // Q_OS_LINUX

QString WindowInformation::GetWindowTitle()
{
    QString windowTitle;
    WindowInformation::GetWindowInformation();

#ifdef Q_OS_LINUX
    qWarning() << "Into errorhandler" << endl;
    // Set error handler
    XSetErrorHandler(catcher);

    // Obtain the X11 display.
    Display *XDisplay = XOpenDisplay(NULL);
    if(XDisplay == NULL) {
        qWarning() << "No X server connection established!" << endl;
    }

    // Retrieve window name //
    XClassHint classProp;
    XGetClassHint(XDisplay, FocusWindow, &classProp);
    windowTitle = classProp.res_class;

    XCloseDisplay(XDisplay); // Close link to X display server
#endif // Q_OS_LINUX
#ifdef Q_OS_WIN32

    TCHAR szProcessName[MAX_PATH] = TEXT("<unknown>");

    GetModuleBaseName(HProcess, NULL, szProcessName, sizeof(szProcessName)/sizeof(TCHAR));
    windowTitle = QString::fromWCharArray(szProcessName);
#endif // Q_OS_WIN32
    qWarning() << windowTitle << endl;
    return windowTitle;
}

void WindowInformation::RestoreWindow()
{
#ifdef Q_OS_LINUX
    if(FocusWindow == 0) {
        // TODO
    }

    FocusWindow = 0;
#endif // Q_OS_LINUX
#ifdef Q_OS_WIN32
    if(FocusWindow == NULL) {
        // if minimized
        if(IsIconic(FocusWindow)) {
            ShowWindow(FocusWindow, 9);
        } // else window is in background
        else {
            SetForegroundWindow(FocusWindow);
        }
    }
    FocusWindow = NULL;
#endif // Q_OS_WIN32
}

void WindowInformation::GetWindowInformation()
{
#ifdef Q_OS_LINUX
    // Obtain the X11 display.
    Display *XDisplay = XOpenDisplay(NULL);
    if(XDisplay == NULL)
        qWarning() << "No X server connection established!" << endl;

    // Find the window which has the current keyboard focus.
    // Based on xdotool under BSD-3: https://github.com/jordansissel/xdotool/blob/master/COPYRIGHT
    Atom request;
    Window root;

    request = XInternAtom(XDisplay, "_NET_ACTIVE_WINDOW", False);
    root = XDefaultRootWindow(XDisplay);

    Atom actual_type;
    int actual_format;
    unsigned long nitems;
    /*unsigned long nbytes;*/
    unsigned long bytes_after; /* unused */
    unsigned char *prop;
    int status;

    status = XGetWindowProperty(XDisplay, root, request, 0, (~0L),
                                False, AnyPropertyType, &actual_type,
                                &actual_format, &nitems, &bytes_after,
                                &prop);

    if (nitems > 0) {
      FocusWindow = *((Window*)prop);
    } else {
      FocusWindow = 0;
    }

    XCloseDisplay(XDisplay); // Close link to X display server
#endif // Q_OS_LINUX
#ifdef Q_OS_WIN32
    // Obtain the window which currnetly has focus
    FocusWindow = GetForegroundWindow();

    DWORD ProcessID;
    GetWindowThreadProcessId(FocusWindow, &ProcessID);
    HProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, processID);
#endif // Q_OS_WIN32
}
