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

import QtQuick 2.6
import QtQuick.Window 2.2
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import QtQuick.Layouts 1.3

Window {
    id: root
    width: Screen.desktopAvailableWidth
    height: Screen.desktopAvailableHeight

    title: qsTr("Input gesture")

    flags: Qt.FramelessWindowHint | Qt.WA_TranslucentBackground | Qt.WindowStaysOnTopHint

    color: Qt.rgba(0, 0, 0, 0.2)

    signal optionSelected(string optionName)
    signal closeRequest()

    onOptionSelected: closeRequest()

    ListView {
        model: moduleOptions

        delegate: Component {
            Item {
                x: model.index * 100
                y: model.index * 100
                width: 100
                height: 100

                Button {
                    height: parent.height
                    width: parent.width
                    style: ButtonStyle {
                        background: Rectangle {
                            radius: 99999999
                        }
                    }

                    onClicked: optionSelected(model.name)

                    Image {
                        anchors {
                            fill: parent
                            leftMargin: 0.1 * parent.width
                            rightMargin: 0.1 * parent.width
                            topMargin: 0.1 * parent.height
                            bottomMargin: 0.1 * parent.height
                        }
                        source: "/icons/" + model.icon
                        fillMode: Image.PreserveAspectFit
                    }
                }
            }
        }
    }
}
