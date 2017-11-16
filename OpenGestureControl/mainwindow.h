#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QObject>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QWindow>

#include "modulelistmodel.h"

class MainWindow : public QObject
{
    Q_OBJECT

public:
    explicit MainWindow(QObject *parent = 0);
    void open();
    void toggle();

private:
    QObject *window; /*!< A QObject pointer to a QML view object. */
    QString appPath; /*!< A QString reference path to the active Lua module. */
    QQmlApplicationEngine engine; /*!< A QQmlApplicationEngine reference to a QML creator engine. */

};

#endif // MAINWINDOW_H
