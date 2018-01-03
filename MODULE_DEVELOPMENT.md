# Module development
## Module format
A module exists of at least the following files:
- [main.lua](#mainlua)
- [metadata.json](#metadatajson)
and the following directories:
- [icons](#icons)

## main.lua
This is the main Lua file, which will be called with Lua 5.3 when your module will be opened. You should ensure it has the following functions:
- [return_options()](#return_options)
- [handle(selection)](#handleselection)

There is also a helper function available:
- [ModuleHelperSendKeyboardKey(keycombo)](#modulehelpersendkeyboardkeykeycombo)

### return_options()
This function is called when your module is opened.

In here, you should return all the options the user has to choose from, together with the name of the appropriate icons. These icons will be loaded from the ``icons`` directory and can be in any format [supported by QImageReader](https://doc.qt.io/qt-5/qimagereader.html#supportedImageFormats). Please keep note that the icons will be displayed in round fashion, so icons in other shapes may not look well.

The entries need to be returned in a table, with a name and icon key.

Example:
```
function return_options()
    local entries = {}
    table.insert(entries, {name = "Back", icon = "back.png"})
    table.insert(entries, {name = "Forward", icon = "forward.png"})
    return entries
end
```

### handle(selection)
This function is called when the user selected an option.

In here, you should handle the option the user chose.

The selection parameter is filled with the string in the name key of the selected table option that was defined in [return_options()](#return_options).

Example:
```
function handle(selection)
    if selection == "Back" then
        -- Do something to go back here
    elseif selection == "Forward" then
        -- Do something to go forward here
    end
end
```

### ModuleHelperSendKeyboardKey(keycombo)
This function can be called to send a keyboard key action. This is useful if you for example want to open a new tab in a browser.

Keys must be one of the following:
- "0" through "9"
- "a" through "z"
- "f1" through "f24"
- "backspace"
- "space"
- "tab"
- "left", "right", "up", "down"
- "medianext", "mediaprev", "mediaplaypause", "mediastop", "volumeup", "volumedown", "volumemute"

These keys can be combined with the modifier keys ctrl, alt and shift by prepending "ctrl+", "alt+", "shift+" or a combination of those before the key name.

Examples:
```
-- To switch to the next song
ModuleHelperSendKeyboardKey("medianext")

-- To send Ctrl+t
ModuleHelperSendKeyboardKey("ctrl+t")

-- To send Ctrl+Alt+up
ModuleHelperSendKeyboardKey("ctrl+alt+up")
```

## metadata.json
This is the main metadata file, which contains information about the module and when it should be called.

metadata.json supports the following keys:
- developer: developer name
- license: license name [in SPDX format](https://spdx.org/licenses/)
- supported_classnames: the classnames the window should have for each platform to be executed. Please note that any entry except "linux" is currently ignored

Example:
```
{
  "developer": "OpenGestureControl",
  "license": "MIT",
  "supported_classnames": {
    "linux": ["Firefox", "Chrome", "Chromium"]
  }
}
```

## icons
This directory contains all the icons used by the application, as described in [return_options()](#return_options).
