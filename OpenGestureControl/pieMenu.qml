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

    // FIXME: This timer is a hack, but doing pieMenu.popup() in pieMenu's
    // Component.onCompleted simply does not work. So we do it with a
    // 1 ms delay.
    Timer {
        id: pressAndHoldTimer
        interval: 1
        onTriggered: pieMenu.popup(root.width / 2, root.height / 2);
    }

    PieMenu {
        id: pieMenu

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
            pressAndHoldTimer.start();
        }
    }
}
