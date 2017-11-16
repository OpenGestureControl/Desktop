import QtQuick 2.0
import QtQuick.Window 2.2
import QtQuick.Controls 1.4

Window {
    id: root
    width: 640
    height: 480

    title: qsTr("OpenGestureControl")

    visible: true // FIXME: Make false after testing

    TabView {
        width: parent.width
        height: parent.height

        Tab {
            width: parent.width
            height: parent.height

            title: "Modules"

            ListView {
                model: moduleList

                delegate: Text {
                    text: name
                }
            }
        }
    }
}
