// Copyright (C) 2015 Vladimir Karlov <vkarlov.work@gmail.com>
// All rights reserved.
//
// Name:        ChessPiece.qml
// Date:        2015.07.13
// Author:      Vladimir Karlov
// Description: Graphical representation of Chess Piece

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

    // Hower on the ground
    border.color: "blue"
    border.width:{
        (chessLogic != null && chessLogic.enable &&
               chessPiece.z == 0 && ma.containsMouse) ? 2: 0
    }

    property ChessPieceLogic chessLogic: null
    property int initPosX: 0;
    property int initPosY: 0;

    signal selected(var piece)

    onChessLogicChanged: {
        if (chessLogic != null)
        {
            // Set main image
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

            chessLogic.boardPosChanged.connect(boardPosChanged);
        }
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

        // Transit events to the board
        //onPositionChanged: mouse.accepted = false;
    }

    Drag.active: ma.drag.active
    Drag.hotSpot.x: pieceSize / 2
    Drag.hotSpot.y: pieceSize / 2

    onParentChanged: {
        if (parent != null)
        {
            ma.drag.minimumX = parent.x
            ma.drag.minimumY = parent.y
            ma.drag.maximumX = parent.width - width
            ma.drag.maximumY = parent.height - height
        }
    }

    Behavior on x {
        NumberAnimation { easing.type: Easing.InOutQuad; duration: 250 }
    }

    Behavior on y {
        NumberAnimation { easing.type: Easing.InOutQuad; duration: 250 }
    }

    function boardPosChanged(newBoardPos) {
        if (chessPiece.parent != null)
            chessPiece.parent.placePiece(chessPiece, newBoardPos);
    }

    function tryToMove(targetPos) {
        var moveState = chessLogic.moveAvailableStates(targetPos.boardPos);
        if (moveState & (ChessTypes.MoveAvailable | ChessTypes.MoveCapture)) {
            chessPiece.selected(null);
            chessPiece.chessLogic.move(targetPos.boardPos);
        } else {
            console.debug("Move unavailable...");
            return false;
        }
        return true;
    }
}
