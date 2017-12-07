#include "linuxcallbackhandler.h"
//#ifdef Q_OS_LINUX

LinuxCallbackHandler::LinuxCallbackHandler() : AbstractCallbackHandler()
{
    LinuxCallbackHandler::retrieveFocusWindowInfo();

    // TODO REDO this to be generic
    if (this->exeTitle == "Spotify.exe" || this->exeTitle == "Spotify") {
        filename = "music.lua";
    } else {
        filename = "browser.lua";
    }
}

XKeyEvent LinuxCallbackHandler::createKeyEvent(Display *display, Window &win, Window &winRoot, bool press, int keycode, int modifiers)
{
   XKeyEvent event;

   event.display     = display;     // Server connection
   event.window      = win;         // "event" window reported in
   event.root        = winRoot;     // Root window event occurred on
   event.subwindow   = None;        // Child window
   event.time        = CurrentTime; // Milliseconds
   event.x           = 1;           // Coordinates in event window
   event.y           = 1;           // Coordinates in event window
   event.x_root      = 1;           // Coordinates relative to root
   event.y_root      = 1;           // Coordinates relative to root
   event.same_screen = True;        // Same screen flag
   event.keycode     = XKeysymToKeycode(display, keycode); // Which key to send
   event.state       = modifiers;   // Key or button mask

   if(press)
      event.type = KeyPress;
   else
      event.type = KeyRelease;

   return event;
}


void LinuxCallbackHandler::parseKey(QStringList hotkey)
{
    if (hotkey.isEmpty())
        return;

    QString tempkey = hotkey[0];
    hotkey.pop_front();
    if (QString::compare(tempkey, "ctrl", Qt::CaseInsensitive) == 0) { // Check if the Control key needs to be pressed
        qWarning() << "Control pressed";
    }
    else if (QString::compare(tempkey, "alt", Qt::CaseInsensitive) == 0) { // Check if the Alt key needs to be pressed
        qWarning() << "Alt pressed";
    }
    else if (QString::compare(tempkey, "shift", Qt::CaseInsensitive) == 0) { // Check if the Shift key needs to be pressed
        qWarning() << "Shift pressed";
    }
    else {
        qWarning() << "Other key pressed: " << tempkey;

        // Send a key press event to the window.
        XKeyEvent event = WindowsCallbackHandler::createKeyEvent(this->display, this->lastProcess, winRoot, true, XK_T, 0);
        if((flags - 100) >= 0) {
            event.state += ControlMask;
            flags -= 100;
        }
        if((flags - 10) >= 0) {
            event.state += Mod1Mask;
            flags -= 10;
        }
        if((flags - 1) >= 0) {
            event.state += ShiftMask;
            flags -= 1;
        }
        XSendEvent(event.display, event.window, True, KeyPressMask, (XEvent *)&event);

        // Send a key release event to the window.
        //event = CallbackHandler::createKeyEvent(this->display, this->lastProcess, winRoot, false, XK_T, 0);
        //XSendEvent(event.display, event.window, True, KeyPressMask, (XEvent *)&event);
    }

    LinuxCallbackHandler::parseKey(hotkey);
}

void LinuxCallbackHandler::close()
{
    AbstractCallbackHandler::close();
    XCloseDisplay(this->display); // Close link to X display server
}

void LinuxCallbackHandler::retrieveFocusWindowInfo()
{
    // Obtain the X11 display.
    this->display = XOpenDisplay(0);
    if(this->display == NULL)
        qWarning() << "No X server connection established!";

    // Get the root window for the current display.
    this->winRoot = XDefaultRootWindow(this->display);
    qWarning() << "Winroot: " << winRoot;

    // Find the window which has the current keyboard focus.
    int    revert;
    XGetInputFocus(this->display, &this->lastProcess, &revert);
    qWarning() << "lastProcess: " << this->lastProcess;

    // Retrieve window name //
    XClassHint classProp;
    XGetClassHint(this->display, (this->lastProcess -1), &classProp); // -1 required because Linux is weird like that, -1 will cause error for Qt itself but w/e
    this->exeTitle = classProp.res_class;

    qWarning() << classProp.res_class << " : " << classProp.res_name << endl;
}

void LinuxCallbackHandler::restoreFocusWindow()
{
    // TODO
}

int WindowsCallbackHandler::lookupKeyLinux(QString keyname)
{
    QMap<QString, int> lookupMap;
    lookupMap["0"] = XK_0;
    lookupMap["1"] = XK_1;
    lookupMap["2"] = XK_2;
    lookupMap["3"] = XK_3;
    lookupMap["4"] = XK_4;
    lookupMap["5"] = XK_5;
    lookupMap["6"] = XK_6;
    lookupMap["7"] = XK_7;
    lookupMap["8"] = XK_8;
    lookupMap["9"] = XK_9;

    lookupMap["a"] = XK_a;
    lookupMap["b"] = XK_b;
    lookupMap["c"] = XK_c;
    lookupMap["d"] = XK_d;
    lookupMap["e"] = XK_e;
    lookupMap["f"] = XK_f;
    lookupMap["g"] = XK_g;
    lookupMap["h"] = XK_h;
    lookupMap["i"] = XK_i;
    lookupMap["j"] = XK_j;
    lookupMap["k"] = XK_k;
    lookupMap["l"] = XK_l;
    lookupMap["m"] = XK_m;
    lookupMap["n"] = XK_n;
    lookupMap["o"] = XK_o;
    lookupMap["p"] = XK_p;
    lookupMap["q"] = XK_q;
    lookupMap["r"] = XK_r;
    lookupMap["s"] = XK_s;
    lookupMap["t"] = XK_t;
    lookupMap["u"] = XK_u;
    lookupMap["v"] = XK_v;
    lookupMap["w"] = XK_w;
    lookupMap["x"] = XK_x;
    lookupMap["y"] = XK_y;
    lookupMap["z"] = XK_z;

    lookupMap["f1"] = XK_F1;
    lookupMap["f2"] = XK_F2;
    lookupMap["f3"] = XK_F3;
    lookupMap["f4"] = XK_F4;
    lookupMap["f5"] = XK_F5;
    lookupMap["f6"] = XK_F6;
    lookupMap["f7"] = XK_F7;
    lookupMap["f8"] = XK_F8;
    lookupMap["f9"] = XK_F9;
    lookupMap["f10"] = XK_F10;
    lookupMap["f11"] = XK_F11;
    lookupMap["f12"] = XK_F12;
    lookupMap["f13"] = XK_F13;
    lookupMap["f14"] = XK_F14;
    lookupMap["f15"] = XK_F15;
    lookupMap["f16"] = XK_F16;
    lookupMap["f17"] = XK_F17;
    lookupMap["f18"] = XK_F18;
    lookupMap["f19"] = XK_F19;
    lookupMap["f20"] = XK_F20;
    lookupMap["f21"] = XK_F21;
    lookupMap["f22"] = XK_F22;
    lookupMap["f23"] = XK_F23;
    lookupMap["f24"] = XK_F24;

    lookupMap["backspace"] = XK_BackSpace;

    lookupMap["enter"] = XK_Return;
    lookupMap["return"] = XK_Return;

    lookupMap["tab"] = XK_Tab;
    lookupMap["left"] = XK_Left;
    lookupMap["right"] = XK_Right;
    lookupMap["up"] = XK_Up;
    lookupMap["down"] = XK_Down;

    lookupMap["medianext"] = 0x1008ff17;
    lookupMap["mediaprev"] = 0x1008ff16;
    lookupMap["mediaplaypause"] = 0x1008ff14;
    lookupMap["mediastop"] = 0x1008ff15;
    lookupMap["volumeup"] = NULL;
    lookupMap["volumedown"] = NULL;
    lookupMap["volumemute"] = NULL;

    return lookupMap[keyname.toLower()];
}

#endif // Q_OS_LINUX
