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
#include "callbackhandler.h"

#include <stdio.h>

CallbackHandler::CallbackHandler(QObject *parent) : QObject(parent)
{
    std::string filename = "browser.lua";

#ifdef Q_OS_WIN32
    this->lastProcess = GetForegroundWindow();
    //qWarning() << this->lastProcess;

    DWORD processID;
    GetWindowThreadProcessId(this->lastProcess, &processID);

    TCHAR szProcessName[MAX_PATH] = TEXT("<unknown>");

    HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, processID);

    GetModuleBaseName(hProcess, NULL, szProcessName, sizeof(szProcessName)/sizeof(TCHAR));
    this->exeTitle = QString::fromWCharArray(szProcessName);
    qWarning() << this->exeTitle;

    if (this->exeTitle == "Spotify.exe") {
        filename = "music.lua";
    }

#endif // Q_OS_WIN32

#ifdef Q_OS_UNIX
    // Obtain the X11 display.
       Display *display = XOpenDisplay(0);
       if(display == NULL)
          //return -1;

    // Get the root window for the current display.
       Window winRoot = XDefaultRootWindow(display);

    // Find the window which has the current keyboard focus.
       Window winFocus;
       int    revert;
       XGetInputFocus(display, &winFocus, &revert);

    // Send a fake key press event to the window.
       //XKeyEvent event = createKeyEvent(display, winFocus, winRoot, true, KEYCODE, 0);
       //XSendEvent(event.display, event.window, True, KeyPressMask, (XEvent *)&event);

    // Send a fake key release event to the window.
       //event = createKeyEvent(display, winFocus, winRoot, false, KEYCODE, 0);
       //XSendEvent(event.display, event.window, True, KeyPressMask, (XEvent *)&event);

#endif // Q_OS_UNIX

    this->moduleOptions = new ModuleOptionsModel();

    // Start initializing the Lua
    int status;
    L = luaL_newstate();
    luaL_openlibs(L);

    lua_register(L, "ModuleHelperSendKeyboardKey", ModuleHelperSendKeyboardKey);

    status = luaL_dofile(L, filename.c_str());
    if (status) {
        fprintf(stderr, "Couldn't load file: %s\n", lua_tostring(L, -1));
        exit(1);
    }
}

#ifdef Q_OS_WIN32
WORD CallbackHandler::lookupKey(QString keyname)
{
    QMap<QString, WORD> lookupMap;
    lookupMap["0"] = 0x30;
    lookupMap["1"] = 0x31;
    lookupMap["2"] = 0x32;
    lookupMap["3"] = 0x33;
    lookupMap["4"] = 0x34;
    lookupMap["5"] = 0x35;
    lookupMap["6"] = 0x36;
    lookupMap["7"] = 0x37;
    lookupMap["8"] = 0x38;
    lookupMap["9"] = 0x39;

    lookupMap["a"] = 0x41;
    lookupMap["b"] = 0x42;
    lookupMap["c"] = 0x43;
    lookupMap["d"] = 0x44;
    lookupMap["e"] = 0x45;
    lookupMap["f"] = 0x46;
    lookupMap["g"] = 0x47;
    lookupMap["h"] = 0x48;
    lookupMap["i"] = 0x49;
    lookupMap["j"] = 0x4a;
    lookupMap["k"] = 0x4b;
    lookupMap["l"] = 0x4c;
    lookupMap["m"] = 0x4d;
    lookupMap["n"] = 0x4e;
    lookupMap["o"] = 0x4f;
    lookupMap["p"] = 0x50;
    lookupMap["q"] = 0x51;
    lookupMap["r"] = 0x52;
    lookupMap["s"] = 0x53;
    lookupMap["t"] = 0x54;
    lookupMap["u"] = 0x55;
    lookupMap["v"] = 0x56;
    lookupMap["w"] = 0x57;
    lookupMap["x"] = 0x58;
    lookupMap["y"] = 0x59;
    lookupMap["z"] = 0x5a;

    lookupMap["f1"] = VK_F1;
    lookupMap["f2"] = VK_F2;
    lookupMap["f3"] = VK_F3;
    lookupMap["f4"] = VK_F4;
    lookupMap["f5"] = VK_F5;
    lookupMap["f6"] = VK_F6;
    lookupMap["f7"] = VK_F7;
    lookupMap["f8"] = VK_F8;
    lookupMap["f9"] = VK_F9;
    lookupMap["f10"] = VK_F10;
    lookupMap["f11"] = VK_F11;
    lookupMap["f12"] = VK_F12;
    lookupMap["f13"] = VK_F13;
    lookupMap["f14"] = VK_F14;
    lookupMap["f15"] = VK_F15;
    lookupMap["f16"] = VK_F16;
    lookupMap["f17"] = VK_F17;
    lookupMap["f18"] = VK_F18;
    lookupMap["f19"] = VK_F19;
    lookupMap["f20"] = VK_F20;
    lookupMap["f21"] = VK_F21;
    lookupMap["f22"] = VK_F22;
    lookupMap["f23"] = VK_F23;
    lookupMap["f24"] = VK_F24;

    lookupMap["backspace"] = VK_BACK;

    lookupMap["enter"] = VK_RETURN;
    lookupMap["return"] = VK_RETURN;

    lookupMap["tab"] = VK_TAB;
    lookupMap["left"] = VK_LEFT;
    lookupMap["right"] = VK_RIGHT;
    lookupMap["up"] = VK_UP;
    lookupMap["down"] = VK_DOWN;

    lookupMap["medianext"] = VK_MEDIA_NEXT_TRACK;
    lookupMap["mediaprev"] = VK_MEDIA_PREV_TRACK;
    lookupMap["mediaplaypause"] = VK_MEDIA_PLAY_PAUSE;
    lookupMap["mediastop"] = VK_MEDIA_STOP;
    lookupMap["volumeup"] = VK_VOLUME_UP;
    lookupMap["volumedown"] = VK_VOLUME_DOWN;
    lookupMap["volumemute"] = VK_VOLUME_MUTE;

    return lookupMap[keyname.toLower()];
}
#endif // Q_OS_WIN32

#ifdef Q_OS_UNIX
XKeyEvent createKeyEvent(Display *display, Window &win, Window &winRoot, bool press, int keycode, int modifiers)
{
   XKeyEvent event;

   event.display     = display;
   event.window      = win;
   event.root        = winRoot;
   event.subwindow   = None;
   event.time        = CurrentTime;
   event.x           = 1;
   event.y           = 1;
   event.x_root      = 1;
   event.y_root      = 1;
   event.same_screen = True;
   event.keycode     = XKeysymToKeycode(display, keycode);
   event.state       = modifiers;

   if(press)
      event.type = KeyPress;
   else
      event.type = KeyRelease;

   return event;
}
#endif //Q_OS_UNIX

void CallbackHandler::parseKey(QStringList hotkey)
{
    if (hotkey.isEmpty())
        return;

#ifndef Q_OS_WIN32
    qWarning() << "Sending a keyboard push event is not supported on this platform";
#endif // Q_OS_WIN32

    QString tempkey = hotkey[0];
    hotkey.pop_front();
    if (QString::compare(tempkey, "ctrl", Qt::CaseInsensitive) == 0) {
        qWarning() << "Control pressed";
#ifdef Q_OS_WIN32
        keybd_event(VK_LCONTROL, 0, 0, 0);
#endif // Q_OS_WIN32
        CallbackHandler::parseKey(hotkey);
        hotkey.pop_front();
#ifdef Q_OS_WIN32
        keybd_event(VK_LCONTROL, 0, KEYEVENTF_KEYUP, 0);
#endif // Q_OS_WIN32
    } else if (QString::compare(tempkey, "alt", Qt::CaseInsensitive) == 0) {
        qWarning() << "Alt pressed";
#ifdef Q_OS_WIN32
        keybd_event(VK_LMENU, 0, 0, 0);
#endif // Q_OS_WIN32
        CallbackHandler::parseKey(hotkey);
        hotkey.pop_front();
#ifdef Q_OS_WIN32
        keybd_event(VK_LMENU, 0, KEYEVENTF_KEYUP, 0);
#endif // Q_OS_WIN32
    } else if (QString::compare(tempkey, "shift", Qt::CaseInsensitive) == 0) {
        qWarning() << "Shift pressed";
#ifdef Q_OS_WIN32
        keybd_event(VK_LSHIFT, 0, 0, 0);
#endif // Q_OS_WIN32
        CallbackHandler::parseKey(hotkey);
        hotkey.pop_front();
#ifdef Q_OS_WIN32
        keybd_event(VK_LSHIFT, 0, KEYEVENTF_KEYUP, 0);
#endif // Q_OS_WIN32
    } else {
        qWarning() << "Other key pressed: " << tempkey;
#ifdef Q_OS_WIN32
        WORD key = CallbackHandler::lookupKey(tempkey);
        if (key != 0x00) {
            keybd_event(key, 0, 0, 0);
        } else {
            qWarning() << "Invalid key pressed";
        }
#endif // Q_OS_WIN32
    }

    CallbackHandler::parseKey(hotkey);
}

extern "C" int CallbackHandler::ModuleHelperSendKeyboardKey(lua_State* L)
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

  CallbackHandler::parseKey(stringList);

  return 0; // Count of returned values
}

bool CallbackHandler::handle(QString optionName)
{
    qWarning() << optionName;

    // This MUST be saved into a QByteArray first, or it'll crash
    // See https://wiki.qt.io/Technical_FAQ#How_can_I_convert_a_QString_to_char.2A_and_vice_versa.3F
    QByteArray optionNameByteArray = optionName.toLocal8Bit();
    const char *optionNameChar = optionNameByteArray.data();

    // Set return_options on stack to call
    lua_getglobal(L, "handle"); /* function to be called */
    lua_pushstring(L, optionNameChar);

#ifdef Q_OS_WIN32
    // if minimized
    if(IsIconic(this->lastProcess)) {
        ShowWindow(this->lastProcess, 9);
    } // else window is in background
    else {
        SetForegroundWindow(this->lastProcess);
    }
#endif // Q_OS_WIN32

    // Call return_options
    int result = lua_pcall(L, 1, 0, 0);
    if (result) {
        fprintf(stderr, "Failed to run script: %s\n", lua_tostring(L, -1));
        return false;
    }

    close();
    return true;
}

ModuleOptionsModel *CallbackHandler::getOptions()
{
    // Clear the list of items
    this->moduleOptions->clear();

    // Set return_options on stack to call
    lua_getglobal(L, "return_options"); /* function to be called */

    // Call return_options
    int result = lua_pcall(L, 0, 1, 0);
    if (result) {
        fprintf(stderr, "Failed to run script: %s\n", lua_tostring(L, -1));
        exit(1);
    }

    // Prepare table vars
    const char* luatypename;
    const char* key;
    const char* value;
    ModuleOption* moduleOption;

    // Get the resulting table of entries
    lua_pushvalue(L, -1);
    lua_pushnil(L);

    // For each entry in the table
    while (lua_next(L, -2)) {
        // Get the index
        luatypename = lua_typename(L, lua_type(L, -2));

        if (strcmp(luatypename, "number") == 0) {
            moduleOption = new ModuleOption();
            moduleOption->setIndex(lua_tonumber(L, -2));
        } else {
            qWarning() << "Index was not a valid type (expected number, got " << luatypename << ")";
        }

        if(lua_istable(L, -1)) {
            lua_pushnil(L);

            while (lua_next(L, -2)) {
                key = value = ""; // Reset key and value
                luatypename = lua_typename(L, lua_type(L, -2));
                if (strcmp(luatypename, "string") == 0) {
                    key = lua_tostring(L, -2);
                } else {
                    qWarning() << "Key was not a valid type (expected string, got " << luatypename << ")";
                }
                luatypename = lua_typename(L, lua_type(L, -1));
                if (strcmp(luatypename, "string") == 0) {
                    value = lua_tostring(L, -1);
                    if (strcmp(key, "name") == 0) {
                        moduleOption->setName(QString(value));
                    } else if (strcmp(key, "icon") == 0) {
                        moduleOption->setIcon(QString(value));
                    }
                } else {
                    qWarning() << "Value was not a valid type (expected string, got " << luatypename << ")";
                }

                lua_pop(L, 1);
            }
        }

        this->moduleOptions->addOption(moduleOption);

        lua_pop(L, 1);
    }

    lua_pop(L, 1);  /* Take the returned value out of the stack */

    return this->moduleOptions;
}

void CallbackHandler::close()
{
    lua_close(L);   /* Close Lua */
}
