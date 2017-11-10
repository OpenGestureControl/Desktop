#include <QtTest/QtTest>

#include "../OpenGestureControl/bluetoothdevicelistmodel.h"

class TestBluetoothDeviceListModel : public QObject
{
    Q_OBJECT
private slots:
    void storingAndRetrievingBluetoothDevice();
    void getCorrectBluetoothDeviceCount();
    void correctlyClearBluetoothDeviceCount();
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

void TestBluetoothDeviceListModel::getCorrectBluetoothDeviceCount()
{
    // Arrange
    QString name1 = "Example device 1";
    QString name2 = "Example device 2";
    QString name3 = "Example device 3";
    QString deviceId1 = "00000000-0000-1000-8000-00805F9B34FA";
    QString deviceId2 = "00000000-0000-1000-8000-00805F9B34FB";
    QString deviceId3 = "00000000-0000-1000-8000-00805F9B34FC";

    BluetoothDeviceListModel *bluetoothDeviceListModel = new BluetoothDeviceListModel();
    BluetoothDevice *bluetoothDevice1 = new BluetoothDevice(name1, deviceId1);
    BluetoothDevice *bluetoothDevice2 = new BluetoothDevice(name2, deviceId2);
    BluetoothDevice *bluetoothDevice3 = new BluetoothDevice(name3, deviceId3);

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
    QString deviceId1 = "00000000-0000-1000-8000-00805F9B34FA";
    QString deviceId2 = "00000000-0000-1000-8000-00805F9B34FB";
    QString deviceId3 = "00000000-0000-1000-8000-00805F9B34FC";

    BluetoothDeviceListModel *bluetoothDeviceListModel = new BluetoothDeviceListModel();
    BluetoothDevice *bluetoothDevice1 = new BluetoothDevice(name1, deviceId1);
    BluetoothDevice *bluetoothDevice2 = new BluetoothDevice(name2, deviceId2);
    BluetoothDevice *bluetoothDevice3 = new BluetoothDevice(name3, deviceId3);

    bluetoothDeviceListModel->addDevice(bluetoothDevice1);
    bluetoothDeviceListModel->addDevice(bluetoothDevice2);
    bluetoothDeviceListModel->addDevice(bluetoothDevice3);

    // Act
    bluetoothDeviceListModel->clear();

    // Assert
    QVERIFY(bluetoothDeviceListModel->rowCount() == 0);
}

QTEST_MAIN(TestBluetoothDeviceListModel)
#include "testbluetoothdevicelistmodel.moc"
