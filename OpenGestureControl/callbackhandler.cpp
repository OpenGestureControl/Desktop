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

#endif // Q_OS_WIN32
    // Start initializing the Lua
    int status;
    L = luaL_newstate();
    luaL_openlibs(L);

    lua_register(L, "ModuleHelperPushKeyboardKey", ModuleHelperPushKeyboardKey);
    lua_register(L, "ModuleHelperReleaseKeyboardKey", ModuleHelperReleaseKeyboardKey);

    status = luaL_dofile(L, "browser.lua");
    if (status) {
        fprintf(stderr, "Couldn't load file: %s\n", lua_tostring(L, -1));
        exit(1);
    }
}

extern "C" int CallbackHandler::ModuleHelperPushKeyboardKey(lua_State* L)
{
  const char *hotkey = lua_tostring(L, 1); // First argument
#ifdef Q_OS_WIN32
  keybd_event(hotkey, 0, 0, 0);
#else
  qWarning() << "Sending a keyboard push event is not supported on this platform";
#endif // Q_OS_WIN32

  return 0; // Count of returned values
}

extern "C" int CallbackHandler::ModuleHelperReleaseKeyboardKey(lua_State* L)
{
  const char *hotkey = lua_tostring(L, 1); // First argument
#ifdef Q_OS_WIN32
  keybd_event(hotkey, 0, KEYEVENTF_KEYUP, 0);
#else
  qWarning() << "Sending a keyboard release event is not supported on this platform";
#endif // Q_OS_WIN32

  return 0; // Count of returned values
}

void CallbackHandler::handle(QString optionName)
{
    qWarning() << optionName;

    // This MUST be saved into a QByteArray first, or it'll crash
    // See https://wiki.qt.io/Technical_FAQ#How_can_I_convert_a_QString_to_char.2A_and_vice_versa.3F
    QByteArray optionNameByteArray = optionName.toLocal8Bit();
    const char *optionNameChar = optionNameByteArray.data();

    // Set return_options on stack to call
    lua_getglobal(L, "handle"); /* function to be called */
    lua_pushstring(L, optionNameChar);

    // Call return_options
    int result = lua_pcall(L, 1, 0, 0);
    if (result) {
        fprintf(stderr, "Failed to run script: %s\n", lua_tostring(L, -1));
        exit(1);
    }

    close();

#ifdef Q_OS_WIN32
    // if minimized
    if(IsIconic(this->lastProcess)) {
        ShowWindow(this->lastProcess, 9);
    } // else window is in background
    else {
        SetForegroundWindow(this->lastProcess);
    }

    if(this->exeTitle == "Spotify.exe") {
        if(optionName == "NextSong") {
            keybd_event(VK_MEDIA_NEXT_TRACK, 0, 0, 0);
        } else if(optionName == "PrevSong") {
            keybd_event(VK_MEDIA_PREV_TRACK, 0, 0, 0);
        } else if(optionName == "PlaySong") {
            keybd_event(VK_MEDIA_PLAY_PAUSE, 0, 0, 0);
        } else if(optionName == "StopSong") {
            keybd_event(VK_MEDIA_STOP, 0, 0, 0);
        } else if(optionName == "VolumeUp") {
            keybd_event(VK_VOLUME_UP, 0, 0, 0);
        } else if(optionName == "VolumeDown") {
            keybd_event(VK_VOLUME_DOWN, 0, 0, 0);
        }
    } else {
        if(optionName == "Back") {
            keybd_event(VK_BROWSER_BACK, 0, 0, 0);
        }
        else if (optionName == "Forward") {
            keybd_event(VK_BROWSER_FORWARD, 0, 0, 0);
        }
        else if (optionName == "Open") {
            // Simulate a key press
            keybd_event( VK_LCONTROL, 0, 0, 0);
            keybd_event( 0x54, 0, 0, 0);
            // Simulate a key release
            keybd_event( 0x54, 0, KEYEVENTF_KEYUP, 0);
            keybd_event( VK_LCONTROL, 0, KEYEVENTF_KEYUP, 0);
        }
        else if (optionName == "Close") {
            // Simulate a key press
            keybd_event( VK_LCONTROL, 0, 0, 0);
            keybd_event( 0x57, 0, 0, 0);
            // Simulate a key release
            keybd_event( 0x57, 0, KEYEVENTF_KEYUP, 0);
            keybd_event( VK_LCONTROL, 0, KEYEVENTF_KEYUP, 0);
        }
        else if (optionName == "Refresh") {
            keybd_event(VK_BROWSER_REFRESH, 0, 0, 0);
        }
    }
#endif // Q_OS_WIN32
}

QList<QString> CallbackHandler::getOptions()
{
    // Clear the list of items
    this->itemMap.clear();

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
    double index;
    const char* key;
    const char* value;

    // Get the resulting table of entries
    lua_pushvalue(L, -1);
    lua_pushnil(L);

    // For each entry in the table
    while (lua_next(L, -2)) {
        // Get the index
        luatypename = lua_typename(L, lua_type(L, -2));

        if (strcmp(luatypename, "number") == 0) {
            index = lua_tonumber(L, -2);
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
                } else {
                    qWarning() << "Value was not a valid type (expected string, got " << luatypename << ")";
                }

                qWarning() << "[" << index << "] " << key << " => " << value;

                if (key && value) {
//                    this->itemMap.append(key);
                    this->itemMap.append(value);
                }

                lua_pop(L, 1);
            }
        }

        lua_pop(L, 1);
    }

    lua_pop(L, 1);  /* Take the returned value out of the stack */

//    if(this->exeTitle == "Spotify.exe") {
//        this->itemMap.append("NextSong");
//        this->itemMap.append("Forward_500px.png");
//
//        this->itemMap.append("PrevSong");
//        this->itemMap.append("Back_500px.png");
//
//        this->itemMap.append("PlaySong");
//        this->itemMap.append("Play_500px.png");
//
//        this->itemMap.append("StopSong");
//        this->itemMap.append("Stop_500px.png");
//
//        this->itemMap.append("VolumeUp");
//        this->itemMap.append("VolumeUp_500px.png");
//
//        this->itemMap.append("VolumeDown");
//        this->itemMap.append("VolumeDown_500px.png");
//    } else {
//        this->itemMap.append("Open");
//        this->itemMap.append("OSwindow_500px.png");
//
//        this->itemMap.append("Forward");
//        this->itemMap.append("Forward_500px.png");
//
//        this->itemMap.append("Close");
//        this->itemMap.append("Close_500px.png");
//
//        this->itemMap.append("Refresh");
//        this->itemMap.append("Refresh_500px.png");
//
//        this->itemMap.append("Back");
//        this->itemMap.append("Back_500px.png");
//    }

    return this->itemMap;
}

void CallbackHandler::close() {
    lua_close(L);   /* Close Lua */
}
