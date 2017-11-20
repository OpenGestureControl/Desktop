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
        ModuleHelperSendKeyboardKey("MediaNext")
    elseif selection == "Previous" then
        ModuleHelperSendKeyboardKey("MediaPrev")
    elseif selection == "Play" then
        ModuleHelperSendKeyboardKey("MediaPlayPause")
    elseif selection == "Stop" then
        ModuleHelperSendKeyboardKey("MediaStop")
    elseif selection == "VolumeUp" then
        ModuleHelperSendKeyboardKey("VolumeUp")
    elseif selection == "VolumeDown" then
        ModuleHelperSendKeyboardKey("VolumeDown")
    else
        io.write("Unknown selection made\n")
    end
end

io.write("Init part\n");
