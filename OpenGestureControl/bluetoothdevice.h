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
#include <QBluetoothServiceDiscoveryAgent>
#include <QDataStream>
#include <QLowEnergyController>
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
    void setDeviceInfo(const QBluetoothDeviceInfo name /*!< [in] parameter, a QBluetoothDeviceInfo value indicating the new deviceinfo.*/);

    /*! \brief A getter function for the QBluetoothDeviceInfo device name.*/
    QString name() const { return m_deviceInfo.name(); }
    /*! \brief A getter function for the QBluetoothDeviceInfo device adress.*/
    QString address() const { return m_deviceInfo.address().toString(); }

    /*! \brief A getter function to check if the device is active.*/
    bool active() const { return m_active; }
    /*! \brief A setter function to set the device active.*/
    void setActive(const bool value /*!< [in] parameter, a boolean value indicating the active value.*/);

    /*! \brief A getter function to check if this Bluetooth device is connected.*/
    bool isConnected() const { return this->lowEnergyController->state() == QLowEnergyController::ConnectedState; }

    /*! \brief A helper function to translate the byte data from the accelerometer to decimal numbers.*/
    short shortFromLittleEndianBytes(const char bytes[] /*!< [in] parameter, a char array pointer with the raw accelerometer data.*/) const;

    /*! \brief A filter function to help create a more stable movement detection.*/
    void lowPass(const float input[] /*!< [in] parameter, a float array pointer with new accelerometer data to smooth.*/,
                 float output[] /*!< [in] parameter, a float array pointer with the previously smoothed accelerometer data.*/) const;

private:
    QBluetoothDeviceInfo m_deviceInfo; /*! \brief A QBluetoothDeviceInfo reference to the Qt bluetooth class.*/
    QLowEnergyService *accelerometer, *button; /*! \brief A QLowEnergyService pointer which represents a Bluetooth LE Service.*/
    QLowEnergyController *lowEnergyController = nullptr; /*! \brief A QLowEnergyController pointer which handles the Bluetooth LE Services.*/

    bool m_active = false; /*! \brief A boolean reference to indicate whether or not this device is active.*/
    int connectionProgress = 0; /*! \brief An integer reference to indicate the connection status of this Bluetooth device.*/

    float accelInput[3]; /*! \brief A float array pointer to hold new accelerometer data from the lowPass filter.*/
    float accelOutput[3]; /*! \brief A float array pointer to hold previous accelerometer smoothing data from the lowPass filter.*/
    const float ALPHA = 0.15f; /*! \brief A float reference which is used by the lowPass smoothing function to set how much smoothing is required.*/

signals:
    /*! \brief This signal fires when a new QBluetoothDeviceInfo class is set.*/
    void deviceInfoChanged() const;
    /*! \brief This signal fires when this device changes it's active boolean.*/
    void activeChanged() const;
    /*! \brief This signal fires when this the program can't find the services of this Bluetooth LE device.*/
    void discoveryFailed(const QString reason /*!< [in] parameter, a QString value holding the reason for the failure.*/) const;
    /*! \brief This signal fires when this the program can't bind the characteristics of a Bluetooth LE service.*/
    void characteristicBindingFailed(const QString reason /*!< [in] parameter, a QString value holding the reason for the failure.*/) const;

    /*! \brief This signal fires when this device is connected.*/
    void connected() const;
    /*! \brief This signal fires when this device is disconnected.*/
    void disconnected() const;

    /*! \brief This signal fires when the 'A' button of the Micro:bit is pressed.*/
    void buttonPressed() const;
    /*! \brief This signal fires when the 'A' button of the Micro:bit is released.*/
    void buttonReleased() const;
    /*! \brief This signal fires when the user tilts the Micro:bit.*/
    void degreesMoved(const int degrees /*!< [in] parameter, an integer value holding the direction of the movement expressed in degrees (0-360 degress).*/) const;

    /*! \brief This signal fires when an error happens somewhere in this class.*/
    void lowEnergyControllerError(const QLowEnergyController::Error error /*!< [in] parameter, an Error value holding the error that was thrown.*/) const;

public slots:
    /*! \brief This slot sets up a newly connected device.*/
    void lowEnergyControllerConnected() const;
    /*! \brief This slot finishes up when the program has discovered all services of a Bluetooth LE device.*/
    void discoveryFinished();
    /*! \brief This slot changes the state of the accelerometer characteristics and if required calls the accelerometerDataChanged slot.*/
    void accelerometerServiceStateChanged(const QLowEnergyService::ServiceState state /*!< [in] parameter, a ServiceState value holding the new state.*/);
    /*! \brief This slot interprets the data recieved from the accelerometerservice.*/
    void accelerometerDataChanged(const QLowEnergyCharacteristic characteristic /*!< [in] parameter, a QLowEnergyCharacteristic value holding the characteristic from which the new data came.*/,
                                  QByteArray data /*!< [in] parameter, a QByteArray value holding the accelerometer data.*/);
    /*! \brief This slot changes the state of the button characteristics and if required calls the buttonDataChanged slot.*/
    void buttonServiceStateChanged(const QLowEnergyService::ServiceState state /*!< [in] parameter, a ServiceState value holding the new state.*/);
    /*! \brief This slot interprets the data recieved from the buttonservice.*/
    void buttonDataChanged(const QLowEnergyCharacteristic characteristic /*!< [in] parameter,  a QLowEnergyCharacteristic value holding the characteristic from which the new data came.*/,
                           const QByteArray data /*!< [in] parameter, a QByteArray value holding the button data.*/) const;
};

#endif // BLUETOOTHDEVICE_H
