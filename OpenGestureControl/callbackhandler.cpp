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

extern "C" {
    #include <stdio.h>
    #include <lua.h>
    #include <lualib.h>
    #include <lauxlib.h>
}

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
}

void CallbackHandler::handle(QString optionName)
{
    qWarning() << optionName;
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
    int status;
    int i;
    int result;
    double sum;
    lua_State *L;
    L = luaL_newstate();
    luaL_openlibs(L);

    status = luaL_loadfilex(L, "script.lua", NULL);
    if (status) {
        fprintf(stderr, "Couldn't load file: %s\n", lua_tostring(L, -1));
        exit(1);
    }

    lua_newtable(L);
    for (i = 1; i <= 5; i++) {
        lua_pushnumber(L, i);   /* Push the table index */
        lua_pushnumber(L, i*2); /* Push the cell value */
        lua_rawset(L, -3);      /* Stores the pair in the table */
    }
    lua_setglobal(L, "foo");

    /* Ask Lua to run our little script */
    result = lua_pcall(L, 0, LUA_MULTRET, 0);
    if (result) {
        fprintf(stderr, "Failed to run script: %s\n", lua_tostring(L, -1));
        exit(1);
    }

    sum = lua_tonumber(L, -1);

    printf("Script returned: %.0f\n", sum);

    lua_pop(L, 1);  /* Take the returned value out of the stack */
    lua_close(L);   /* Cya, Lua */

    this->itemMap.clear();
    if(this->exeTitle == "Spotify.exe") {
        this->itemMap.append("NextSong");
        this->itemMap.append("Forward_500px.png");

        this->itemMap.append("PrevSong");
        this->itemMap.append("Back_500px.png");

        this->itemMap.append("PlaySong");
        this->itemMap.append("Play_500px.png");

        this->itemMap.append("StopSong");
        this->itemMap.append("Stop_500px.png");

        this->itemMap.append("VolumeUp");
        this->itemMap.append("VolumeUp_500px.png");

        this->itemMap.append("VolumeDown");
        this->itemMap.append("VolumeDown_500px.png");
    } else {
        this->itemMap.append("Open");
        this->itemMap.append("OSwindow_500px.png");

        this->itemMap.append("Forward");
        this->itemMap.append("Forward_500px.png");

        this->itemMap.append("Close");
        this->itemMap.append("Close_500px.png");

        this->itemMap.append("Refresh");
        this->itemMap.append("Refresh_500px.png");

        this->itemMap.append("Back");
        this->itemMap.append("Back_500px.png");
    }

    return this->itemMap;
}
