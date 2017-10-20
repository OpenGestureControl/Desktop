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

    function showMenu(menuContent) {
        var menuKeys = Object.keys(menuContent);

        var translator;
        // FIXME: Make less ugly
        switch(menuKeys.length) {
        case 1:
            translator = [1];
            break;
        case 2:
            translator = [5, 3];
            break;
        case 3:
            translator = [1, 8, 6];
            break;
        case 4:
            translator = [1, 5, 7, 3];
            break;
        case 5:
            translator = [1, 5, 8, 6, 3];
            break;
        case 6:
            translator = [2, 5, 8, 6, 3, 0];
            break;
        case 7:
            translator = [1, 2, 5, 8, 6, 3, 0];
            break;
        case 8:
            translator = [1, 2, 5, 8, 7, 6, 3, 0];
            break;
        default:
            return;
        }

        for (var i = 0; i < menuKeys.length; i++) {
            var item = pieMenu.children[translator[i]];
            item.identifierText = menuKeys[i];
            item.imageURL = "/icons/" + menuContent[menuKeys[i]];
        }
    }

    GridLayout {
        id: pieMenu
        width: root.width / 1.5
        height: root.height / 1.5

        anchors {
            horizontalCenter: parent.horizontalCenter
            verticalCenter: parent.verticalCenter
        }

        columns: 3
        rows: 3

        Repeater {
            model: 9
            Button {
                property string identifierText: ""
                property string imageURL: ""

                Layout.fillHeight: true
                Layout.fillWidth: true

                width: this.height

                style: ButtonStyle {
                    background: Rectangle {
                        color: control.hovered ? "white" : Qt.darker("white")
                        radius: 99999999
                    }
                }

                opacity: this.identifierText ? 0.8 : 0

                onClicked: if (this.identifierText) { optionSelected(this.identifierText) }

                Image {
                    anchors {
                        fill: parent
                        leftMargin: 0.1 * parent.width
                        rightMargin: 0.1 * parent.width
                        topMargin: 0.1 * parent.height
                        bottomMargin: 0.1 * parent.height
                    }
                    source: imageURL
                    fillMode: Image.PreserveAspectFit
                }
            }
        }
    }
}
