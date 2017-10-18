#include "keyboardinput.h"

#include <QTime>
#include <QChar>
#include <iostream>
#include <windows.h>
//#pragma comment(lib, "user32.lib")

HHOOK hHook = NULL;
PieMenu * pieMenuPtr = NULL;

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

KeyBoardInput::KeyBoardInput(PieMenu *menu)
{
    pieMenuPtr = menu;

    hHook = SetWindowsHookEx(WH_KEYBOARD_LL, LowLevelKeyboardProc, NULL, 0);

    if (hHook == NULL)
    {
        printf("Hook Failed\n");
    }
}
