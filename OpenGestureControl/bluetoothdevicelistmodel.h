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

#ifndef BLUETOOTHDEVICELISTMODEL_H
#define BLUETOOTHDEVICELISTMODEL_H

#include <QAbstractListModel>
#include <QBluetoothAddress>

#include "bluetoothdevice.h"

class BluetoothDeviceListModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(int count READ rowCount NOTIFY countChanged)

public:
    enum BluetoothDeviceRoles {
        NameRole = Qt::UserRole + 1,
        AddressRole
    };

    explicit BluetoothDeviceListModel(QObject *parent = 0);

    int rowCount(const QModelIndex & = QModelIndex()) const override { return m_data.count(); }
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    Q_INVOKABLE BluetoothDevice* get(int index) const { return m_data.at(index); }
    BluetoothDevice* get(QString deviceAddress);

    bool addDevice(BluetoothDevice* device);
    void clear();


signals:
    void countChanged(int c);

protected:
    QHash<int, QByteArray> roleNames() const;

private:
    QList<BluetoothDevice*> m_data;
};

#endif // BLUETOOTHDEVICELISTMODEL_H
