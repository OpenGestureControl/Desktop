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

    function showMenu(menuContent) {
        pieMenu.menuItems = [];
        pieMenu.popup(root.width / 2, root.height / 2); // Workaround for PieMenu bug
        for (var key in menuContent) {
            var newItem = pieMenu.addItem(key);
            newItem.iconSource = "/icons/" + menuContent[key];
        }
        pieMenu.popup(root.width / 2, root.height / 2);
    }

    PieMenu {
        id: pieMenu

        width: Screen.desktopAvailableWidth / 1.5
        height: Screen.desktopAvailableHeight / 1.5

        triggerMode: TriggerMode.TriggerOnPress

        style: PieMenuStyle {
            startAngle: 0
            endAngle: 360
        }
    }
}
