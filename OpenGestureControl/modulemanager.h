#ifndef MODULEMANAGER_H
#define MODULEMANAGER_H

#include <QObject>
#include <QDebug>
#include <QtGlobal>

#undef Unsorted
#include <QDir>
#include <QDirIterator>

#include "windowinformation.h"


class ModuleManager : public QObject
{
    Q_OBJECT
public:
    explicit ModuleManager(QObject *parent = nullptr);
    bool checkForModule();

private:


signals:

public slots:
};

#endif // MODULEMANAGER_H
