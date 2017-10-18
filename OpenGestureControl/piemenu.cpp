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
