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
            if(pieMenuPtr->isOpen) {
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
