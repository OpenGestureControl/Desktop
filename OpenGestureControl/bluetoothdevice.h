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

#ifndef BLUETOOTHDEVICE_H
#define BLUETOOTHDEVICE_H

#include <QBluetoothAddress>
#include <QBluetoothDeviceInfo>
#include <QBluetoothServiceDiscoveryAgent>
#include <QDataStream>
#include <QLowEnergyController>
#include <QObject>
#include <QString>
#include <QVariant>

class BluetoothDevice : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QBluetoothDeviceInfo deviceInfo READ deviceInfo WRITE setDeviceInfo NOTIFY deviceInfoChanged)
    Q_PROPERTY(QString name READ name NOTIFY deviceInfoChanged)
    Q_PROPERTY(QString address READ address NOTIFY deviceInfoChanged)
    Q_PROPERTY(bool active READ active WRITE setActive NOTIFY activeChanged)

public:
    explicit BluetoothDevice(QObject *parent = 0);
    explicit BluetoothDevice(const QBluetoothDeviceInfo &deviceInfo, QObject *parent = 0);

    QBluetoothDeviceInfo deviceInfo() const { return m_deviceInfo; }
    void setDeviceInfo(const QBluetoothDeviceInfo name);

    QString name() const { return m_deviceInfo.name(); }
    QString address() const { return m_deviceInfo.address().toString(); }

    bool active() const { return m_active; }
    void setActive(const bool value);

    bool isConnected() const { return this->lowEnergyController->state() == QLowEnergyController::ConnectedState; }

    short shortFromLittleEndianBytes(const char bytes[]) const;
    void lowPass(const float input[], float output[]) const;

private:
    QBluetoothDeviceInfo m_deviceInfo;
    QLowEnergyService *accelerometer, *button;
    QLowEnergyController *lowEnergyController;
    bool m_active = false;
    int connectionProgress = 0;

    float accelInput[3];
    float accelOutput[3];
    const float ALPHA = 0.15f;

signals:
    void deviceInfoChanged() const;
    void activeChanged() const;
    void discoveryFailed(const QString reason) const;
    void characteristicBindingFailed(const QString reason) const;

    void connected() const;
    void disconnected() const;

    void buttonPressed() const;
    void buttonReleased() const;
    void degreesMoved(const int degrees) const;

    void lowEnergyControllerError(const QLowEnergyController::Error error) const;

public slots:
    void lowEnergyControllerConnected() const;
    void discoveryFinished();
    void accelerometerServiceStateChanged(const QLowEnergyService::ServiceState state);
    void accelerometerDataChanged(const QLowEnergyCharacteristic characteristic, QByteArray data);
    void buttonServiceStateChanged(const QLowEnergyService::ServiceState state);
    void buttonDataChanged(const QLowEnergyCharacteristic characteristic, const QByteArray data) const;
};

#endif // BLUETOOTHDEVICE_H
