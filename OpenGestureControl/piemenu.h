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
#include <QMap>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQmlPropertyMap>
#include <QWindow>
#include <iostream>

#include "abstractcallbackhandler.h"
#include "windowscallbackhandler.h"
#include "linuxcallbackhandler.h"
#include "moduleoptionslistmodel.h"

/*! \brief A class which creates and manages the piemenu QML view object.
 *
 *  This class retrieves the QML view piemenu file and renders it.
 *  It retains a reference to the created QML view to open and close it.
 */

class PieMenu : public QObject
{
    Q_OBJECT
public:
    /*! \brief The constructor.
     *
     *  This constructor retrieves the pieMenu.qml file and instantiates it.
     *  When the QML is instantiated it does not open itself.
     *  It also sets a reference to the QML view in the QML itself (like a javascript "this" variable).
     */
    explicit PieMenu(QObject *parent = Q_NULLPTR /*!< [in] optional parameter, a QObject pointer to the parent of this class.*/);

    /*! \brief This function opens the QML.
     *
     *  This function removes all previous callbackhandlers and instantiates a new one.
     *  It then opens the QML view with options from the active Lua module in Callbackhandler.
     */
    void open();

    /*! \brief This function translates the mouse position to an option entry.
     *
     *  This function recieves a mouse/hand position and calculates which option the mouse/hand hovering over.
     *  It then highlights this position in the view for visual feedback for the user.
     */
    void setActive(int degrees /*!< [in] parameter, an integer reference to the position of the mouse/hand expressed in degrees*/);

    /*! \brief This function checks whether the QML view is visible.
     *
     *  This function check if the QML view is visible for the user and returns a boolean indicating if visible (true) or not (false).
     */
    bool isOpen();

private:
    QObject *window; /*!< A QObject pointer to a QML view object. */
    QString appPath; /*!< A QString reference path to the active Lua module. */
    QQmlApplicationEngine engine; /*!< A QQmlApplicationEngine reference to a QML creator engine. */
    QMetaObject::Connection activeCallbackConnection; /*!< A QMetaObject reference between a QML Signal and pieMenu slot */
    AbstractCallbackHandler *callbackHandler; /*!< A CallbackHandler pointer to a callback handler. */
    ModuleOptionsListModel *moduleOptions; /*!< The list of displayed options. */

signals:

public slots:
    /*! \brief This function closes the QML.
     *
     *  This function sets the visible property of the QML view object on false.
     * It does not destroy the QML view object
     */
    void close();
};

#endif // PIEMENU_H
