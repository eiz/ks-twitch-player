import QtQuick 2.0
import org.e7m.steamlink 1.0
import org.e7m.kappa.core.ui 1.0

SLListView {
    focus: true

    model: ListModel {
        ListElement { name: "Following" }
        ListElement { name: "Games" }
        ListElement { name: "Channels" }
        ListElement { name: "Settings" }
    }

    delegate: SLRoundedPanel {
        id: wrapper
        width: 200
        height: 30
        highlight: ListView.isCurrentItem

        Text {
            anchors.fill: parent
            id: label
            text: name
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            color: wrapper.ListView.isCurrentItem ? "cyan" : "white"

            Behavior on color {
                ColorAnimation { duration: 100 }
            }
        }
    }
}
