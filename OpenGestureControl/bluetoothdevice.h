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

#ifndef BLUETOOTHDEVICE_H
#define BLUETOOTHDEVICE_H

#include <QBluetoothAddress>
#include <QBluetoothDeviceInfo>
#include <QObject>
#include <QString>
#include <QVariant>

/*! \brief A class which represents a found bluetooth device.*/

class BluetoothDevice : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QBluetoothDeviceInfo deviceInfo READ deviceInfo WRITE setDeviceInfo NOTIFY deviceInfoChanged)
    Q_PROPERTY(QString name READ name NOTIFY deviceInfoChanged)
    Q_PROPERTY(QString address READ address NOTIFY deviceInfoChanged)
    Q_PROPERTY(bool active READ active WRITE setActive NOTIFY activeChanged)

public:
    /*! \brief The constructor.
     *
     *  This constructor instantiates this class.
     */
    explicit BluetoothDevice(QObject *parent = 0 /*!< [in] optional parameter, a QObject pointer to the parent of this class.*/);
    /*! \brief The constructor.
     *
     *  This constructor instantiates this object with all the variables given to it.
     */
    explicit BluetoothDevice(const QBluetoothDeviceInfo &deviceInfo, /*!< [in] parameter, a dereferenced QBluetoothDeviceInfo pointer to the QBluetoothDeviceInfo that this class governs.*/
                             QObject *parent = 0 /*!< [in] optional parameter, a QObject pointer to the parent of this class.*/);

    /*! \brief A getter function for the QBluetoothDeviceInfo.*/
    QBluetoothDeviceInfo deviceInfo() const { return m_deviceInfo; }
    /*! \brief A setter function for the QBluetoothDeviceInfo.*/
    void setDeviceInfo(const QBluetoothDeviceInfo name);

    /*! \brief A getter function for the QBluetoothDeviceInfo device name.*/
    QString name() const { return m_deviceInfo.name(); }
    /*! \brief A getter function for the QBluetoothDeviceInfo device adress.*/
    QString address() const { return m_deviceInfo.address().toString(); }

    /*! \brief A getter function to check if the device is active.*/
    bool active() const { return m_active; }
    /*! \brief A setter function to set the device active.*/
    void setActive(const bool value);

private:

    QBluetoothDeviceInfo m_deviceInfo; /*! \brief A QBluetoothDeviceInfo reference to the Qt bluetooth class.*/
    bool m_active = false; /*! \brief A boolean reference to indicate whether or not this device is active.*/

signals:
    /*! \brief This signal fires when a new QBluetoothDeviceInfo class is set.*/
    void deviceInfoChanged();
    /*! \brief This signal fires when when this device changes it's active boolean.*/
    void activeChanged();

public slots:
};

#endif // BLUETOOTHDEVICE_H
