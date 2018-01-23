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

#include "bluetoothmanager.h"

BluetoothManager::BluetoothManager(QObject *parent) : QObject(parent), bluetoothDeviceDiscoveryAgent()
{
    this->bluetoothDevices = new BluetoothDeviceListModel();
    this->engine.rootContext()->setContextProperty("bluetoothDevices", this->bluetoothDevices);

    this->engine.load(QUrl(QStringLiteral("qrc:/bluetoothManager.qml")));
    this->window = this->engine.rootObjects()[0];

    this->bluetoothDeviceDiscoveryAgent = new QBluetoothDeviceDiscoveryAgent();
    this->bluetoothDeviceDiscoveryAgent->setLowEnergyDiscoveryTimeout(5000);

    connect(this->bluetoothDeviceDiscoveryAgent, SIGNAL(deviceDiscovered(QBluetoothDeviceInfo)), this, SLOT(deviceDiscovered(QBluetoothDeviceInfo)));
    connect(this->bluetoothDeviceDiscoveryAgent, SIGNAL(finished()), this, SLOT(scanFinished()));

    connect(this->window, SIGNAL(scanRequest()), this, SLOT(scanForDevices()));
    connect(this->window, SIGNAL(connectRequest(QString)), this, SLOT(connectToDevice(QString)));
    connect(this->window, SIGNAL(forgetRequest(QString)), this, SLOT(forgetDevice(QString)));
}

bool BluetoothManager::isUIOpen() const
{
    return this->window->property("visible").toBool();
}

void BluetoothManager::openUI() const
{
    this->window->setProperty("visible", true);
}

void BluetoothManager::closeUI() const
{
    this->window->setProperty("visible", false);
}

void BluetoothManager::scanForDevices()
{
    this->window->setProperty("status", "SCANNING");
    this->bluetoothDevices->clear();
    this->bluetoothDeviceDiscoveryAgent->start();
}

void BluetoothManager::connectToDevice(const QString deviceAddress)
{
    qWarning() << deviceAddress;
    this->connectingTo = bluetoothDevices->getDevice(deviceAddress);
    connect(this->connectingTo, SIGNAL(discoveryFailed(QString)),
            this, SLOT(error(QString)));
    connect(this->connectingTo, SIGNAL(characteristicBindingFailed(QString)),
            this, SLOT(error(QString)));
    connect(this->connectingTo, SIGNAL(connected()),
            this, SLOT(connected()));
    connect(this->connectingTo, SIGNAL(disconnected()),
            this, SLOT(disconnected()));
    connect(this->connectingTo, SIGNAL(lowEnergyControllerError(QLowEnergyController::Error)),
            this, SLOT(error(QLowEnergyController::Error)));
    this->bluetoothDevices->setActive(this->connectingTo);
    this->window->setProperty("status", "CONNECTING");
}

void BluetoothManager::forgetDevice(const QString deviceAddress)
{
    this->bluetoothDevices->clearActive();
    this->window->setProperty("status", "IDLE");
    // Hack because the Connect/Forget buttons don't work well
    this->scanForDevices();
}

void BluetoothManager::deviceDiscovered(const QBluetoothDeviceInfo deviceInfo) const
{
    bluetoothDevices->addDevice(new BluetoothDevice(deviceInfo));
}

void BluetoothManager::connected() const
{
    connect(this->connectingTo, SIGNAL(buttonAPressed()),
            this, SIGNAL(buttonAPressed()));
    connect(this->connectingTo, SIGNAL(buttonAReleased()),
            this, SIGNAL(buttonAReleased()));
    connect(this->connectingTo, SIGNAL(buttonAHeld()),
            this, SIGNAL(buttonAHeld()));
    connect(this->connectingTo, SIGNAL(buttonBPressed()),
            this, SIGNAL(buttonBPressed()));
    connect(this->connectingTo, SIGNAL(buttonBReleased()),
            this, SIGNAL(buttonBReleased()));
    connect(this->connectingTo, SIGNAL(buttonBHeld()),
            this, SIGNAL(buttonBHeld()));
    connect(this->connectingTo, SIGNAL(degreesMoved(int)),
            this, SIGNAL(degreesMoved(int)));
    this->window->setProperty("status", "CONNECTED");
}

void BluetoothManager::disconnected()
{
    this->bluetoothDevices->clearActive();
    this->window->setProperty("status", "IDLE");
    // Hack because the Connect/Forget buttons don't work well
    this->scanForDevices();
}

void BluetoothManager::error(const QString reason)
{
    qWarning() << reason;
    this->bluetoothDevices->clearActive();
    this->window->setProperty("status", "IDLE");
    // Hack because the Connect/Forget buttons don't work well
    this->scanForDevices();
}

void BluetoothManager::error(QLowEnergyController::Error reason)
{
    this->error(reason);
}

void BluetoothManager::scanFinished() const
{
    BluetoothDevice *activeDevice = this->bluetoothDevices->getActive();
    if (!activeDevice || !activeDevice->isConnected())
        this->window->setProperty("status", "IDLE");
}
