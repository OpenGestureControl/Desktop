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

#ifndef APPSWITCHER_H
#define APPSWITCHER_H

#include <QObject>
#include <QTimer>

#include "windowscallbackhandler.h"
#include "linuxcallbackhandler.h"

#ifdef Q_OS_LINUX
#include <X11/Xlib.h>
#include <X11/keysym.h>
#include <X11/Xutil.h>
#undef Bool // Needed because of weird Xlib C library
#endif // Q_OS_LINUX

class AppSwitcher : public QObject
{
    Q_OBJECT

public:
    /*! \brief The constructor.
     *
     *  This constructor instantiates this class.
     */
    explicit AppSwitcher(QObject *parent = 0 /*!< [in] optional parameter, a QObject pointer to the parent of this class.*/);

private:
    QTimer *switchTimer = new QTimer(this);
    quint32 *windowList;
    quint32 currentwindow;
    unsigned long numItems;
    Display *XDisplay;

public slots:
    /*! \brief This function opens the appswitcher. */
    void open();

    /*! \brief This function closes the appswitcher. */
    void close() const;

    /*! \brief This function switches app. */
    void switchApp();

};

#endif // APPSWITCHER_H
