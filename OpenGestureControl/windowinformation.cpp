#include "windowinformation.h"

WindowInformation::WindowInformation(QObject *parent) : QObject(parent)
{

}

QString WindowInformation::GetWindowTitle()
{
    QString windowTitle;
    WindowInformation::GetWindowInformation();

#ifdef Q_OS_LINUX
    // Obtain the X11 display.
    XDisplay = XOpenDisplay(0);
    if(XDisplay == NULL) {
        qWarning() << "No X server connection established!" << endl;
    }

    // Retrieve window name //
    XClassHint classProp;
    XGetClassHint(XDisplay, (FocusWindow -1), &classProp); // -1 required because Linux is weird like that, -1 will cause error for Qt itself but w/e
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
    if(FocusWindow == NULL) {
        // TODO
    }

    FocusWindow = NULL;
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
    XDisplay = XOpenDisplay(0);
    if(XDisplay == NULL)
        qWarning() << "No X server connection established!" << endl;

    // Get the root window for the current display.
    //WinRoot = XDefaultRootWindow(XDisplay);

    // Find the window which has the current keyboard focus.
    int revert = 0;
    XGetInputFocus(XDisplay, &FocusWindow, &revert);

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
