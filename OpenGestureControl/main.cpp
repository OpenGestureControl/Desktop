#include <functional>

#include <QApplication>
#include <QMenu>
#include <QObject>
#include <QSystemTrayIcon>
#include <QTranslator>

#include "piemenu.h"
#ifdef Q_OS_WIN32
    #include "keyboardinput.h"
#endif

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setQuitOnLastWindowClosed(false);

    QTranslator translator;
    translator.load(QLocale(), "", "i18n", ".qm");
    app.installTranslator(&translator);

    PieMenu pieMenu(qApp->applicationDirPath());

    QSystemTrayIcon tray(QIcon(qApp->applicationDirPath() + "/icons/app.png"), &app);

    QMenu trayMenu;
    trayMenu.addAction(QObject::tr("Open menu"), std::bind(&PieMenu::open, &pieMenu));
    trayMenu.addAction(QObject::tr("&Quit"), qApp, &QApplication::quit);

    tray.setContextMenu(&trayMenu);
    tray.show();

#ifdef Q_OS_WIN32
    KeyBoardInput keyboardinput(&pieMenu);
#endif

    return app.exec();
}
