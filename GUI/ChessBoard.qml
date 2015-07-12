import QtQuick 2.0
import ChessLib 1.0
import "." as ChessGUI

// ChessBoard with markup

Rectangle {
    id: chessBoard
    property int gridSize: 64
    width: gridSize * 8 + gridSize // 8 cells + markers
    height: width

    property ChessPiece selectedPiece: null

    Rectangle {
        id: cbPlaceHolder
        width: parent.width
        height: parent.height

        border.color: "black"
        border.width: 2

        Grid {
            id: cbGrid

            x: gridSize / 2
            y: gridSize / 2
            width:  gridSize * 8
            height: gridSize * 8
            spacing: 0

            rows: 8
            columns: 8

            // ChessBoard tiles - from top left to buttom right
            Repeater {
                id: cbCells
                model: 64
                DropArea {
                    id: cbCellTarget
                    width: gridSize
                    height: gridSize

                    property int cx: x + width / 2
                    property int cy: y + height / 2
                    property int boardPos: modelData

                    Rectangle {
                        id: chessDrawCell
                        width: gridSize
                        height: gridSize

                        color: (Math.floor(index / 8) + (index % 8)) % 2 ?
                               "#763703" : "#FBD19C"

                        border.color: "yellow"
                        border.width: cbCellMa.containsMouse ? 3 : 0

                        MouseArea {
                            id: cbCellMa
                            anchors.fill: parent

                            hoverEnabled: selectedPiece != null

                            onClicked: {
                                if (selectedPiece != null) {
                                    if (!selectedPiece.tryToMove(cbCellTarget))
                                        selectPiece(null);
                                }
                            }
                        }
                    }

                    states: [
                        State {
                            name: "moveLookup"
                            PropertyChanges { target: chessDrawCell; border.width: 3; border.color: "yellow" }
                        },
                        State {
                            name: "moveAvailable"
                            PropertyChanges { target: chessDrawCell; border.width: 3; border.color: "green" }
                        },
                        State {
                            name: "moveInitial"
                            PropertyChanges { target: chessDrawCell; border.width: 3; border.color: "blue" }
                        },
                        State {
                            name: "moveCapture"
                            PropertyChanges { target: chessDrawCell; border.width: 3; border.color: "red" }
                        }
                    ]
                }
            }
        }

        Component {
            id: cbVerticalMarkers

            Column {
                width: gridSize / 4

                anchors.left: parent.left;
                anchors.top: parent.top;
                anchors.bottom: parent.bottom
                anchors.margins: gridSize / 8

                anchors.topMargin: gridSize * 3 / 4
                spacing: anchors.topMargin / 2

                Repeater {
                    model: 8
                    Text {
                        font.pixelSize: gridSize / 2
                        text: 8 - modelData
                    }
                }
            }
        }

        Component {
            id: cbHorizontalMarkers

            Row {
                height: gridSize / 4

                anchors.bottom: parent.bottom
                anchors.leftMargin: gridSize * 3 / 4
                anchors.left: parent.left
                anchors.margins: gridSize / 8
                spacing: gridSize * 3 / 4

                Repeater {
                    model: ["a", "b", "c", "d", "e", "f", "g", "h"]
                    Text {
                        font.pixelSize: gridSize / 2
                        text: modelData
                    }
                }
            }
        }

        Loader {sourceComponent: cbVerticalMarkers }
        Loader {sourceComponent: cbVerticalMarkers; x: parent.width - gridSize / 2 }
        Loader {sourceComponent: cbHorizontalMarkers }
        Loader {sourceComponent: cbHorizontalMarkers; y: parent.height - gridSize / 2 }
    }

    function selectPiece(chessPiece) {
//        if (chessPiece !== null && chessBoard.selectedChessPiece === chessPiece ) {
//            pieceSelect(null);
//            return;
//        }

        chessBoard.selectedPiece = chessPiece;

        // Reset all squares
        if (chessPiece === null) {
            for (var i = 0; i < cbCells.count; i++) {
                cbCells.itemAt(i).state = "";
            }
            return;
        }

        // Highlight available moves
        for (i = 0; i < cbCells.count; i++) {
            var moveStates = chessPiece.chessLogic.moveAvailableStates(i);
            if (moveStates & ChessTypes.MoveCapture) {
                cbCells.itemAt(i).state = "moveCapture";
            } else
            if (moveStates & ChessTypes.MoveAvailable) {
                cbCells.itemAt(i).state = "moveAvailable";
            } else {
                cbCells.itemAt(i).state = "";
            }
        }

        // Hightlight initial place
        if (chessPiece !== null) {
            cbCells.itemAt(chessPiece.chessLogic.boardPos).state = "moveInitial";
        }
    }

    function placePiece(figure, boardPos){
        var cell = cbCells.itemAt(boardPos);
        if (cell !== null){
            figure.selected.connect(selectPiece);
            figure.x = cell.cx;
            figure.y = cell.cy;
        }
    }
}
