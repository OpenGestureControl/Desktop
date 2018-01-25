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

#ifndef BLUETOOTHMANAGER_H
#define BLUETOOTHMANAGER_H

#include <QAbstractItemModel>
#include <QBluetoothDeviceDiscoveryAgent>
#include <QLowEnergyController>
#include <QDataStream>
#include <QtMath>
#include <QObject>
#include <QString>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QDebug>

#include "bluetoothdevicelistmodel.h"
#include "piemenu.h"

/*! \brief A class which manages all known Bluetooth devices.
 *
 *  This class handles the discovery, connecting and releasing of Bluetooth LE devices.
 *  It also retains a list of previously connected Bluetooth LE devices for easy managing.
 *  Finally it controls when the Bluetooth UI is opened and closed.
 */

class BluetoothManager : public QObject
{
    Q_OBJECT

public:
    /*! \brief The constructor.
     *
     *  This constructor instantiates this class.
     */
    explicit BluetoothManager(QObject *parent = 0 /*!< [in] optional parameter, a QObject pointer to the parent of this class.*/);
    /*! \brief A function to open the Bluetooth UI.*/
    void openUI() const;
    /*! \brief A function to close the Bluetooth UI.*/
    void closeUI() const;
    /*! \brief A function to check if the Bluetooth UI is open.*/
    bool isUIOpen() const;

private:
    QBluetoothDeviceDiscoveryAgent *bluetoothDeviceDiscoveryAgent; /*! A QBluetoothDeviceDiscoveryAgent pointer which can discover services of found Bluetooth devices.*/
    QQmlApplicationEngine engine; /*! A QQmlApplicationEngine value variable.*/
    BluetoothDeviceListModel *bluetoothDevices; /*! A BluetoothDeviceListModel pointer which holds all found Bluetooth devices.*/
    BluetoothDevice *connectingTo; /*! A BluetoothDevice pointer which points to the Bluetooth device to which it is currently connecting to.*/
    QObject *window; /*! A QObject pointer which points to the piemenu UI.*/

signals:
    /*! \brief This signal fires when the 'A' button of the Micro:bit is pressed.*/
    void buttonAPressed() const;
    /*! \brief This signal fires when the 'A' button of the Micro:bit is released.*/
    void buttonAReleased() const;
    /*! \brief This signal fires when the 'A' button of the Micro:bit is held.*/
    void buttonAHeld() const;
    /*! \brief This signal fires when the 'B' button of the Micro:bit is pressed.*/
    void buttonBPressed() const;
    /*! \brief This signal fires when the 'B' button of the Micro:bit is released.*/
    void buttonBReleased() const;
    /*! \brief This signal fires when the 'B' button of the Micro:bit is held.*/
    void buttonBHeld() const;
    /*! \brief This signal fires when the user tilts the Micro:bit.*/
    void degreesMoved(const int degrees /*!< [in] parameter, an integer value holding the direction of the movement expressed in degrees (0-360 degress).*/) const;

public slots:
    /*! \brief This slot scans for all Bluetooth LE devicesin the vacinity.*/
    void scanForDevices();
    /*! \brief This slot connects to a device selected by the user.*/
    void connectToDevice(const QString deviceAddress /*!< [in] parameter, a QString value holding the adress of the device to connect to.*/);
    /*! \brief This slot forgets a previously connected device.*/
    void forgetDevice(const QString deviceAddress /*!< [in] parameter, a QString value holding the adress of the device to forget.*/);
    /*! \brief This slot connects multiple signals and slots after a connection with a Bluetooth LE has been established.*/
    void connected() const;
    /*! \brief This slot cleans up after a Bluetooth LE connection has been forgotten.*/
    void disconnected();
    /*! \brief This slot handles errors thrown during connecting and disconnecting Bluetooth LE devices.*/
    void error(const QString reason /*!< [in] parameter, a QString value holding the reason why the programm threw an error.*/);
    /*! \brief This slot handles errors thrown during connecting and disconnecting Bluetooth LE devices.*/
    void error(QLowEnergyController::Error reason /*!< [in] parameter, a QString value holding the reason why the programm threw an error.*/);
    /*! \brief This slot adds newly discovered Bluetooth LE devices to the BluetoothDeviceListModel.*/
    void deviceDiscovered(const QBluetoothDeviceInfo deviceInfo /*!< [in] parameter, a QBluetoothDeviceInfo value holding the information of the newly discovered Bluetooth LE device.*/) const;
    /*! \brief This slot cleans up after scanning for nerby Bluetooth LE devices is finished.*/
    void scanFinished() const;
};

#endif // BLUETOOTHMANAGER_H
