import QtQuick 2.0
import QtQuick.Controls 1.2
import QtQuick.Layouts 1.0
import ChessLib 1.0

Rectangle {
    width: 200
    height: 100

    color: "transparent"

    property ChessGameplay chessGame: null

    GridView {
        id: mainList

        //anchors.fill: parent
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.bottom: parent.bottom
        anchors.margins: 5

        focus: true

        model: chessGame.chessMoves
        delegate: moveDelegate

        cellWidth: parent.width / 2 - anchors.margins * 2
        cellHeight: chessBoard.gridSize / 2

        width: cellWidth * 2

        highlight: Rectangle { color: "yellow" }

        header: Item {
            id: listHeader
            width: parent.width
            height: mainList.cellHeight - 5

            Rectangle {
                anchors.left: parent.left
                anchors.top: parent.top
                width: mainList.width / 2
                height: parent.height
                border { color: "black"; width: 1 }

                Text {
                    anchors.centerIn: parent
                    anchors.left: parent.left
                    renderType: Text.NativeRendering
                    text: "White"
                }
            }
            Rectangle {
                anchors.right: parent.right
                anchors.top: parent.top
                width: mainList.width / 2
                height: parent.height
                border { color: "black"; width: 1 }

                Text {
                    anchors.centerIn: parent
                    anchors.left: parent.left
                    renderType: Text.NativeRendering
                    text: "Black"
                }
            }
        }

        Component {
            id: moveDelegate
            Item {
                width: mainList.cellWidth - 2
                height: mainList.cellHeight - 2
                Rectangle {
                    anchors.fill: parent

                    border.color: "black"
                    border.width: ma.containsMouse ? 3 : 1
                    radius: ma.containsMouse ? 4 : 0

                    color: GridView.isCurrentItem ? "yellow" : "transparent"
                    Text {
                        anchors.verticalCenter: parent.verticalCenter
                        //anchors.horizontalCenter: parent.horizontalCenter
                        anchors.left: parent.left
                        anchors.margins: 5

                        font.pixelSize: chessBoard.gridSize / 4
                        text: (model.index % 2) === 0 ?
                                  ("<b>" + ((model.index)/2 + 1) + ".</b> " + model.modelData.name) : model.modelData.name
                    }
                }

                MouseArea {
                    id: ma
                    anchors.fill: parent
                    hoverEnabled: true;
                    onClicked: {
                        chessGame.moveAt(model.index);
                    }
                }
            }
        }

        Component.onCompleted: {

        }

        Connections {
            target: chessGame
            onActiveMoveChanged: { mainList.currentIndex = activeMove }
        }
    }
}
