#ifndef CALLBACKHANDLER_H
#define CALLBACKHANDLER_H

#include <QDebug>
#include <QObject>
#include <QString>

class CallbackHandler : public QObject
{
    Q_OBJECT
public:
    explicit CallbackHandler(QObject *parent = 0);

signals:

public slots:
    void handle(QString optionName);
};

#endif // CALLBACKHANDLER_H
