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

    connect(this->window, SIGNAL(closeRequest()), this, SLOT(close()));
    this->callbackHandler = NULL;
}

bool PieMenu::isOpen()
{
    return this->window->property("visible").toBool();
}

void PieMenu::open()
{
    if(this->callbackHandler) {
        delete this->callbackHandler;
    }
    /*
#ifdef Q_OS_WIN32
    this->callbackHandler = new WindowsCallbackHandler();
#endif // Q_OS_WIN32
#ifdef Q_OS_LINUX
    this->callbackHandler = new LinuxCallbackHandler();
#endif // Q_OS_LINUX
*/
    this->moduleManager = new ModuleManager(); // TODO - expand on this

    if (this->activeCallbackConnection) {
        disconnect(this->activeCallbackConnection);
    }
    this->activeCallbackConnection = connect(this->window, SIGNAL(optionSelected(QString)), callbackHandler, SLOT(handle(QString)));

    this->engine.rootContext()->setContextProperty("moduleOptions", this->callbackHandler->getOptions());

    this->window->setProperty("visible", true);
    ((QWindow*) this->window)->requestActivate();
}

void PieMenu::setActive(int degrees)
{
    QMetaObject::invokeMethod(this->window,
            "setActiveEntry",
            Q_ARG(QVariant, degrees));
}

void PieMenu::close()
{
    this->window->setProperty("visible", false);
    // This needs to be delayed until the handle function is done
    //callbackHandler->close();
}
