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

#ifndef KEYBOARDINPUT_H
#define KEYBOARDINPUT_H

#include <iostream>

#ifdef Q_OS_WIN32
    #include <windows.h>
#endif // Q_OS_WIN32

#include "piemenu.h"

/*! \brief A class which handles keyboard input.
 *
 *  This class sets up a Low Level hook for Windows to catch a leftshift key from being pressed.
 *  After a leftshift keypress is detected the callback class is called and the piemenu pointer is asked to open the piemenu.
 *
 *  Note: This class is currently only usable in Windows. It will compile in other OSes but will not register keypresses.
 */

class KeyBoardInput
{
    public:
        /*! \brief The constructor.
         *
         *  It requires a pointer to the Piemenu in order to be able to open the piemenu from a keyboard call.
         *  The hook for keyboardinput is set up directly in this constructor.
         *  After a key is pressed it will call a callback function to determine if the pressed key is a left shift key.
         */
        explicit KeyBoardInput(PieMenu *menu /*!< [in] parameter, a QObject pointer to a piemenu class. */);
};

#endif // KEYBOARDINPUT_H
