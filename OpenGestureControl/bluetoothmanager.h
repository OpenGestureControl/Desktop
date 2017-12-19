/*
   Copyright (c) 2017 ICT Group

   Permission is hereby granted, free of charge, to any person obtaining a copy
   of this software and associated documentation files (the "Software"), to deal
   in the Software without restriction, including without limitation the rights
   to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
   copies of the Software, and to permit persons to whom the Software is
   furnished to do so, subject to the following conditions:

   The above copyright notice and this permission notice shall be included in all
   copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
   AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
   OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
   SOFTWARE.
*/

#ifndef BLUETOOTHMANAGER_H
#define BLUETOOTHMANAGER_H

#include <QAbstractItemModel>
#include <QBluetoothDeviceDiscoveryAgent>
#include <QBluetoothServiceDiscoveryAgent>
#include <QLowEnergyController>
#include <QDataStream>
#include <QObject>
#include <QString>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "bluetoothdevicelistmodel.h"
#include "piemenu.h"

/*! \brief A class which manages all known Bluetooth devices.
 *
 *  Doesn't do much yet.
 */
//This class retains a list of previously connected Bluetooth devices for easy managing.
class BluetoothManager : public QObject
{
    Q_OBJECT

public:
    explicit BluetoothManager(QObject *parent = 0);
    void openUI();
    void closeUI();

    bool isUIOpen();

private:
    QBluetoothDeviceDiscoveryAgent *bluetoothDeviceDiscoveryAgent;
    QLowEnergyService *accelerometer, *button;
    QLowEnergyController *lowEnergyController;
    QObject *window;
    QQmlApplicationEngine engine;
    BluetoothDeviceListModel *bluetoothDevices;
    int connectionProgress;
    BluetoothDevice *connectingTo;

signals:
    void buttonPressed();
    void buttonReleased();

public slots:
    void scanForDevices();
    void connectToDevice(QString deviceAddress);
    void forgetDevice(QString deviceAddress);
    void connected();
    void disconnected();
    void error(QLowEnergyController::Error error);
    void deviceDiscovered(QBluetoothDeviceInfo deviceInfo);
    void scanFinished();
    void discoveryFinished();
    void accelerometerServiceStateChanged(QLowEnergyService::ServiceState state);
    void accelerometerDataChanged(QLowEnergyCharacteristic characteristic, QByteArray data);
    void buttonServiceStateChanged(QLowEnergyService::ServiceState state);
    void buttonDataChanged(QLowEnergyCharacteristic characteristic, QByteArray data);
};

#endif // BLUETOOTHMANAGER_H
