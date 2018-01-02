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

#include <functional>
#include <QApplication>
#include <QDebug>
#include <QMenu>
#include <QObject>
#include <QTranslator>

#include "bluetoothmanager.h"
#include "piemenu.h"
#include "systemtray.h"

#ifdef Q_OS_WIN32
    #include "keyboardinput.h"
#endif

#include <QQmlApplicationEngine>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setQuitOnLastWindowClosed(false);

    QTranslator translator;
    translator.load(QLocale(), "", "i18n", ".qm");
    app.installTranslator(&translator);

    SystemTray *tray = new SystemTray();
    tray->show();

    PieMenu *pieMenu = new PieMenu();
    pieMenu->connect(pieMenu, SIGNAL(couldntOpenMenu(QString)), tray, SLOT(showMessage(QString)));
    tray->connect(tray, SIGNAL(menuOpenClicked()), pieMenu, SLOT(open()));

    BluetoothManager *bluetoothManager = new BluetoothManager();
    pieMenu->connect(bluetoothManager, SIGNAL(buttonPressed()), pieMenu, SLOT(open()));
    pieMenu->connect(bluetoothManager, SIGNAL(buttonReleased()), pieMenu, SLOT(close()));
    pieMenu->connect(bluetoothManager, SIGNAL(degreesMoved(int)), pieMenu, SLOT(setActive(int)));

#ifdef Q_OS_WIN32
    KeyBoardInput keyboardinput(&pieMenu);
#endif // Q_OS_WIN32

    return app.exec();
}
