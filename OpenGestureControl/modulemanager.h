#ifndef MODULEMANAGER_H
#define MODULEMANAGER_H

#include <QObject>
#include <QDebug>
#include <QtGlobal>

#undef Unsorted
#include <QDir>
#include <QDirIterator>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>

#include "windowinformation.h"


class ModuleManager : public QObject
{
    Q_OBJECT
public:
    explicit ModuleManager(QObject *parent = nullptr);
    QDir getModule();
    QString errorString() const;

private:
    QString eString;
    WindowInformation *windowInformation = new WindowInformation();

signals:

public slots:
};

#endif // MODULEMANAGER_H
