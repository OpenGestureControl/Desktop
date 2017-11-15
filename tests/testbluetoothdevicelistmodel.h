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
