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

#ifndef MODULEOPTION_H
#define MODULEOPTION_H

#include <QObject>
#include <QString>

/*! \brief A class which represents an option within the piemenu.*/

class ModuleOption : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QString icon READ icon WRITE setIcon NOTIFY iconChanged)
    Q_PROPERTY(int index READ index WRITE setIndex NOTIFY indexChanged)

public:
    /*! \brief The constructor.
     *
     *  This constructor instantiates this class.
     */
    explicit ModuleOption(QObject *parent = 0 /*!< [in] optional parameter, a QObject pointer to the parent of this class.*/);

    /*! \brief The constructor.
     *
     *  This constructor instantiates this object with all the variables given to it.
     */
    explicit ModuleOption(const QString &name, /*!< [in] parameter, a dereferenced QString pointer to the name of this option.*/
                          const QString &icon, /*!< [in] parameter, a dereferenced Qstring pointer to the icon of this option.*/
                          const int &index, /*!< [in] parameter, a dereferenced integer pointer to the index of this option.*/
                          QObject *parent = 0 /*!< [in] optional parameter, a QObject pointer to the parent of this class.*/);

    /*! \brief A getter function for m_name.*/
    QString name() const;
    /*! \brief A setter function for m_name.*/
    void setName(const QString name);

    /*! \brief A getter function for m_icon.*/
    QString icon() const;
    /*! \brief A setter function for m_icon.*/
    void setIcon(const QString icon);

    /*! \brief A getter function for m_index.*/
    int index() const;
    /*! \brief A setter function for m_index.*/
    void setIndex(const int index);

private:
    QString m_name; /*!< A QString reference to the name of the option. */
    QString m_icon; /*!< A QString reference to the icon of the option. */
    int m_index; /*!< An integer reference to the index of the option. */

signals:
    /*! \brief This signal fires when the m_name variable is changed via setName.*/
    void nameChanged();
    /*! \brief This signal fires when the m_icon variable is changed via setIcon.*/
    void iconChanged();
    /*! \brief This signal fires when the m_index variable is changed via setIndex.*/
    void indexChanged();

public slots:
};

#endif // BLUETOOTHDEVICE_H
