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
        ModuleHelperPushKeyboardKey("VK_LCONTROL")
        ModuleHelperPushKeyboardKey(0x54)
        ModuleHelperReleaseKeyboardKey(0x54)
        ModuleHelperReleaseKeyboardKey("VK_LCONTROL")
    elseif selection == "Forward" then
        ModuleHelperPushKeyboardKey("VK_BROWSER_FORWARD")
    elseif selection == "Close" then
        ModuleHelperPushKeyboardKey("VK_LCONTROL")
        ModuleHelperPushKeyboardKey(0x57)
        ModuleHelperReleaseKeyboardKey(0x57)
        ModuleHelperReleaseKeyboardKey("VK_LCONTROL")
    elseif selection == "Refresh" then
        ModuleHelperPushKeyboardKey("VK_BROWSER_REFRESH")
    elseif selection == "Back" then
        ModuleHelperPushKeyboardKey("VK_BROWSER_BACK")
    else
        io.write("Unknown selection made\n")
    end
end

io.write("Init part\n");
