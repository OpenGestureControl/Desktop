#include "modulemanager.h"

ModuleManager::ModuleManager(QObject *parent) : QObject(parent)
{

}

bool ModuleManager::checkForModule() {
    QString windowTitle = WindowInformation::GetWindowTitle();

    // TODO
    // Check all files in modules map in config map
    // Retrieve from each module the metadata file with applicable apps name in it
    // Check title against each applicable apps name
QDir::home();
    QString dirString = ""; //QDir::home(); + "/.config";
    qWarning() << dirString << endl;
    qWarning() << windowTitle << endl;
    //QDirIterator iterator(dir.home() + "/.config", QDirIterator::Subdirectories);
}

