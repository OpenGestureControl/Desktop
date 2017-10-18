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

#include <iostream>
#ifdef Q_OS_WIN32
    #include <windows.h>
    //#pragma comment(lib, "user32.lib")
#endif

PieMenu * pieMenuPtr = NULL;
#ifdef Q_OS_WIN32
    HHOOK hHook = NULL;

    LRESULT CALLBACK LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam)
    {
        //WPARAM is signal
        //LPARAM is signal information

        std::cout << "Key Pressed!\n";

        if (wParam == WM_KEYDOWN)
        {
            if(pieMenuPtr->isOpen()) {
                pieMenuPtr->close();
            }
            else {
                pieMenuPtr->open();
            }
        }

        return CallNextHookEx(hHook, nCode, wParam, lParam);
    }
#endif

KeyBoardInput::KeyBoardInput(PieMenu *menu)
{
    pieMenuPtr = menu;

#ifdef Q_OS_WIN32
    hHook = SetWindowsHookEx(WH_KEYBOARD_LL, LowLevelKeyboardProc, NULL, 0);

    if (hHook == NULL)
    {
        printf("Hook Failed\n");
    }
#endif
}
