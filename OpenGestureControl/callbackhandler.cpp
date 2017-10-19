#include "callbackhandler.h"

CallbackHandler::CallbackHandler(QObject *parent) : QObject(parent)
{

}

void CallbackHandler::handle(QString optionName)
{
    qWarning() << optionName;
}
