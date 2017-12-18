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
#include "linuxcallbackhandler.h"

#ifdef Q_OS_LINUX
LinuxCallbackHandler::LinuxCallbackHandler(QDir modulePath, QObject *parent) : AbstractCallbackHandler(parent)
{
    LinuxCallbackHandler::retrieveFocusWindowInfo();

    // Start initializing the Lua
    this->L = luaL_newstate();
    luaL_openlibs(L);

    lua_register(L, "ModuleHelperSendKeyboardKey", ModuleHelperSendKeyboardKey);

    if (!init(modulePath)) {
        LinuxCallbackHandler::close();
    }
}

extern "C" int LinuxCallbackHandler::ModuleHelperSendKeyboardKey(lua_State* L)
{
  const char *hotkey = lua_tostring(L, 1); // First argument
  std::string hotkeystring(hotkey);

  std::replace(hotkeystring.begin(), hotkeystring.end(), '+', ' ');
  std::string temp;
  std::stringstream ss(hotkeystring);

  QStringList stringList;

  while (ss >> temp) {
      stringList.append(QString(temp.c_str()));
  }

  LinuxCallbackHandler::parseKey(stringList);

  return 0; // Count of returned values
}

void LinuxCallbackHandler::parseKey(QStringList hotkey)
{
    XKeyEvent event;

    event.display     = XDisplay;    // Server connection
    event.window      = LastProcess; // "event" window reported in
    event.root        = WinRoot;     // Root window event occurred on
    event.subwindow   = None;        // Child window
    event.time        = CurrentTime; // Milliseconds
    event.x           = 1;           // Coordinates in event window
    event.y           = 1;           // Coordinates in event window
    event.x_root      = 1;           // Coordinates relative to root
    event.y_root      = 1;           // Coordinates relative to root
    event.same_screen = True;        // Same screen flag
    event.keycode     = 0;           // Which key to send
    event.state       = 0;           // Key or button mask
    event.type        = KeyPress;    // Key press of release
    event.state       = 0;           // Modifier keys

    for(int i = 0; i < hotkey.size(); i++) {
        if (QString::compare(hotkey[i], "ctrl", Qt::CaseInsensitive) == 0) { // Check if the Control key needs to be pressed
            qWarning() << "Control pressed";
            event.state += ControlMask;
        }
        else if (QString::compare(hotkey[i], "alt", Qt::CaseInsensitive) == 0) { // Check if the Alt key needs to be pressed
            qWarning() << "Alt pressed";
            event.state += Mod1Mask;
        }
        else if (QString::compare(hotkey[i], "shift", Qt::CaseInsensitive) == 0) { // Check if the Shift key needs to be pressed
            qWarning() << "Shift pressed";
            event.state += ShiftMask;
        }
        else {
            qWarning() << "Other key pressed: " << hotkey[i];
            event.keycode = XKeysymToKeycode(XDisplay, lookupKey(hotkey[i]));

            // Send a key press event to the window.
            XSendEvent(event.display, event.window, True, KeyPressMask, (XEvent *)&event);

            // Send a key release event to the window.
            //event = CallbackHandler::createKeyEvent(this->display, this->lastProcess, winRoot, false, XK_T, 0);
            //XSendEvent(event.display, event.window, True, KeyPressMask, (XEvent *)&event);
        }
    }
}

bool LinuxCallbackHandler::handle(QString optionName)
{
    qWarning() << optionName;

    // This MUST be saved into a QByteArray first, or it'll crash
    // See https://wiki.qt.io/Technical_FAQ#How_can_I_convert_a_QString_to_char.2A_and_vice_versa.3F
    QByteArray optionNameByteArray = optionName.toLocal8Bit();
    const char *optionNameChar = optionNameByteArray.data();

    // Set return_options on stack to call
    lua_getglobal(L, "handle"); /* function to be called */
    lua_pushstring(L, optionNameChar);

    LinuxCallbackHandler::restoreFocusWindow();

    // Call return_options
    int result = lua_pcall(L, 1, 0, 0);
    if (result) {
        fprintf(stderr, "Failed to run script: %s\n", lua_tostring(L, -1));
        return false;
    }

    // TODO change this
    LinuxCallbackHandler::close();
    return true;
}

void LinuxCallbackHandler::retrieveFocusWindowInfo()
{
    // Obtain the X11 display.
    XDisplay = XOpenDisplay(0);
    if(XDisplay == NULL)
        qWarning() << "No X server connection established!";

    // Get the root window for the current display.
    WinRoot = XDefaultRootWindow(XDisplay);
    qWarning() << "Winroot: " << WinRoot;

    // Find the window which has the current keyboard focus.
    int revert = 0;
    XGetInputFocus(XDisplay, &LastProcess, &revert);
    qWarning() << "lastProcess: " << LastProcess;

    // Retrieve window name //
    XClassHint classProp;
    XGetClassHint(XDisplay, (LastProcess -1), &classProp); // -1 required because Linux is weird like that, -1 will cause error for Qt itself but w/e
    this->exeTitle = classProp.res_class;

    qWarning() << classProp.res_class << " : " << classProp.res_name << endl;
}

void LinuxCallbackHandler::restoreFocusWindow()
{
    //XRaiseWindow(XDisplay, LastProcess); // currently does not work
    int revert = 0;
    XSetInputFocus(XDisplay, LastProcess, revert, CurrentTime);
}

void LinuxCallbackHandler::close()
{
    AbstractCallbackHandler::close();
    XCloseDisplay(XDisplay); // Close link to X display server
}

int LinuxCallbackHandler::lookupKey(QString keyname)
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
    lookupMap["space"] = XK_space;

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
    lookupMap["volumeup"] = 0x1008ff13;
    lookupMap["volumedown"] = 0x1008ff11;
    lookupMap["volumemute"] = 0x1008ff12;

    return lookupMap[keyname.toLower()];
}

#endif // Q_OS_LINUX
