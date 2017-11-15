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

#ifndef PIEMENU_H
#define PIEMENU_H

#include <functional>

#include <QObject>
#include <QString>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQmlPropertyMap>
#include <QWindow>
#include <iostream>

#include "callbackhandler.h"
#include "moduleoptionsmodel.h"

/*! \brief A class which creates and manages the piemenu QML object.
 *
 *  This class retrieves the QML piemenu file and renders it.
 *  It retains a reference to the created QML to open and close it.
 */

class PieMenu : public QObject
{
    Q_OBJECT
public:
    /*! \brief The constructor.
     *
     *  This constructor retrieves the pieMenu.qml file and instantiates it.
     *  When the QML is instantiated it does not open itself.
     *  It also sets a reference to the QML in the QML itself (like a javascript "this" variable).
     */
    explicit PieMenu(QObject *parent = Q_NULLPTR /*!< [in] optional parameter, a QObject pointer to the parent of this class.*/);

    /*! \brief This function opens the QML.
     *
     *  This function removes all previous callbackhandlers and instantiates a new one.
     *  It then opens the QML with options from the active Lua module in Callbackhandler.
     */
    void open();

    /*! \brief This function translates the mouse position to an option entry.
     *
     *  This function recieves a mouse/hand position and calculates which option the mouse/hand hovering over.
     *  It then highlights this position in the view for visual feedback for the user.
     */
    void setActive(int degrees /*!< [in] parameter, an integer reference to the position of the mouse/hand expressed in degrees*/);

    /*! \brief This function checks whether the QML is visible.
     *
     *  This function check if the QML is visible for the user and returns a boolean indicating if visible (true) or not (false).
     */
    bool isOpen();

private:
    QObject *window; /*!< A pointer to a QML object. */
    QString appPath; /*!< A reference path to the active Lua module. */
    QQmlApplicationEngine engine; /*!< A reference to a QML creator engine. */
    QMetaObject::Connection activeCallbackConnection; /*!< A reference between a QML Signal and pieMenu slot */
    CallbackHandler *callbackHandler; /*!< A pointer to a callback handler. */

signals:

public slots:
    /*! \brief This function closes the QML.
     *
     *  This function sets the visible property of the QML object on false.
     */
    void close();
};

#endif // PIEMENU_H
