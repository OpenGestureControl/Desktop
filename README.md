[![Travis build status](https://travis-ci.org/OpenGestureControl/Desktop.svg?branch=master)](https://travis-ci.org/OpenGestureControl) [![codecov](https://codecov.io/gh/OpenGestureControl/Desktop/branch/master/graph/badge.svg)](https://codecov.io/gh/OpenGestureControl/Desktop)

The OpenGestureControl project is made possible by [ICT Group](https://ict.eu/).

# OpenGestureControl Desktop
OpenGestureControl Desktop is an application for Linux which interacts with the BBC micro:bit to give handprothesis users the ability to control their desktop computer using gestures.

## How to use
Ensure you have at least one module (see [our GitHub org](https://github.com/OpenGestureControl/)) in ``~/.config/opengesturecontrol/modules/<module_name>``. Flash our firmware onto a micro:bit (repo coming soon) and connect the micro:bit using the Bluetooth dialog. Hold button A to open the pie menu. At this point, move your microbit in the direction of the option you want to select. Release button A to close the pie menu.

## Module development
See [MODULE_DEVELOPMENT.md](MODULE_DEVELOPMENT.md).

## License
MIT
