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

#ifndef MODULEOPTIONSMODEL_H
#define MODULEOPTIONSMODEL_H

#include <QAbstractListModel>

#include "moduleoption.h"

/*! \brief This class represents a piemenu.
 *
 *  This class manages a group of ModuleOptionsModel to store module options received from a Lua module.
 */

class ModuleOptionsListModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(int count READ rowCount NOTIFY countChanged)

public:
    /*! \brief This enum is used in the roleNames function to overwrite the default roles.*/
    enum ModuleOptionRoles {
        NameRole = Qt::UserRole + 1,
        IconRole,
        IndexRole
    };

    /*! \brief The constructor.
     *
     *  This constructor instantiates this class.
     */
    explicit ModuleOptionsListModel(QObject *parent = 0 /*!< [in] optional parameter, a QObject pointer to the parent of this class.*/);

    /*! \brief This function returns the amount of ModuleOptions currently loaded.*/
    int rowCount(const QModelIndex & = QModelIndex() /*!< [in] optional parameter, a QModelIndex reference required to overload this function.*/) const override { return m_data.count(); }

    /*! \brief This function returns the data stored under the given role for the item referred to by the index.
     *
     *  This function is required to be implemented in order to inherit from QAbstractListModel.
     */
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    /*! \brief This function returns the piemenu option at the given index.*/
    Q_INVOKABLE ModuleOption* get(int index /*!< [in] parameter, an integer reference to the requested index.*/) const { return m_data.at(index); }

    /*! \brief This function adds an ModuleOption object to the list of options.
     *
     *  This function first checks if the option to add already exists. If it doesn't it will add it to the data list of the class.
     */
    bool addOption(ModuleOption* option /*!< [in] parameter, a ModuleOption pointer to the ModuleOption to add.*/);
    /*! \brief This function removes all ModuleOption objects from the list of options.*/
    void clear();

signals:
    /*! \brief This signal fires when addoption is finished.*/
    void countChanged(int c /*!< [in] parameter, an integer reference to the new amount.*/);

protected:
    /*! \brief This function creates and returns a hashmap with rolenames required by Qt to work.*/
    QHash<int, QByteArray> roleNames() const;

private:
    QList<ModuleOption*> m_data; /*!< An QList reference to the menu options pointers from the piemenu. */
};

#endif // MODULEOPTIONSMODEL_H
