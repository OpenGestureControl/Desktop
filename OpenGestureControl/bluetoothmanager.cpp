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

    this->lowEnergyController = NULL;
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
    if(this->lowEnergyController) {
        this->lowEnergyController->disconnectFromDevice();
        delete this->lowEnergyController;
        this->lowEnergyController = nullptr;
    }

    this->window->setProperty("status", "SCANNING");
    this->bluetoothDevices->clear();
    this->bluetoothDeviceDiscoveryAgent->start();
}

void BluetoothManager::connectToDevice(const QString deviceAddress)
{
    qWarning() << "Disconnect existing device";
    if (this->lowEnergyController) {
        this->connectingTo->setActive(false);
        this->lowEnergyController->disconnectFromDevice();
        delete this->lowEnergyController;
        this->lowEnergyController = nullptr;
    }
    qWarning() << deviceAddress;
    this->connectionProgress = 0;
    this->connectingTo = bluetoothDevices->getDevice(deviceAddress);
    this->window->setProperty("status", "CONNECTING");
    qWarning() << "Creating Low Energy Controller";
    this->lowEnergyController = QLowEnergyController::createCentral(this->connectingTo->deviceInfo());
    qWarning() << "Workaround for failing to connect";
    this->lowEnergyController->setRemoteAddressType(QLowEnergyController::RandomAddress);

    qWarning() << "Preparing connecting to device";
    connect(this->lowEnergyController, SIGNAL(connected()),
            this, SLOT(connected()));
    connect(this->lowEnergyController, SIGNAL(disconnected()),
            this, SLOT(disconnected()));
    connect(this->lowEnergyController, SIGNAL(error(QLowEnergyController::Error)),
            this, SLOT(error(QLowEnergyController::Error)));
    qWarning() << "Connecting to device";
    this->lowEnergyController->connectToDevice();
}

void BluetoothManager::forgetDevice(const QString deviceAddress)
{
    bluetoothDevices->getDevice(deviceAddress)->setActive(false);
    this->window->setProperty("status", "IDLE");
    this->lowEnergyController->disconnectFromDevice();
    // Hack because the Connect/Forget buttons don't work well
    this->scanForDevices();
}

void BluetoothManager::deviceDiscovered(const QBluetoothDeviceInfo deviceInfo) const
{
    bluetoothDevices->addDevice(new BluetoothDevice(deviceInfo, lowEnergyController));
}

void BluetoothManager::connected() const
{
    qWarning() << "Preparing service discovery";
    connect(this->lowEnergyController, SIGNAL(discoveryFinished()),
            this->connectingTo, SLOT(discoveryFinished()));
    qWarning() << "Starting service discovery";
    this->lowEnergyController->discoverServices();
}

void BluetoothManager::disconnected()
{
    this->connectingTo->setActive(false);
    this->window->setProperty("status", "IDLE");
    // Hack because the Connect/Forget buttons don't work well
    this->scanForDevices();
}

void BluetoothManager::error(const QLowEnergyController::Error error)
{
    qWarning() << error;
    this->connectingTo->setActive(false);
    this->window->setProperty("status", "IDLE");
    // Hack because the Connect/Forget buttons don't work well
    this->scanForDevices();
}

void BluetoothManager::scanFinished() const
{
    if (!this->lowEnergyController || this->lowEnergyController->state() == QLowEnergyController::UnconnectedState)
        this->window->setProperty("status", "IDLE");
}
