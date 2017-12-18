#include "modulemanager.h"

ModuleManager::ModuleManager(QObject *parent) : QObject(parent)
{

}

QDir ModuleManager::getModule() {
    QString windowTitle = WindowInformation().GetWindowTitle();

    // TODO
    // Check all files in modules map in config map
    // Retrieve from each module the metadata file with applicable apps name in it
    // Check title against each applicable apps name
    QDir dir = QDir::home();
    dir.mkpath(".config/opengesturecontrol/modules"); // Ensure module directory exists
    if (!dir.cd(".config/opengesturecontrol/modules")) {
        qWarning("Couldn't cd into modules directory");
        return QDir();
    }
    qWarning() << dir << endl;
    qWarning() << windowTitle << endl;
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
            qWarning() << moduleDir << "is compatible";
            return moduleDir;
        };
    }

    // Nothing found
    return QDir();
}

