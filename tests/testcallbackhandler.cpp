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

#include "testcallbackhandler.h"

void TestCallbackHandler::GetCorrectOptionsFromLua() {

    // Arrange
#ifdef Q_OS_LINUX
    LinuxCallbackHandler *handler = new LinuxCallbackHandler();
#endif
#ifdef Q_OS_WIN32
    WindowsCallbackHandler *handler = new WindowsCallbackHandler();
#endif

    ModuleOptionsListModel * result;
    ModuleOption *first, *second, *third, *fourth, *fifth;

    // Act
    result = handler->getOptions();
    first = result->get(0);
    second = result->get(1);
    third = result->get(2);
    fourth = result->get(3);
    fifth = result->get(4);

    // Assert
    QVERIFY(first->name() == QString("Open"));
    QVERIFY(second->name() == QString("Forward"));
    QVERIFY(third->name() == QString("Close"));
    QVERIFY(fourth->name() == QString("Refresh"));
    QVERIFY(fifth->name() == QString("Back"));
}

void TestCallbackHandler::HandleOptionChoiceCorrectly() {

    // Arrange
#ifdef Q_OS_LINUX
    LinuxCallbackHandler *handler = new LinuxCallbackHandler();
#endif
#ifdef Q_OS_WIN32
    WindowsCallbackHandler *handler = new WindowsCallbackHandler();
#endif
    bool result;

    // Act
    result = handler->handle(QString("Open"));

    // Assert
    QVERIFY(result == true);

}

void TestCallbackHandler::HandleOptionChoiceIncorrectly() {

    // Arrange
#ifdef Q_OS_LINUX
    LinuxCallbackHandler *handler = new LinuxCallbackHandler();
#endif
#ifdef Q_OS_WIN32
    WindowsCallbackHandler *handler = new WindowsCallbackHandler();
#endif
    bool result;

    // Act
    result = handler->handle(QString("incorrect"));

    // Assert
    QVERIFY(result == false);

}
