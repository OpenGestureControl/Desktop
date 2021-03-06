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

#include "bluetoothdevice.h"

BluetoothDevice::BluetoothDevice(QObject *parent) : QObject(parent)
{
}

BluetoothDevice::BluetoothDevice(const QBluetoothDeviceInfo &deviceInfo, QObject *parent)
    : QObject(parent), m_deviceInfo(deviceInfo)
{
}

void BluetoothDevice::setDeviceInfo(const QBluetoothDeviceInfo deviceInfo)
{
    if (deviceInfo != this->m_deviceInfo) {
        this->m_deviceInfo = deviceInfo;
        emit deviceInfoChanged();
    }
}

void BluetoothDevice::setActive(const bool value)
{
    if (value != this->m_active) {
        this->m_active = value;
        this->connectionProgress = 0;
        emit activeChanged();
    }

    if (value && this->deviceInfo().isValid()) {
        qWarning() << "Creating Low Energy Controller";
        this->lowEnergyController = QLowEnergyController::createCentral(this->deviceInfo());
        qWarning() << "Workaround for failing to connect";
        this->lowEnergyController->setRemoteAddressType(QLowEnergyController::RandomAddress);

        qWarning() << "Preparing connecting to device";
        connect(this->lowEnergyController, SIGNAL(connected()),
                this, SLOT(lowEnergyControllerConnected()));
        connect(this->lowEnergyController, SIGNAL(disconnected()),
                this, SIGNAL(disconnected()));
        connect(this->lowEnergyController, SIGNAL(error(QLowEnergyController::Error)),
                this, SIGNAL(lowEnergyControllerError(QLowEnergyController::Error)));
        qWarning() << "Connecting to device";
        this->lowEnergyController->connectToDevice();
    } else if (this->lowEnergyController->state() != QLowEnergyController::UnconnectedState) {
        this->lowEnergyController->disconnectFromDevice();
    }
}

void BluetoothDevice::lowEnergyControllerConnected() const
{
    qWarning() << "Preparing service discovery";
    connect(this->lowEnergyController, SIGNAL(discoveryFinished()),
            this, SLOT(discoveryFinished()));
    qWarning() << "Starting service discovery";
    this->lowEnergyController->discoverServices();
}

void BluetoothDevice::discoveryFinished()
{
     qWarning() << "Discovery finished";
     qWarning() << "Preparing services we want";
     if (!(this->accelerometer = this->lowEnergyController->createServiceObject(QBluetoothUuid(QString("{e95d0753-251d-470a-a062-fa1922dfa9a8}"))))) {
         qWarning() << "Could not find the accelerometer service!";
         emit discoveryFailed("Could not find the accelerometer service");
         return;
     }

     if (!(this->button = this->lowEnergyController->createServiceObject(QBluetoothUuid(QString("{e95d9882-251d-470a-a062-fa1922dfa9a8}"))))) {
         emit discoveryFailed("Could not find the button service");
         return;
     }

     connect(this->accelerometer, SIGNAL(stateChanged(QLowEnergyService::ServiceState)),
            this, SLOT(accelerometerServiceStateChanged(QLowEnergyService::ServiceState)));
     connect(this->button, SIGNAL(stateChanged(QLowEnergyService::ServiceState)),
             this, SLOT(buttonServiceStateChanged(QLowEnergyService::ServiceState)));

     this->accelerometer->discoverDetails();
     this->button->discoverDetails();
}

void BluetoothDevice::accelerometerServiceStateChanged(const QLowEnergyService::ServiceState state)
{
    qWarning() << state;
    if (state == QLowEnergyService::ServiceDiscovered) {
        qWarning() << "Accelerometer service is ready";
        QLowEnergyCharacteristic accelerometerData = this->accelerometer->characteristic(QBluetoothUuid(QString("{e95dca4b-251d-470a-a062-fa1922dfa9a8}")));
        QLowEnergyDescriptor notification = accelerometerData.descriptor(QBluetoothUuid::ClientCharacteristicConfiguration);

        if (!accelerometerData.isValid()) {
            emit characteristicBindingFailed("Accelerometer data not valid");
            return;
        }

        connect(this->accelerometer, SIGNAL(characteristicChanged(QLowEnergyCharacteristic, QByteArray)),
                this, SLOT(accelerometerDataChanged(QLowEnergyCharacteristic, QByteArray)));

        // Enable notification
        this->accelerometer->writeDescriptor(notification, QByteArray::fromHex("0100"));

        this->connectionProgress++;

        if (this->connectionProgress == 2) {
            emit connected();
        }
    }
}

void BluetoothDevice::accelerometerDataChanged(const QLowEnergyCharacteristic characteristic, QByteArray data)
{
    if (characteristic.uuid() != QBluetoothUuid(QString("{e95dca4b-251d-470a-a062-fa1922dfa9a8}")))
    {
        qWarning() << "Not the characteristic we want for accelerometer, ignoring";
        return;
    }

    QDataStream ds(data);
    char x[2];
    ds.readRawData(x, 2);
    char y[2];
    ds.readRawData(y, 2);
    char z[2];
    ds.readRawData(z, 2);

    short xData = shortFromLittleEndianBytes(x);
    short yData = shortFromLittleEndianBytes(y);
    short zData = shortFromLittleEndianBytes(z);

    accelInput[0] = xData/(float)1000;
    accelInput[1] = yData/(float)1000;
    accelInput[2] = zData/(float)1000;

    this->lowPass(accelInput, accelOutput);

    float threshold = 0.2;
    int updown = 0, leftright = 0, deg = 0;

    if (accelInput[1] < -threshold) updown = 1; // User moves up
    else if (accelInput[1] > threshold) updown = -1; // User moves down

    if (accelInput[0] > threshold) leftright = -1; // User moves left
    else if (accelInput[0] < -threshold) leftright = 1; // User moves right

    if (updown == 0 && leftright == 0) deg = -1;    // If no angle is held
    else {
        float rad = atan2(leftright, updown);       // Get angle in radians
        deg = int(rad * (180 / 3.14159));       // Translate to degrees
        if (deg < 0) deg = 360 + deg;               // Minor correction if degrees are negative
    }
    qWarning() << "degrees moved: " << deg;
    emit degreesMoved(deg);
}

void BluetoothDevice::buttonServiceStateChanged(const QLowEnergyService::ServiceState state)
{
    qWarning() << state;
    if (state == QLowEnergyService::ServiceDiscovered) {
        qWarning() << "Button service is ready";
        QLowEnergyCharacteristic buttonData = this->button->characteristic(QBluetoothUuid(QString("{e95dda90-251d-470a-a062-fa1922dfa9a8}")));
        QLowEnergyDescriptor notification = buttonData.descriptor(QBluetoothUuid::ClientCharacteristicConfiguration);

        if (!buttonData.isValid()) {
            emit characteristicBindingFailed("Button data not valid");
            return;
        }

        connect(this->button, SIGNAL(characteristicChanged(QLowEnergyCharacteristic, QByteArray)),
                this, SLOT(buttonDataChanged(QLowEnergyCharacteristic, QByteArray)));

        // Enable notification
        this->button->writeDescriptor(notification, QByteArray::fromHex("0100"));

        this->connectionProgress++;

        if (this->connectionProgress == 2) {
            emit connected();
        }
    }
}

void BluetoothDevice::buttonDataChanged(const QLowEnergyCharacteristic characteristic, const QByteArray data) const
{
    if (characteristic.uuid() != QBluetoothUuid(QString("{e95dda90-251d-470a-a062-fa1922dfa9a8}")))
    {
        qWarning() << "Not the characteristic we want for button, ignoring";
        return;
    }
    QString data2 = QString(data);
    qWarning() << "Button:" << data2;
    if (data2 == "\x00") {
        emit buttonReleased();
    } else if (data2 == "\x01") {
        emit buttonPressed();
    }
}

short BluetoothDevice::shortFromLittleEndianBytes(const char bytes[]) const {

    if (bytes == nullptr ) {
        return 0;
    }

    short result=0;
    result = (short) (((bytes[1]  & 0xff ) << 8) + (bytes[0] & 0xff));
    if ((result | 0x8000) == 0x8000 ) {
        result = (short) (result * -1);
    }
    return result;
}

void BluetoothDevice::lowPass(const float input[], float output[]) const {
    if ( output == nullptr ) return;

    for ( int i=0; i < 3; i++ ) {
        output[i] = output[i] +  ALPHA * (input[i] - output[i]);
    }
}
