-- browser.lua
-- Controls any browser with basic hotkeys
function return_options()
    io.write("We're asked for the options. Going to return them.\n");
    local entries = {};
    table.insert(entries, {name = "Open", icon = "OSwindow_500px.png"})
    table.insert(entries, {name = "Forward", icon = "Forward_500px.png"})
    return entries;
end

function handle(selection)
    io.write("We're asked to handle something. Going to handle it.\n");
    io.write(string.format("We were asked to handle %s, but this isn't implemented yet.\n", selection))
end

io.write("We're not in the function right now\n");
