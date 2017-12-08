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

#include "testbluetoothdevicelistmodel.h"

void TestBluetoothDeviceListModel::storingAndRetrievingBluetoothDevice()
{
    // Arrange
    QString name = "Example device";
    QString deviceAddress = "01:23:45:67:89:01";

    BluetoothDeviceListModel *bluetoothDeviceListModel = new BluetoothDeviceListModel();
    BluetoothDevice *bluetoothDevice = new BluetoothDevice(QBluetoothDeviceInfo(QBluetoothAddress(deviceAddress), name, 0));

    // Act
    bluetoothDeviceListModel->addDevice(bluetoothDevice);
    BluetoothDevice *retrievedBluetoothDevice = bluetoothDeviceListModel->get(0);

    // Assert
    QVERIFY(retrievedBluetoothDevice->name() == name);
    QVERIFY(retrievedBluetoothDevice->address() == deviceAddress);
}

void TestBluetoothDeviceListModel::getCorrectBluetoothDeviceCount()
{
    // Arrange
    QString name1 = "Example device 1";
    QString name2 = "Example device 2";
    QString name3 = "Example device 3";
    QString deviceAddress1 = "01:23:45:67:89:01";
    QString deviceAddress2 = "01:23:45:67:89:02";
    QString deviceAddress3 = "01:23:45:67:89:03";

    BluetoothDeviceListModel *bluetoothDeviceListModel = new BluetoothDeviceListModel();
    BluetoothDevice *bluetoothDevice1 = new BluetoothDevice(QBluetoothDeviceInfo(QBluetoothAddress(deviceAddress1), name1, 0));
    BluetoothDevice *bluetoothDevice2 = new BluetoothDevice(QBluetoothDeviceInfo(QBluetoothAddress(deviceAddress2), name2, 0));
    BluetoothDevice *bluetoothDevice3 = new BluetoothDevice(QBluetoothDeviceInfo(QBluetoothAddress(deviceAddress3), name3, 0));

    bluetoothDeviceListModel->addDevice(bluetoothDevice1);
    bluetoothDeviceListModel->addDevice(bluetoothDevice2);
    bluetoothDeviceListModel->addDevice(bluetoothDevice3);

    // Act
    int deviceCount = bluetoothDeviceListModel->rowCount();

    // Assert
    QVERIFY(deviceCount == 3);
}

void TestBluetoothDeviceListModel::correctlyClearBluetoothDeviceCount()
{
    // Arrange
    QString name1 = "Example device 1";
    QString name2 = "Example device 2";
    QString name3 = "Example device 3";
    QString deviceAddress1 = "01:23:45:67:89:01";
    QString deviceAddress2 = "01:23:45:67:89:02";
    QString deviceAddress3 = "01:23:45:67:89:03";

    BluetoothDeviceListModel *bluetoothDeviceListModel = new BluetoothDeviceListModel();
    BluetoothDevice *bluetoothDevice1 = new BluetoothDevice(QBluetoothDeviceInfo(QBluetoothAddress(deviceAddress1), name1, 0));
    BluetoothDevice *bluetoothDevice2 = new BluetoothDevice(QBluetoothDeviceInfo(QBluetoothAddress(deviceAddress2), name2, 0));
    BluetoothDevice *bluetoothDevice3 = new BluetoothDevice(QBluetoothDeviceInfo(QBluetoothAddress(deviceAddress3), name3, 0));

    bluetoothDeviceListModel->addDevice(bluetoothDevice1);
    bluetoothDeviceListModel->addDevice(bluetoothDevice2);
    bluetoothDeviceListModel->addDevice(bluetoothDevice3);

    // Act
    bluetoothDeviceListModel->clear();

    // Assert
    QVERIFY(bluetoothDeviceListModel->rowCount() == 0);
}
