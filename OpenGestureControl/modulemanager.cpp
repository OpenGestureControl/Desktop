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

#include "modulemanager.h"

ModuleManager::ModuleManager(QObject *parent) : QObject(parent)
{

}

QDir ModuleManager::getModule() {
    // TODO: When Windows gets working bluetooth, also make these checks function for Windows
    QString windowTitle = windowInformation->GetWindowTitle();

    QDir dir = QDir::home();
    dir.mkpath(".config/opengesturecontrol/modules"); // Ensure module directory exists
    if (!dir.cd(".config/opengesturecontrol/modules")) {
        this->eString = tr("Couldn't cd into modules directory");
        return QDir();
    }
    QDirIterator iterator(dir.canonicalPath(), QDir::Dirs | QDir::NoDotAndDotDot);
    while (iterator.hasNext()) {
        QString moduleDir = iterator.next();

        QFile metadataFile(moduleDir + "/metadata.json");
        if (!metadataFile.open(QIODevice::ReadOnly)) {
            qWarning() << "Couldn't open metadata.json for" << moduleDir;
            continue;
        }
        QByteArray metadataData = metadataFile.readAll();
        metadataFile.close();
        QJsonDocument metadataJson = QJsonDocument::fromJson(metadataData);
        QJsonObject metadata = metadataJson.object();

        if (metadata["supported_classnames"].toObject()["linux"].toArray().contains(windowTitle)) {
            this->eString = "";
            qWarning() << moduleDir << "is compatible";
            return moduleDir;
        };
    }

    // Nothing found
    this->eString = tr("Couldn't find a compatible module");
    return QDir();
}

QString ModuleManager::errorString() const
{
    return this->eString;
}
