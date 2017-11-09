#include <QtTest/QtTest>

#include "../OpenGestureControl/bluetoothdevicelistmodel.h"

class TestBluetoothDeviceListModel : public QObject
{
    Q_OBJECT
private slots:
    void storingAndRetrievingBluetoothDevice();
};

void TestBluetoothDeviceListModel::storingAndRetrievingBluetoothDevice()
{
    // Arrange
    QString name = "Example device";
    QString deviceId = "00000000-0000-1000-8000-00805F9B34FB";

    BluetoothDeviceListModel *bluetoothDeviceListModel = new BluetoothDeviceListModel();
    BluetoothDevice *bluetoothDevice = new BluetoothDevice(name, deviceId);

    // Act
    bluetoothDeviceListModel->addDevice(bluetoothDevice);
    BluetoothDevice *retrievedBluetoothDevice = bluetoothDeviceListModel->get(0);

    // Assert
    QVERIFY(retrievedBluetoothDevice->name() == name);
    QVERIFY(retrievedBluetoothDevice->deviceId() == deviceId);
}

QTEST_MAIN(TestBluetoothDeviceListModel)
#include "testbluetoothdevicelistmodel.moc"
