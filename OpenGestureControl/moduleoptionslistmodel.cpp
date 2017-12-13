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

#include "moduleoptionslistmodel.h"

ModuleOptionsListModel::ModuleOptionsListModel(QObject *parent) :
    QAbstractListModel(parent)
{
}

QHash<int, QByteArray> ModuleOptionsListModel::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[NameRole] = "name";
    roles[IconRole] = "icon";
    roles[IndexRole] = "index";
    return roles;
}

QVariant ModuleOptionsListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || index.row() < 0 || index.row() >= rowCount())
        return QVariant();

    ModuleOption *val = m_data.at(index.row());

    switch (role) {
    case Qt::DisplayRole:
    case NameRole:
        return val->name();
        break;
    case IconRole:
        return val->icon();
        break;
    case IndexRole:
        return val->index();
        break;
    default:
        return QVariant();
    }
}

bool ModuleOptionsListModel::addOption(ModuleOption *option)
{
    if (m_data.contains(option)) {
        return false;
    }

    beginInsertRows(QModelIndex(), m_data.size(), m_data.size());

    m_data.append(option);

    endInsertRows();

    return true;
}

void ModuleOptionsListModel::clear()
{
    beginRemoveRows(QModelIndex(), 0, m_data.size());

    m_data.clear();

    endRemoveRows();
}
