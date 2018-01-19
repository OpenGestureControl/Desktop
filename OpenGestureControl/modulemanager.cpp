#include "modulemanager.h"

ModuleManager::ModuleManager(QObject *parent) : QObject(parent)
{

}

QDir ModuleManager::getModule() {
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
