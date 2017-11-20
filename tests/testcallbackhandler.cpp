#include "testcallbackhandler.h"

void TestCallbackHandler::GetCorrectOptionsFromLua() {

    // Arrange
    CallbackHandler handler;
    ModuleOptionsModel * result;
    ModuleOption *first, *second, *third, *fourth, *fifth;

    // Act
    result = handler.getOptions();
    first = result->get(0);
    second = result->get(1);
    third = result->get(2);
    fourth = result->get(3);
    fifth = result->get(4);

    // Assert
    QVERIFY(first->name() == QString("Open"));
    QVERIFY(second->name() == QString("Forward"));
    QVERIFY(third->name() == QString("Close"));
    QVERIFY(fourth->name() == QString("Refresh"));
    QVERIFY(fifth->name() == QString("Back"));
}

void TestCallbackHandler::HandleOptionChoiceCorrectly() {
    // Arrange
    CallbackHandler handler;
    bool result;

    // Act
    result = handler.handle(QString("Open"));

    // Assert
    QVERIFY(result == true);

}

void TestCallbackHandler::HandleOptionChoiceIncorrectly() {
    // Arrange
    CallbackHandler handler;
    bool result;

    // Act
    result = handler.handle(QString("incorrect"));

    // Assert
    QVERIFY(result == false);

}
