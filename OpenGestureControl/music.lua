-- music.lua
-- Controls any music player basic hotkeys
function return_options()
    io.write("We're asked for the options. Going to return them.\n");
    local entries = {};
    table.insert(entries, {name = "Play", icon = "Play_500px.png"})
    table.insert(entries, {name = "Next", icon = "Forward_500px.png"})
    table.insert(entries, {name = "VolumeUp", icon = "VolumeUp_500px.png"})
    table.insert(entries, {name = "Stop", icon = "Stop_500px.png"})
    table.insert(entries, {name = "VolumeDown", icon = "VolumeDown_500px.png"})
    table.insert(entries, {name = "Previous", icon = "Back_500px.png"})
    return entries;
end

function handle(selection)
    io.write(string.format("We were asked to handle %s.\n", selection))
    if selection == "Next" then
        ModuleHelperSendKeyboardKey("Ctrl+Right")
    elseif selection == "Previous" then
        ModuleHelperSendKeyboardKey("Ctrl+Left")
    elseif selection == "Play" then
        ModuleHelperSendKeyboardKey("Space")
    elseif selection == "Stop" then
        ModuleHelperSendKeyboardKey("Space")
    elseif selection == "VolumeUp" then
        ModuleHelperSendKeyboardKey("Ctrl+Up")
    elseif selection == "VolumeDown" then
        ModuleHelperSendKeyboardKey("Ctrl+Down")
    else
        io.write("Unknown selection made\n")
    end
end

io.write("Init part\n");
