#include "piemenu.h"

PieMenu::PieMenu(const QString appPath, QObject *parent) : QObject(parent)
{
    this->appPath = appPath;
    this->isOpen = false;
}

void PieMenu::open()
{
    this->itemMap.insert("Back", "Back_500px.png");
    this->itemMap.insert("Close", "Close_500px.png");
    this->itemMap.insert("Refresh", "Refresh_500px.png");

    this->engine.rootContext()->setContextProperty("applicationPath", "file://" + this->appPath + "/");
    this->engine.rootContext()->setContextProperty("pieMenuItems", &itemMap);
    this->isOpen = true;
    this->engine.load(QUrl(QStringLiteral("qrc:/pieMenu.qml")));
}

void PieMenu::close()
{
    this->isOpen = false;
    this->engine.quit();
}
