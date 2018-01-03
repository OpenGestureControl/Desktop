#include "systemtray.h"

SystemTray::SystemTray(QObject *parent) : QObject(parent)
{
    this->tray = new QSystemTrayIcon(QIcon(":/icons/app.png"), qApp);

    this->trayMenu = new QMenu();
    trayMenu->addAction(tr("Open menu"));
    trayMenu->addAction(tr("&Quit"), qApp, &QApplication::quit);

    connect(this->trayMenu, SIGNAL(triggered(QAction*)), this, SLOT(menuActionClicked(QAction*)));

    this->tray->setContextMenu(this->trayMenu);
}

void SystemTray::show() const
{
    this->tray->show();
}

void SystemTray::showMessage(const QString message) const
{
    this->tray->showMessage(tr("OpenGestureControl"), message);
}

void SystemTray::menuActionClicked(const QAction *action) const
{
    if (action->text() == tr("Open menu")) {
        emit menuOpenClicked();
    }
}
