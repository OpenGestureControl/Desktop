/*
   Copyright (c) 2017 ICT Group

   Permission is hereby granted, free of charge, to any person obtaining a copy
   of this software and associated documentation files (the "Software"), to deal
   in the Software without restriction, including without limitation the rights
   to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
   copies of the Software, and to permit persons to whom the Software is
   furnished to do so, subject to the following conditions:

   The above copyright notice and this permission notice shall be included in all
   copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
   AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
   OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
   SOFTWARE.
*/

import QtQuick 2.0
import QtQuick.Window 2.2
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.3

Window {
    id: root
    width: 640
    height: 480

    title: qsTr("OpenGestureControl - Bluetooth Manager")

    signal scanRequest()
    signal connectRequest(string deviceAddress)
    signal forgetRequest(string deviceAddress)

    property string status: "IDLE"
    // FIXME: Remove this line later
    visible: true

    SystemPalette { id: palette; colorGroup: SystemPalette.Active }

    Item {
        anchors.fill: parent

        BusyIndicator {
            id: busyIndicator

            visible: root.status == "SCANNING"
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

                model: bluetoothDevices

                delegate: Component {
                    Item {
                        id: wrapper

                        width: parent.width
                        height: connectButton.height

                        Row {
                            Text {
                                id: text
                                text: "%1 (%2)".arg(model.name).arg(model.address)
                                height: connectButton.height
                                width: deviceList.width - connectButton.width - forgetButton.width
                                elide: Text.ElideRight
                                verticalAlignment: Text.AlignVCenter
                            }
                            Button {
                                id: connectButton

                                text: qsTr("Connect")

                                enabled: !model.active && root.status != "CONNECTING"

                                onClicked: connectRequest(model.address)
                            }
                            Button {
                                id: forgetButton

                                text: qsTr("Forget")

                                enabled: !connectButton.enabled && root.status != "CONNECTING"

                                onClicked: forgetRequest(model.address)
                            }
                        }
                    }
                }
            }
        }

        Button {
            id: newDeviceButton
            Layout.fillWidth: true

            text: if (root.status == "IDLE")
                     return qsTr("Search for devices")
                  else if (root.status == "SCANNING")
                      return qsTr("Searching...")
                  else if (root.status == "CONNECTING")
                      return qsTr("Connecting...")
                  else if (root.status == "CONNECTED")
                      return qsTr("Disconnect and search for devices")
            enabled: root.status == "IDLE" || root.status == "CONNECTED"

            onClicked: {
                scanRequest();
            }
        }
    }
}
