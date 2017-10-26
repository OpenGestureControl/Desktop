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
#include <QUrl>
#include <QDesktopServices>
#include <iostream>
#include "callbackhandler.h"

#include <stdio.h>
#include <tchar.h>
#include <psapi.h>

CallbackHandler::CallbackHandler(QObject *parent) : QObject(parent)
{
#ifdef Q_OS_WIN32
    this->lastProcess = GetForegroundWindow();
    //qWarning() << this->lastProcess;

    DWORD processID;
    GetWindowThreadProcessId(this->lastProcess, &processID);

    TCHAR szProcessName[MAX_PATH] = TEXT("<unknown>");

    HANDLE hProcess = OpenProcess( PROCESS_QUERY_INFORMATION |
                                       PROCESS_VM_READ,
                                       FALSE, processID );
    int bufsize = GetWindowTextLength(this->lastProcess) + 1;
    LPTSTR tTitle = new WCHAR[512];
    GetModuleBaseName(hProcess, NULL, szProcessName,
                      sizeof(szProcessName)/sizeof(TCHAR));
    this->exeTitle = QString::fromWCharArray(szProcessName);
    //std::cout << this->exeTitle << std::endl;

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

        } else if(optionName == "PrevSong") {

        } else if(optionName == "PlaySong") {

        } else if(optionName == "StopSong") {

        } else if(optionName == "VolumeUp") {

        } else if(optionName == "VolumeDown") {

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
QVariantMap CallbackHandler::getOptions() {

    this->itemMap.clear();
    if(this->exeTitle == "Spotify.exe") {
        this->itemMap.insert("NextSong", "Forward_500px.png");
        this->itemMap.insert("PrevSong", "Back_500px.png");
        this->itemMap.insert("PlaySong", "Play_500px.png");
        this->itemMap.insert("StopSong", "Stop_500px.png");
        this->itemMap.insert("VolumeUp", "VolumeUp_500px.png");
        this->itemMap.insert("VolumeDown", "VolumeDown_500px.png");
    } else {
        this->itemMap.insert("Open", "OSwindow_500px.png");
        this->itemMap.insert("Forward", "Forward_500px.png");
        this->itemMap.insert("Close", "Close_500px.png");
        this->itemMap.insert("Refresh", "Refresh_500px.png");
        this->itemMap.insert("Back", "Back_500px.png");
    }

    return this->itemMap;
}
