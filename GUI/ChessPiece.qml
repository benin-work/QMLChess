import QtQuick 2.0
import ChessLib 1.0

Rectangle {
    id: chessPiece

    property int pieceSize: 64
    width: pieceSize
    height: pieceSize

    z: 0;

    Image {
        id: chessImg
        fillMode: Image.PreserveAspectFit
    }

    color: "transparent"
    //border.color: "lightblue"
    //border.width: ma.containsMouse ? 2 : 0

    property ChessPieceLogic chessLogic: null
    property int initPosX: 0;
    property int initPosY: 0;

    signal selected(var piece)

    onChessLogicChanged: {
        var strColor = chessLogic.color === ChessTypes.White ?
                    "White" : "Black";
        var strType = "Pawn";
        switch(chessLogic.type){
            case ChessTypes.Bishop: strType = "Bishop"; break;
            case ChessTypes.Rook: strType = "Rook"; break;
            case ChessTypes.Knight: strType = "Knight"; break;
            case ChessTypes.Queen: strType = "Queen"; break;
            case ChessTypes.King: strType = "King"; break;
        }

        chessImg.source = "images/" + strColor + strType + ".png";
    }

    MouseArea {
        id: ma

        enabled: chessLogic !== null ? chessLogic.enable : false

        hoverEnabled: true

        anchors.fill: parent
        drag.target: parent

        onPressed: {
            chessPiece.z = 1;
            initPosX = chessPiece.x;
            initPosY = chessPiece.y;
            chessPiece.selected(chessPiece);
        }

        onReleased: {
            chessPiece.z = 0;

            function returnPiece() {
                chessPiece.x = initPosX;
                chessPiece.y = initPosY;
            }

            if (chessLogic !== null && chessPiece.Drag.target !== null) {
                if (!tryToMove(chessPiece.Drag.target))
                    returnPiece();
            } else {
                returnPiece();
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

    function tryToMove(targetPos) {
        var moveState = chessLogic.moveAvailableState(targetPos.boardPos);
        if (moveState === ChessTypes.MoveAvailable) {
            makeMove(targetPos)
        } else if (moveState === ChessTypes.MoveCapture) {
            makeCapture(targetPos)
        } else {
            return false;
        }
        return true;
    }

    function makeMove(targetPos) {
        chessPiece.x = targetPos.cx;
        chessPiece.y = targetPos.cy;
        chessPiece.selected(null);
        chessPiece.chessLogic.move(targetPos.boardPos);
    }

    function makeCapture(targetPos) {
        chessPiece.x = targetPos.cx;
        chessPiece.y = targetPos.cy;
        chessPiece.selected(null);
        chessPiece.chessLogic.capture(targetPos.boardPos);
    }
}
