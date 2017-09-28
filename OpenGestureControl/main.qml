import QtQuick 2.6
import QtQuick.Window 2.2
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import QtQuick.Extras 1.4

Window {
    id: root
    visible: true
    width: Screen.desktopAvailableWidth
    height: Screen.desktopAvailableHeight
    title: qsTr("Input gesture")

    flags: Qt.FramelessWindowHint | Qt.WA_TranslucentBackground

    color: Qt.rgba(0, 0, 0, 0.2)

    MouseArea {
        anchors.fill: parent

        onPressed: pieMenu.popup(Screen.desktopAvailableWidth / 2, Screen.desktopAvailableHeight / 2)
    }

    PieMenu {
        id: pieMenu
        objectName: "pieMenu"

        width: Screen.desktopAvailableWidth / 1.5
        height: Screen.desktopAvailableHeight / 1.5

        triggerMode: TriggerMode.TriggerOnRelease

        style: PieMenuStyle {
            startAngle: 0
            endAngle: 360
        }

        Component.onCompleted: {
            var itemKeys = pieMenuItems.keys();

            for (var i = 0; i < itemKeys.length; i++) {
                var menuItem = itemKeys[i];
                var newItem = pieMenu.addItem(menuItem);
                newItem.iconSource = applicationPath + "/icons/" + pieMenuItems[menuItem];
            }
            pieMenu.update();
        }
    }
}
