#ifndef PIEMENU_H
#define PIEMENU_H

#include <QObject>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQmlPropertyMap>

class PieMenu : public QObject
{
    Q_OBJECT
public:
    explicit PieMenu(const QString appPath, QObject *parent = 0);
    void open();
    void close();

    bool isOpen;

private:
    QString appPath;
    QQmlApplicationEngine engine;
    QQmlPropertyMap itemMap;

signals:

public slots:
};

#endif // PIEMENU_H
