#include "testcallbackhandler.h"

/*
-- browser.lua
-- Controls any browser with basic hotkeys
function return_options()
    io.write("We're asked for the options. Going to return them.\n");
    local entries = {};
    table.insert(entries, {name = "Open", icon = "OSwindow_500px.png"})
    table.insert(entries, {name = "Forward", icon = "Forward_500px.png"})
    table.insert(entries, {name = "Close", icon = "Close_500px.png"})
    table.insert(entries, {name = "Refresh", icon = "Refresh_500px.png"})
    table.insert(entries, {name = "Back", icon = "Back_500px.png"})
    return entries;
end

function handle(selection)
    io.write(string.format("We were asked to handle %s.\n", selection))
    if selection == "Open" then
        ModuleHelperSendKeyboardKey("Ctrl+T")
    elseif selection == "Forward" then
        ModuleHelperSendKeyboardKey("Alt+Right")
    elseif selection == "Close" then
        ModuleHelperSendKeyboardKey("Ctrl+W")
    elseif selection == "Refresh" then
        ModuleHelperSendKeyboardKey("F5")
    elseif selection == "Back" then
        ModuleHelperSendKeyboardKey("Alt+Left")
    else
        io.write("Unknown selection made\n")
    end
end

io.write("Init part\n");
*/

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
