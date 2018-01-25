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

#ifndef MODULEMANAGER_H
#define MODULEMANAGER_H

#include <QObject>
#include <QDebug>
#include <QtGlobal>

#undef Unsorted
#include <QDir>
#include <QDirIterator>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>

#include "windowinformation.h"

/*! \brief A class which manages all Modules.
 *
 *  This class handles the searching and retrieving of all modules.
 */
class ModuleManager : public QObject
{
    Q_OBJECT
public:
    /*! \brief The constructor.
     *
     *  This constructor instantiates this class.
     */
    explicit ModuleManager(QObject *parent = nullptr /*!< [in] optional parameter, a QObject pointer to the parent of this class.*/);
    /*! \brief This function returns a module based on the program currently running on the foreground.*/
    QDir getModule();
    /*! \brief A getter function for the errorstring.*/
    QString errorString() const;

private:
    QString eString; /*!< A QString value holding the error string if an error is thrown. */
    WindowInformation *windowInformation = new WindowInformation(); /*!< A WindowInformation pointer pointing to the windowInformation class. */

signals:

public slots:
};

#endif // MODULEMANAGER_H
