import QtQuick 2.0
import ChessLib 1.0
import "." as ChessGUI

// ChessBoard with markup

Item {
    id: chessBoard
    property int gridSize: 64
    width: gridSize * 8 + gridSize // 8 cells + markers
    height: width
    x: 0
    y: 0

    property ChessPiece selectedChessPiece: null

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
                        color: ((Math.floor(index / 8) % 2) === 0) ?
                             (index % 2  === 1 ? "#D18B47" : "#FFCE9E") :
                             (index % 2  === 0 ? "#D18B47" : "#FFCE9E")

                        border.color: "yellow"
                        border.width: cbCellMa.containsMouse ? 3 : 0

                        MouseArea {
                            id: cbCellMa
                            anchors.fill: parent

                            hoverEnabled: selectedChessPiece != null

                            onClicked: {
                                if (selectedChessPiece != null) {
                                    if (selectedChessPiece.chessPieceLogic.moveAvailableState(cbCellTarget.boardPos) === ChessPieceLogic.MoveAvailable) {
                                        console.log("Moving chessPiece at pos:", cbCellTarget.boardPos);
                                        selectedChessPiece.makeMove(cbCellTarget);
                                    } else {
                                        pieceSelect(null);
                                    }
                                }
                            }
                        }
                    }

//                    property string oldState: ""
//                    onEntered: { oldState = state; state = "moveLookup" }
//                    onExited: { state = oldState; oldState = "" }

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
                width: 16

                anchors.left: parent.left;
                anchors.top: parent.top;
                anchors.bottom: parent.bottom
                anchors.margins: 8

                anchors.topMargin: 48
                spacing: 24

                Repeater {
                    model: 8
                    Text {
                        font.pixelSize: 32
                        text: 8 - modelData
                    }
                }
            }
        }

        Component {
            id: cbHorizontalMarkers

            Row {
                height: 16

                anchors.bottom: parent.bottom
                anchors.leftMargin: 48
                anchors.left: parent.left
                anchors.margins: 8
                spacing: 48

                Repeater {
                    model: ["a", "b", "c", "d", "e", "f", "g", "h"]
                    Text {
                        font.pixelSize: 32
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

    function pieceSelect(chessPiece) {
        console.log("Chess piece selected ON board", chessPiece);

//        if (chessPiece !== null && chessBoard.selectedChessPiece === chessPiece ) {
//            pieceSelect(null);
//            return;
//        }

        chessBoard.selectedChessPiece = chessPiece;

        // Reset all squares
        if (chessPiece === null) {
            for (var i = 0; i < cbCells.count; i++) {
                cbCells.itemAt(i).state = "";
            }
            return;
        }

        // Highlight available moves
        for (var i = 0; i < cbCells.count; i++) {
            switch (chessPiece.chessPieceLogic.moveAvailableState(i)) {
                case ChessPieceLogic.MoveAvailable:
                    cbCells.itemAt(i).state = "moveAvailable";
                    break;
                case ChessPieceLogic.MoveCapture:
                    cbCells.itemAt(i).state = "moveCapture";
                    break;
                default:
                    cbCells.itemAt(i).state = "";
            }
        }

        // Hightlight initial place
        if (chessPiece !== null) {
            cbCells.itemAt(chessPiece.chessPieceLogic.boardPos).state = "moveInitial";
        }
    }

    function placePiece(figure, boardPos){
        var cell = cbCells.itemAt(boardPos);
        if (cell !== null){
            figure.selected.connect(pieceSelect);
            figure.x = cell.cx;
            figure.y = cell.cy;
        }
    }
}
