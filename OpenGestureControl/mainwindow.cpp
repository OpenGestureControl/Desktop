#include "mainwindow.h"

MainWindow::MainWindow(QObject *parent) : QObject(parent)
{
    this->engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    this->engine.rootContext()->setContextProperty("moduleList", new ModuleListModel());
    this->window = this->engine.rootObjects()[0];
}

void MainWindow::open()
{
    this->window->setProperty("visible", true);
    ((QWindow*) this->window)->requestActivate();
}

void MainWindow::toggle()
{
    if (this->window->property("visible").toBool()) {
        this->window->setProperty("visible", false);
    } else {
        this->open();
    }
}
