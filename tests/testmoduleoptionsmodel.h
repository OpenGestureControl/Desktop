#include <QtTest/QtTest>

#include "../OpenGestureControl/moduleoptionsmodel.h"

class TestModuleOptionsModel : public QObject
{
    Q_OBJECT
private slots:
    void storingAndRetrievingOptions();
    void getCorrectOptionsCount();
    void correctlyClearOptionsCount();
};
