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

/*! \brief This class represents the list of bluetooth devices found after scanning.
 *
 *  This class manages a group of BluetoothDevice classes for the user to pick out from.
 */
class BluetoothDeviceListModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(int count READ rowCount NOTIFY countChanged)

public:
    enum BluetoothDeviceRoles {
        NameRole = Qt::UserRole + 1,
        AddressRole,
        ActiveRole
    };

    /*! \brief The constructor.
     *
     *  This constructor instantiates this class.
     */
    explicit BluetoothDeviceListModel(QObject *parent = 0 /*!< [in] optional parameter, a QObject pointer to the parent of this class.*/);

    /*! \brief This function returns the amount of BluetoothDevice found after scanning.*/
    int rowCount(const QModelIndex & = QModelIndex()) const override { return m_data.count(); }

    /*! \brief This function returns the data stored under the given role for the item referred to by the index.
     *
     *  This function is required to be implemented in order to inherit from QAbstractListModel.
     */
    QVariant data(const QModelIndex &index, const int role = Qt::DisplayRole) const override;

    /*! \brief This function returns the BluetoothDevice entry at the given index.*/
    Q_INVOKABLE BluetoothDevice* get(const int index) const { return m_data.at(index); }
    /*! \brief This function returns the BluetoothDevice referred to by the device adress.*/
    BluetoothDevice* getDevice(const QString deviceAddress);

    /*! \brief This function adds an BluetoothDevice object to the list of device.
     *
     *  This function first checks if the device to add already exists. If it doesn't it will add it to the data list of the class.
     */
    bool addDevice(BluetoothDevice* device);
    /*! \brief This function removes all BluetoothDevice objects from the list.*/
    void clear();

    /*! \brief This function is called to set a device on active.*/
    void setActive(BluetoothDevice *device /*!< [in] parameter, a BluetoothDevice pointer to the device to be set active.*/);
    /*! \brief This function unsets the current active BluetoothDevice.*/
    void clearActive();
    /*! \brief This function return the current active BluetoothDevice.*/
    BluetoothDevice* getActive();

protected:
    /*! \brief This function creates and returns a hashmap with rolenames required by Qt to work.*/
    QHash<int, QByteArray> roleNames() const override;

    BluetoothDevice *activeDevice = nullptr; /*!< A BluetoothDevice pointer to the currently active device. */

private:
    QList<BluetoothDevice*> m_data; /*!< \brief A QList value to the menu options pointers from the piemenu. */

signals:
    /*! \brief This signal fires when addDevice is finished.*/
    void countChanged(int c /*!< [in] parameter, an integer reference to the new amount.*/);
};

#endif // BLUETOOTHDEVICELISTMODEL_H
