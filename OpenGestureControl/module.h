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

#ifndef MODULE_H
#define MODULE_H

#include <QObject>
#include <QString>

/*! \brief A class which represents a single module.*/

class Module : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)

public:
    /*! \brief The constructor.
     *
     *  This constructor instantiates this class.
     */
    explicit Module(QObject *parent = 0 /*!< [in] optional parameter, a QObject pointer to the parent of this class.*/);

    /*! \brief The constructor.
     *
     *  This constructor instantiates this object with all the variables given to it.
     */
    explicit Module(const QString &name, /*!< [in] parameter, a dereferenced QString pointer to the name of this option.*/
                          QObject *parent = 0 /*!< [in] optional parameter, a QObject pointer to the parent of this class.*/);

    /*! \brief A getter function for m_name.*/
    QString name() const;
    /*! \brief A setter function for m_name.*/
    void setName(const QString name);

private:
    QString m_name; /*!< A QString reference to the name of the option. */

signals:
    /*! \brief This signal fires when the m_name variable is changed via setName.*/
    void nameChanged();

public slots:
};

#endif // MODULE_H
