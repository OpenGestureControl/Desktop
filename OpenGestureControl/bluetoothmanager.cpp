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
#include <QDebug>

BluetoothManager::BluetoothManager(QObject *parent) : QObject(parent)
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

bool BluetoothManager::isUIOpen()
{
    return this->window->property("visible").toBool();
}

void BluetoothManager::openUI()
{
    this->window->setProperty("visible", true);
}

void BluetoothManager::closeUI()
{
    this->window->setProperty("visible", false);
}

void BluetoothManager::scanForDevices()
{
    this->window->setProperty("status", "SCANNING");
    this->bluetoothDevices->clear();
    this->bluetoothDeviceDiscoveryAgent->start();
}

void BluetoothManager::connectToDevice(QString deviceAddress)
{
    qWarning() << deviceAddress;
    qWarning() << "Creating Low Energy Controller";
    this->lowEnergyController = QLowEnergyController::createCentral(bluetoothDevices->get(deviceAddress)->deviceInfo());
    qWarning() << "Workaround for failing to connect";
    lowEnergyController->setRemoteAddressType(QLowEnergyController::RandomAddress);
    qWarning() << "Preparing connecting to device";
    connect(lowEnergyController, SIGNAL(connected()),
            this, SLOT(connected()));
    qWarning() << "Connecting to device";
    lowEnergyController->connectToDevice();
}

void BluetoothManager::forgetDevice(QString deviceAddress)
{
    // TODO: Forget device
}

void BluetoothManager::deviceDiscovered(QBluetoothDeviceInfo deviceInfo)
{
    bluetoothDevices->addDevice(new BluetoothDevice(deviceInfo));
}

void BluetoothManager::discoveryFinished()
{
     qWarning() << "Discovery finished";
     qWarning() << "Preparing services we want";
     if (!(this->accelerometer = lowEnergyController->createServiceObject(QBluetoothUuid(QString("{e95d0753-251d-470a-a062-fa1922dfa9a8}")))))
         qWarning() << "Could not find the accelerometer service!";

     if (!(this->button = lowEnergyController->createServiceObject(QBluetoothUuid(QString("{e95d9882-251d-470a-a062-fa1922dfa9a8}")))))
         qWarning() << "Could not find the button service!";

     connect(this->accelerometer, SIGNAL(stateChanged(QLowEnergyService::ServiceState)),
            this, SLOT(accelerometerServiceStateChanged(QLowEnergyService::ServiceState)));
     connect(this->button, SIGNAL(stateChanged(QLowEnergyService::ServiceState)),
             this, SLOT(buttonServiceStateChanged(QLowEnergyService::ServiceState)));

     this->accelerometer->discoverDetails();
     this->button->discoverDetails();
}

void BluetoothManager::accelerometerServiceStateChanged(QLowEnergyService::ServiceState state)
{
    qWarning() << state;
    if (state == QLowEnergyService::ServiceDiscovered) {
        qWarning() << "Accelerometer service is ready";
        QLowEnergyCharacteristic accelerometerData = this->accelerometer->characteristic(QBluetoothUuid(QString("{e95dca4b-251d-470a-a062-fa1922dfa9a8}")));
        QLowEnergyDescriptor notification = accelerometerData.descriptor(QBluetoothUuid::ClientCharacteristicConfiguration);

        if (!accelerometerData.isValid())
            qWarning() << "Accelerometer data not valid! Halp!";

        connect(this->accelerometer, SIGNAL(characteristicChanged(QLowEnergyCharacteristic, QByteArray)),
                this, SLOT(accelerometerDataChanged(QLowEnergyCharacteristic, QByteArray)));

        // Enable notification
        this->accelerometer->writeDescriptor(notification, QByteArray::fromHex("0100"));
    }
}

void BluetoothManager::accelerometerDataChanged(QLowEnergyCharacteristic characteristic, QByteArray data)
{
    if (characteristic.uuid() != QBluetoothUuid(QString("{e95dca4b-251d-470a-a062-fa1922dfa9a8}")))
    {
        qWarning() << "Not the characteristic we want for accelerometer, ignoring";
        return;
    }
    qWarning() << "Accelerometer:" << data;
}

void BluetoothManager::buttonServiceStateChanged(QLowEnergyService::ServiceState state)
{
    qWarning() << state;
    if (state == QLowEnergyService::ServiceDiscovered) {
        qWarning() << "Button service is ready";
        QLowEnergyCharacteristic buttonData = this->button->characteristic(QBluetoothUuid(QString("{e95dda90-251d-470a-a062-fa1922dfa9a8}")));
        QLowEnergyDescriptor notification = buttonData.descriptor(QBluetoothUuid::ClientCharacteristicConfiguration);

        if (!buttonData.isValid())
            qWarning() << "Button data not valid! Halp!";

        connect(this->button, SIGNAL(characteristicChanged(QLowEnergyCharacteristic, QByteArray)),
                this, SLOT(buttonDataChanged(QLowEnergyCharacteristic, QByteArray)));

        // Enable notification
        this->button->writeDescriptor(notification, QByteArray::fromHex("0100"));
    }
}

void BluetoothManager::buttonDataChanged(QLowEnergyCharacteristic characteristic, QByteArray data)
{
    if (characteristic.uuid() != QBluetoothUuid(QString("{e95dda90-251d-470a-a062-fa1922dfa9a8}")))
    {
        qWarning() << "Not the characteristic we want for button, ignoring";
        return;
    }
    qWarning() << "Button:" << data;
}

void BluetoothManager::connected()
{
    qWarning() << "Preparing service discovery";
    connect(lowEnergyController, SIGNAL(discoveryFinished()),
            this, SLOT(discoveryFinished()));
    qWarning() << "Starting service discovery";
    lowEnergyController->discoverServices();
}

void BluetoothManager::scanFinished()
{
    this->window->setProperty("status", "IDLE");
}
