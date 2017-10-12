#include "piemenu.h"

PieMenu::PieMenu(const QString appPath, QObject *parent) : QObject(parent)
{
    this->appPath = appPath;
}

void PieMenu::open()
{
    this->itemMap.insert("Back", "Back_222222_500px.png");
    this->itemMap.insert("Refresh", "Refresh_222222_500px.png");

    this->engine.rootContext()->setContextProperty("applicationPath", "file://" + this->appPath + "/");
    this->engine.rootContext()->setContextProperty("pieMenuItems", &itemMap);
    this->engine.load(QUrl(QStringLiteral("qrc:/pieMenu.qml")));
}
