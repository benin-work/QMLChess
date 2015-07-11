import QtQuick 2.0
import QtQuick.Controls 1.2
import QtQuick.Layouts 1.0
import ChessLib 1.0

Rectangle {
    width: 200
    height: 100

    color: "transparent"

    property ChessGame chessGame: null

    GridView {
        id: mainList

        //anchors.fill: parent
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.bottom: parent.bottom
        anchors.margins: 5

        model: chessGame.chessMoves
        delegate: moveDelegate
        focus: true

        cellWidth: parent.width / 2 - anchors.margins * 2
        cellHeight: chessBoard.gridSize / 2

        width: cellWidth * 2

        highlight: Rectangle { color: "skyblue" }

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
                    border.width: 1
                    radius: 4

                    color: GridView.isCurrentItem ? "skyblue" : "transparent"
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
            }
        }
    }
}
