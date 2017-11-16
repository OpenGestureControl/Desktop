######################################################################
# Automatically generated by qmake (3.1) Fri Nov 10 13:52:37 2017
######################################################################

QT += qml quick widgets testlib
CONFIG += c++11 qt
TEMPLATE = app
TARGET = tests
INCLUDEPATH += .

# gcov
QMAKE_CXXFLAGS += -fprofile-arcs -ftest-coverage
macx: {
    QMAKE_LFLAGS += --coverage
    QMAKE_CFLAGS += --coverage
}
!macx: {
    LIBS += -lgcov
}

# The following define makes your compiler warn you if you use any
# feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

HEADERS += ../OpenGestureControl/piemenu.h \
    ../OpenGestureControl/keyboardinput.h \
    ../OpenGestureControl/callbackhandler.h \
    ../OpenGestureControl/bluetoothmanager.h \
    ../OpenGestureControl/bluetoothdevice.h \
    ../OpenGestureControl/bluetoothdevicelistmodel.h \
    ../OpenGestureControl/moduleoptionsmodel.h \
    ../OpenGestureControl/moduleoption.h \ # End of main project headers
    testbluetoothdevicelistmodel.h \
    testmoduleoptionsmodel.h \
    testcallbackhandler.h


SOURCES += ../OpenGestureControl/piemenu.cpp \
    ../OpenGestureControl/keyboardinput.cpp \
    ../OpenGestureControl/callbackhandler.cpp \
    ../OpenGestureControl/bluetoothmanager.cpp \
    ../OpenGestureControl/bluetoothdevice.cpp \
    ../OpenGestureControl/bluetoothdevicelistmodel.cpp \
    ../OpenGestureControl/moduleoptionsmodel.cpp \
    ../OpenGestureControl/moduleoption.cpp \ # End of main project sources
    testbluetoothdevicelistmodel.cpp \
    testmoduleoptionsmodel.cpp \
    testcallbackhandler.cpp \
    main.cpp

# Lua
win32:INCLUDEPATH += $$PWD/../OpenGestureControl/libs $$PWD/../OpenGestureControl/libs/include
win32:DEPENDPATH += $$PWD/../OpenGestureControl/libs

unix:LIBS += -llua -lm -ldl
win32:LIBS += -lpsapi -L$$PWD/../OpenGestureControl/libs/ -llua53
