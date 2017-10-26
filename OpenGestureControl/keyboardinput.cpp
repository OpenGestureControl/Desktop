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

#include "keyboardinput.h"

    PieMenu *pieMenuPtr = NULL;

#ifdef Q_OS_WIN32
    HHOOK hHook = NULL;

    void UpdateKeyState(BYTE *keystate, int keycode)
    {
        keystate[keycode] = GetKeyState(keycode);
    }

    LRESULT CALLBACK LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam)
    {
        //WPARAM is signal
        //LPARAM is signal information

        if (wParam == WM_KEYDOWN)
        {
            //Get the key information
            KBDLLHOOKSTRUCT cKey = *((KBDLLHOOKSTRUCT*)lParam);

            wchar_t buffer[5];

            //Get the keyboard state
            BYTE keyboard_state[256];
            GetKeyboardState(keyboard_state);
            UpdateKeyState(keyboard_state, VK_SHIFT);
            UpdateKeyState(keyboard_state, VK_CAPITAL);
            UpdateKeyState(keyboard_state, VK_CONTROL);
            UpdateKeyState(keyboard_state, VK_MENU);

            //Get keyboard layout
            HKL keyboard_layout = GetKeyboardLayout(0);

            //Get the name
            char lpszName[0X100] = {0};

            DWORD dwMsg = 1;
            dwMsg += cKey.scanCode << 16;
            dwMsg += cKey.flags << 24;

            int i = GetKeyNameText(dwMsg, (LPTSTR)lpszName, 255);

            //Try to convert the key information
            int result = ToUnicodeEx(cKey.vkCode, cKey.scanCode, keyboard_state, buffer, 4, 0, keyboard_layout);
            buffer[4] = L'\0';

            //std::cout << "Key: " << cKey.vkCode << " " << QString::fromUtf16((ushort*)buffer).toStdString() << " " << QString::fromUtf16((ushort*)lpszName).toStdString();
            std::cout << "Key Pressed!\n";
            if(cKey.vkCode == 160) {
                if(pieMenuPtr->isOpen()) {
                    pieMenuPtr->close();
                }
                else {
                    pieMenuPtr->open();
                }
            }
        }

        return CallNextHookEx(hHook, nCode, wParam, lParam);
    }
#endif // Q_OS_WIN32

KeyBoardInput::KeyBoardInput(PieMenu *menu)
{
    pieMenuPtr = menu;

#ifdef Q_OS_WIN32
    hHook = SetWindowsHookEx(WH_KEYBOARD_LL, LowLevelKeyboardProc, NULL, 0);

    if (hHook == NULL)
    {
        printf("Hook Failed\n");
    }
#endif // Q_OS_WIN32
}
