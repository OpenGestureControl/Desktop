#include <QtTest/QtTest>

#ifdef Q_OS_WIN32
#include <windows.h>
#endif

#include "../OpenGestureControl/callbackhandler.h"

class TestCallbackHandler : public QObject
{
    Q_OBJECT
private slots:
    void GetCorrectOptionsFromLua();
    void HandleOptionChoiceCorrectly();
    void HandleOptionChoiceIncorrectly();
};
