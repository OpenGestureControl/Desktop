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
import QtQuick.Extras 1.4

Window {
    id: root
    width: Screen.desktopAvailableWidth
    height: Screen.desktopAvailableHeight

    title: qsTr("Input gesture")

    flags: Qt.FramelessWindowHint | Qt.WA_TranslucentBackground | Qt.WindowStaysOnTopHint

    color: Qt.rgba(0, 0, 0, 0.2)

    signal optionSelected(string optionName)

    function showMenu(menuContent) {
        pieMenu.menuItems = [];
        pieMenu.popup(root.width / 2, root.height / 2); // Workaround for PieMenu bug
        for (var key in menuContent) {
            var newItem = pieMenu.addItem(key);
            newItem.iconSource = "/icons/" + menuContent[key];
            newItem.triggered.connect(function() { optionSelected(pieMenu.lastItem.text) });
        }
        pieMenu.popup(root.width / 2, root.height / 2);
    }

    PieMenu {
        id: pieMenu

        width: Screen.desktopAvailableWidth / 1.5
        height: Screen.desktopAvailableHeight / 1.5

        triggerMode: TriggerMode.TriggerOnPress

        property var lastItem: null

        onCurrentItemChanged: {
            if (pieMenu.currentItem != null) {
                pieMenu.lastItem = pieMenu.currentItem;
            }
        }

        style: PieMenuStyle {
            startAngle: 0
            endAngle: 360
        }

        onVisibleChanged: {
            if (!pieMenu.visible) {
                root.visible = false;
            }
        }
    }
}
