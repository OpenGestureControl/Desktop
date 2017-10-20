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

    function _getTranslator(itemCount) {
        switch(itemCount) {
        case 1:
            return [1];
        case 2:
            return [5, 3];
        case 3:
            return [1, 8, 6];
        case 4:
            return [1, 5, 7, 3];
        case 5:
            return [1, 5, 8, 6, 3];
        case 6:
            return [2, 5, 8, 6, 3, 0];
        case 7:
            return [1, 2, 5, 8, 6, 3, 0];
        case 8:
            return [1, 2, 5, 8, 7, 6, 3, 0];
        default:
            return;
        }
    }

    function showMenu(menuContent) {
        var menuKeys = Object.keys(menuContent);
        var translator = _getTranslator(menuKeys.length);

        for (var i = 0; i < menuKeys.length; i++) {
            var item = pieMenu.children[translator[i]];
            item.identifierId = translator[i]
            item.identifierText = menuKeys[i];
            item.imageURL = "/icons/" + menuContent[menuKeys[i]];
        }

        pieMenu.containCount = menuKeys.length
    }

    function setActiveEntry(degrees) {
        var degreesPerEntry = 360 / pieMenu.containCount;
        var section = parseInt((degrees + (0.5 * degreesPerEntry)) / degreesPerEntry) % pieMenu.containCount
        pieMenu.activeButtonId = _getTranslator(pieMenu.containCount)[section];
    }

    GridLayout {
        id: pieMenu

        property int activeButtonId: -1
        property int containCount: 0

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
                property int identifierId: -1
                property string identifierText: ""
                property string imageURL: ""

                Layout.fillHeight: true
                Layout.fillWidth: true

                width: this.height

                style: ButtonStyle {
                    background: Rectangle {
                        color: control.identifierId == pieMenu.activeButtonId ? "white" : Qt.darker("white")
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
