import QtQuick 2.0
import ChessLib 1.0

Rectangle {
    id: chessPiece

    property int pieceSize: 64
    width: pieceSize
    height: pieceSize

    Image {
        id: chessImg
        fillMode: Image.PreserveAspectFit
    }

    color: "transparent"
    //border.color: "lightblue"
    //border.width: ma.containsMouse ? 2 : 0

    property ChessPieceLogic chessPieceLogic: null
    property int initPosX: 0;
    property int initPosY: 0;

    signal selected(var piece)
    signal moved(var piece)

    onChessPieceLogicChanged: {
        console.debug("color: ", chessPieceLogic.color, "type: ", chessPieceLogic.type);
        var strColor =
                chessPieceLogic.color === ChessPieceLogic.White ? "White" : "Black";
        var strType = "Pawn";
        switch(chessPieceLogic.type){
            case ChessPieceLogic.Bishop: strType = "Bishop"; break;
            case ChessPieceLogic.Rock: strType = "Rock"; break;
            case ChessPieceLogic.Knight: strType = "Knight"; break;
            case ChessPieceLogic.Queen: strType = "Queen"; break;
            case ChessPieceLogic.King: strType = "King"; break;
        }

        chessImg.source = "images/" + strColor + strType + ".png";
    }

    MouseArea {
        id: ma

        hoverEnabled: true

        anchors.fill: parent
        drag.target: parent

        onPressed: {
            console.debug("Chess piece pressed ", chessPiece);

            initPosX = chessPiece.x;
            initPosY = chessPiece.y;
            chessPiece.selected(chessPiece);
        }

        onReleased: {
            console.debug("Chess piece released ", chessPiece);

            if (chessPieceLogic !== null) {
                if (chessPiece.Drag.target !== null &&
                        chessPieceLogic.isMoveAvailable(chessPiece.Drag.target.boardPos)) {
                    makeMove(chessPiece.Drag.target)
                } else {
                    chessPiece.x = initPosX;
                    chessPiece.y = initPosY;
                }
            }
        }
    }

    Drag.active: ma.drag.active
    Drag.hotSpot.x: pieceSize / 2
    Drag.hotSpot.y: pieceSize / 2

    onParentChanged: {
        ma.drag.minimumX = parent.x
        ma.drag.minimumY = parent.y
        ma.drag.maximumX = parent.width - width
        ma.drag.maximumY = parent.height - height
    }

    Behavior on x {
        NumberAnimation { easing.type: Easing.InOutQuad; duration: 250 }
    }

    Behavior on y {
        NumberAnimation { easing.type: Easing.InOutQuad; duration: 250 }
    }

    function makeMove(targetPos) {
        chessPiece.x = targetPos.cx;
        chessPiece.y = targetPos.cy;
        chessPiece.chessPieceLogic.boardPos = targetPos.boardPos;
        chessPiece.selected(null);
        chessPiece.moved(chessPiece);
    }
}
