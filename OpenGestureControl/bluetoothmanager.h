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
#include <QtMath>
#include <QObject>
#include <QString>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QDebug>

#include "bluetoothdevicelistmodel.h"
#include "piemenu.h"

/*! \brief A class which manages all known Bluetooth devices.
 *
 *  This class retains a list of previously connected Bluetooth devices for easy managing.
 */

class BluetoothManager : public QObject
{
    Q_OBJECT

public:
    explicit BluetoothManager(QObject *parent = 0);
    void openUI() const;
    void closeUI() const;

    bool isUIOpen() const;
    short shortFromLittleEndianBytes(const char bytes[]) const;
    void lowPass(const float input[], float output[]) const;

private:
    QBluetoothDeviceDiscoveryAgent *bluetoothDeviceDiscoveryAgent;
    QQmlApplicationEngine engine;
    QLowEnergyService *accelerometer, *button;
    BluetoothDeviceListModel *bluetoothDevices;
    BluetoothDevice *connectingTo;
    QLowEnergyController *lowEnergyController;
    QObject *window;
    int connectionProgress;

    float accelInput[3];
    float accelOutput[3];
    const float ALPHA = 0.15f;

signals:
    void buttonPressed() const;
    void buttonReleased() const;
    void degreesMoved(const int degrees) const;

public slots:
    void scanForDevices();
    void connectToDevice(const QString deviceAddress);
    void forgetDevice(const QString deviceAddress);
    void connected() const;
    void disconnected();
    void error(const QLowEnergyController::Error error);
    void deviceDiscovered(const QBluetoothDeviceInfo deviceInfo) const;
    void scanFinished() const;
    void discoveryFinished();
    void accelerometerServiceStateChanged(const QLowEnergyService::ServiceState state);
    void accelerometerDataChanged(const QLowEnergyCharacteristic characteristic, QByteArray data);
    void buttonServiceStateChanged(const QLowEnergyService::ServiceState state);
    void buttonDataChanged(const QLowEnergyCharacteristic characteristic, const QByteArray data) const;
};

#endif // BLUETOOTHMANAGER_H
