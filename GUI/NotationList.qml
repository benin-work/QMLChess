import QtQuick 2.0

Rectangle {
    width: 100;
    height: 100

    ListModel {
        id: movesModel
        ListElement {
            _color: "White"
            move: "e2"
        }
        ListElement {
            _color: "Black"
            move: "e4"
        }
        ListElement {
            _color: "White"
            move: "Bxe2"
        }
        ListElement {
            _color: "Black"
            move: "Qxf4+"
        }
    }

    Component {
        id: moveDelegate
        Item {
            width: 180; height: 40
            Column {
                Text { text: '<b>' + _color + "</b>: " + move}
            }
        }
    }

    ListView {
        anchors.fill: parent
        model: movesModel
        delegate: moveDelegate
        highlight: Rectangle { color: "lightsteelblue"; radius: 5 }
        focus: true

        header: Rectangle {
            width: parent.width
            height: 40
            border {
                color: "black"
                width: 1
            }

            Text {
                anchors.centerIn: parent
                renderType: Text.NativeRendering
                text: "Moves"
            }
        }
    }

}
