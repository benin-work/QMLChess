import QtQuick 2.0
import QtQuick.Controls 1.2
import QtQuick.Layouts 1.0
import ChessLib 1.0

Rectangle {
    width: 200
    height: 100

    property ChessGame chessGame: null

    GridView {
        id: mainList
        anchors.fill: parent
        model: chessGame.chessMoves
        delegate: moveDelegate
        focus: true

        cellWidth: chessBoard.gridSize
        cellHeight: cellWidth / 2

        highlight: Rectangle { color: "skyblue" }

        Component {
            id: moveDelegate
            Item {
                width: mainList.cellWidth;
                height: mainList.cellHeight
                Rectangle {
                    anchors.fill: parent
                    color: GridView.isCurrentItem ? "skyblue" : "transparent"
                    Text {
                        anchors.horizontalCenter: parent.horizontalCenter
                        font.pixelSize: chessBoard.gridSize / 3
                        text: (model.index % 2) === 0 ?
                                  ("<b>" + ((model.index)/2 + 1) + ".</b> " + model.modelData.name) : model.modelData.name
                    }
                }
            }
        }
    }
}
