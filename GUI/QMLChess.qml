/*
    Copyright (C) 2015 Vladimir Karlov
*/

import QtQuick 2.0
import QtQuick.Layouts 1.1
import QtQuick.Controls 1.1
import "." as ChessGUI
import ChessLib 1.0

Item {
    id: mainWindow
    height: 768
    width: 1024

    ChessGame {
        id: chessMainGame
    }

    ColumnLayout {
        spacing: 0
        anchors.fill: parent
        anchors.left: parent.left
        anchors.top: parent.top

        Rectangle {
            id: toolBar
            height: 50
            anchors.top: parent.top
            width: parent.width
            color: "#000000"

            RowLayout {
                anchors.left: parent.left
                anchors.leftMargin: 10
                anchors.verticalCenter: parent.verticalCenter
                anchors.top: parent.top
                spacing: 10

                Button {
                    text: "Start"
                    onClicked: startGame();
                }

                Button {
                    text: "Load"
                    //onClicked: chessBoardMyObject.getInfo()
                }

                Text {
                    text: chessMainGame.moveColor == ChessTypes.White ?
                              "White Move" : "Black Move"
                    color: "white"
                }
            }
        }

        RowLayout {
            id: chessBoardContainer
            Layout.alignment: Qt.AlignTop

            ChessGUI.ChessBoard {
                id: chessBoard
                objectName: "chessBoard"
            }
        }
    }

    Component.onCompleted: {
        // Just for debug
        startGame();
    }

    function startGame(){
        console.log("Start game.");
        chessBoard.selectPiece(null);
        chessMainGame.startNewGame(chessBoard);
    }
}
