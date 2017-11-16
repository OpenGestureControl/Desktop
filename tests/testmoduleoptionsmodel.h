#include <QtTest/QtTest>

#include "../OpenGestureControl/moduleoptionsmodel.h"

class TestModuleOptionsModel : public QObject
{
    Q_OBJECT
private slots:
    void storingAndRetrievingOptions();
    void storingAndRetrievingDuplicateOptions();
    void getCorrectOptionsCount();
    void correctlyClearOptionsCount();
    void retrieveIncorrectRoleData();
};
