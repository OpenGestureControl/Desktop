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

#include "moduleoption.h"

ModuleOption::ModuleOption(QObject *parent) : QObject(parent)
{

}

ModuleOption::ModuleOption(const QString &name, const QString &icon, const int &index, QObject *parent)
    : QObject(parent), m_name(name), m_icon(icon), m_index(index)
{

}

QString ModuleOption::name() const
{
    return this->m_name;
}

QString ModuleOption::icon() const
{
    return this->m_icon;
}

int ModuleOption::index() const
{
    return this->m_index;
}

void ModuleOption::setName(const QString name)
{
    if (name != this->m_name) {
        this->m_name = name;
        emit nameChanged();
    }
}

void ModuleOption::setIcon(const QString icon)
{
    if (icon != this->m_icon) {
        this->m_icon = icon;
        emit iconChanged();
    }
}

void ModuleOption::setIndex(const int index)
{
    if (index != this->m_index) {
        this->m_index = index;
        emit indexChanged();
    }
}
