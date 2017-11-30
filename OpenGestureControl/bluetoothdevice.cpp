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

BluetoothDevice::BluetoothDevice(const QString &name, const QString &deviceAddress, QObject *parent)
    : QObject(parent), m_name(name), m_deviceAddress(deviceAddress)
{

}

QString BluetoothDevice::name() const
{
    return this->m_name;
}

QString BluetoothDevice::deviceAddress() const
{
    return this->m_deviceAddress;
}

void BluetoothDevice::setName(const QString name)
{
    if (name != this->m_name) {
        this->m_name = name;
        emit nameChanged();
    }
}

void BluetoothDevice::setDeviceAddress(const QString deviceAddress)
{
    if (deviceAddress != this->m_deviceAddress) {
        this->m_deviceAddress = deviceAddress;
        emit deviceAddressChanged();
    }
}
