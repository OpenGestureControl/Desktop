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
#include <QWindow>

PieMenu::PieMenu(QObject *parent) : QObject(parent)
{
    this->appPath = appPath;
    this->engine.rootContext()->setContextProperty("applicationPath", "file://" + this->appPath + "/");
    this->engine.load(QUrl(QStringLiteral("qrc:/pieMenu.qml")));
}

bool PieMenu::isOpen()
{
    return this->engine.rootObjects()[0]->property("visible").toBool();
}

void PieMenu::open()
{
    QVariantMap itemMap;
    itemMap.insert("Back", "Back_500px.png");
    itemMap.insert("Close", "Close_500px.png");
    itemMap.insert("Refresh", "Refresh_500px.png");

    this->engine.rootObjects()[0]->setProperty("visible", true);
    ((QWindow*) this->engine.rootObjects()[0])->requestActivate();
    QMetaObject::invokeMethod(this->engine.rootObjects()[0],
            "showMenu",
            Q_ARG(QVariant, QVariant::fromValue(itemMap)));
}

void PieMenu::close()
{
    this->engine.rootObjects()[0]->setProperty("visible", false);
}
