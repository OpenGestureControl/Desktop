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

#include "piemenu.h"

PieMenu::PieMenu(QObject *parent) : QObject(parent)
{
    this->appPath = appPath;
    this->engine.rootContext()->setContextProperty("applicationPath", "file://" + this->appPath + "/");
    this->engine.load(QUrl(QStringLiteral("qrc:/pieMenu.qml")));
    this->window = this->engine.rootObjects()[0];
    lastForegroundProcess = NULL;
}

bool PieMenu::isOpen()
{
    return this->window->property("visible").toBool();
}

void PieMenu::open(QVariantMap *itemMap, CallbackHandler *callbackHandler)
{
#ifdef Q_OS_WIN32
    lastForegroundProcess = GetForegroundWindow();
    std::cout << lastForegroundProcess << "\n";
#endif // Q_OS_WIN32

    if (this->activeCallbackConnection) {
        disconnect(this->activeCallbackConnection);
    }
    //this->activeCallbackConnection = connect(this->window, SIGNAL(optionSelected(QString)), this->window, SLOT(handle(QString)));
    this->activeCallbackConnection = connect(this->window, SIGNAL(optionSelected(QString)), callbackHandler, SLOT(handle(QString)));

    this->window->setProperty("visible", true);
    ((QWindow*) this->window)->requestActivate();
    QMetaObject::invokeMethod(window,
            "showMenu",
            Q_ARG(QVariant, QVariant::fromValue(*itemMap)));
}

void PieMenu::close()
{
    this->window->setProperty("visible", false);
    std::cout << GetForegroundWindow() << "\n";
    SetForegroundWindow(lastForegroundProcess); //0x205ec
}

void PieMenu::getWindowProcess()
{
#ifdef Q_OS_WIN32
    lastForegroundProcess = GetForegroundWindow();
#endif // Q_OS_WIN32
}
