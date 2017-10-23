import QtQuick 2.0
import QtQuick.Window 2.2
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.3

Window {
    id: root
    width: 640
    height: 480

    title: qsTr("OpenGestureControl - Bluetooth Manager")

    visible: true

    SystemPalette { id: palette; colorGroup: SystemPalette.Active }

    Item {
        anchors.fill: parent

        BusyIndicator {
            id: busyIndicator

            visible: false
            anchors.verticalCenter: parent.verticalCenter
            anchors.horizontalCenter: parent.horizontalCenter
        }
    }

    ColumnLayout {
        height: root.height
        width: root.width

        Text {
            Layout.fillWidth: true

            text: qsTr("Connect to device:")

            font.pointSize: 14
            font.bold: true
            horizontalAlignment: Text.AlignHCenter
        }

        ScrollView {
            Layout.fillHeight: true
            Layout.fillWidth: true

            ListView {
                id: deviceList

                model: 10

                delegate: Component {
                    Item {
                        id: wrapper

                        width: parent.width
                        height: connectButton.height

                        Row {
                            Text {
                                id: text
                                text: "Prosthetic %1 (00000000-0000-1000-8000-00805F9B34FB)".arg(model.index)
                                height: connectButton.height
                                width: deviceList.width - connectButton.width - forgetButton.width
                                elide: Text.ElideRight
                                verticalAlignment: Text.AlignVCenter
                            }
                            Button {
                                id: connectButton

                                visible: wrapper.ListView.isCurrentItem

                                text: qsTr("Connect")
                            }
                            Button {
                                id: forgetButton

                                visible: wrapper.ListView.isCurrentItem

                                text: qsTr("Forget")
                            }
                        }
                        MouseArea {
                            anchors.fill: parent
                            hoverEnabled: true
                            onPositionChanged: deviceList.currentIndex = index
                        }
                    }
                }
                highlight: Rectangle {
                    color: palette.highlight
                }
                highlightFollowsCurrentItem: true
                highlightMoveDuration: 0
            }
        }

        Button {
            id: newDeviceButton
            Layout.fillWidth: true

            text: qsTr("Search for devices")

            onClicked: {
                text = qsTr("Searching...")
                // FIXME: Obviously, this is example code
                deviceList.model = 0
                busyIndicator.visible = true
                timer.start()
            }
        }
    }

    // FIXME: This timer is just an example
    Timer {
        id: timer
        interval: 200
        repeat: true
        onTriggered: {
            if (deviceList.count < 5) {
                deviceList.model = deviceList.count + 1
            } else {
                busyIndicator.visible = false
                newDeviceButton.text = qsTr("Search for devices")
                timer.stop()
            }
        }
    }
}
