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
#include <QDebug>

PieMenu::PieMenu(QObject *parent) : QObject(parent)
{
    this->engine.rootContext()->setContextProperty("moduleOptions", new ModuleOptionsListModel());
    this->engine.load(QUrl(QStringLiteral("qrc:/pieMenu.qml")));
    this->window = this->engine.rootObjects()[0];

    connect(this->window, SIGNAL(closeRequest()), this, SLOT(close()));
    this->callbackHandler = NULL;
}

bool PieMenu::isOpen() const
{
    return this->window->property("visible").toBool();
}

void PieMenu::open()
{
    if (isOpen())
        return;

    if(this->callbackHandler) {
        delete this->callbackHandler;
        this->callbackHandler = NULL;
    }

    if(this->moduleManager)
        delete this->moduleManager;
    this->moduleManager = new ModuleManager();
    QDir modulePath = this->moduleManager->getModule();
    if (!this->moduleManager->errorString().isEmpty()) {
        emit couldntOpenMenu(this->moduleManager->errorString());
        return;
    }

#ifdef Q_OS_WIN32
    this->callbackHandler = new WindowsCallbackHandler(modulePath);
#endif // Q_OS_WIN32
#ifdef Q_OS_LINUX
    this->callbackHandler = new LinuxCallbackHandler(modulePath);
#endif // Q_OS_LINUX

    this->moduleOptions = this->callbackHandler->getOptions();
    if (this->moduleOptions->rowCount() == 0) {
        QString noOptionsMessage = QObject::tr("Could not find any actions for the active window. This may be a bug in the active module.");
        emit couldntOpenMenu(noOptionsMessage);
        return;
    }

    this->engine.rootContext()->setContextProperty("moduleOptions", this->moduleOptions);

    this->window->setProperty("visible", true);
    ((QWindow*) this->window)->requestActivate();
}

void PieMenu::setActive(const int degrees) const
{
    if (!isOpen())
        return;

    qWarning() << degrees;
    QMetaObject::invokeMethod(this->window,
            "setActiveEntry",
            Q_ARG(QVariant, degrees));
}

void PieMenu::close() const
{
    int activeId = this->window->property("activeEntry").toInt();
    if (activeId != -1) {
        QString activeName = moduleOptions->get(activeId)->name();
        if (this->callbackHandler)
            this->callbackHandler->handle(activeName);
    }
    this->window->setProperty("visible", false);
}
