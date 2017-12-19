#ifndef SYSTEMTRAY_H
#define SYSTEMTRAY_H

#include <QObject>
#include <QApplication>
#include <QDebug>
#include <QSystemTrayIcon>
#include <QMenu>

class SystemTray : public QObject
{
    Q_OBJECT

public:
    explicit SystemTray(QObject *parent = 0);
    void show();

private:
    QSystemTrayIcon *tray;
    QMenu *trayMenu;

signals:
    void menuOpenClicked();

public slots:
    void showMessage(QString message);

private slots:
    void menuActionClicked(QAction* action);
};

#endif // SYSTEMTRAY_H
