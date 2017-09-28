#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include <QQmlContext>

#include <QQmlPropertyMap>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    QQmlPropertyMap itemMap;
    itemMap.insert("Back", "Back_222222_500px.png");
    itemMap.insert("Refresh", "Refresh_222222_500px.png");

    engine.rootContext()->setContextProperty("applicationPath", "file://" + qApp->applicationDirPath() + "/");
    engine.rootContext()->setContextProperty("pieMenuItems", &itemMap);
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
