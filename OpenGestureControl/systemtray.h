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
    void show() const;

private:
    QSystemTrayIcon *tray;
    QMenu *trayMenu;

signals:
    void menuOpenClicked() const;

public slots:
    void showMessage(const QString message) const;

private slots:
    void menuActionClicked(const QAction* action) const;
};

#endif // SYSTEMTRAY_H
