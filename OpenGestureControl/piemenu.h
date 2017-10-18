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
    explicit PieMenu(QObject *parent = Q_NULLPTR);
    void open();
    void close();

    bool isOpen();

private:
    QString appPath;
    QQmlApplicationEngine engine;

signals:

public slots:
};

#endif // PIEMENU_H
