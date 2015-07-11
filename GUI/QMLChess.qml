/*
    Copyright (C) 2015 Vladimir Karlov
*/

import QtQuick 2.0
import QtQuick.Layouts 1.1
import QtQuick.Controls 1.2
import "." as ChessGUI
import ChessLib 1.0

ApplicationWindow {
    id: mainWindow

    minimumWidth: 800
    minimumHeight: 700

    width: minimumWidth
    height: minimumHeight
    visible: true

    title: "QML Chess"

//    menuBar: MenuBar {
//        Menu {
//            title: "File"
//            MenuItem { text: "Open..." }
//            MenuItem { text: "Save..." }
//            MenuItem { text: "Exit" ; onTriggered:  Qt.quit()}
//        }
//    }

    toolBar: ToolBar {
        RowLayout {
            anchors.fill: parent
            Button {
                text: chessGame.started ? "Stop" : "Start";
                onClicked: chessGame.started ? stopGame() : startGame();
            }
            Button {
                text: chessGame.started ? "Save..." : "Load...";
                onClicked: chessGame.started ? saveGame() : loadGame();
            }
            Item {
                Layout.fillWidth: true
                Text {
                    Layout.fillWidth: true
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.horizontalCenter: parent.horizontalCenter
                    visible: chessGame.started
                    text: chessGame.moveColor == ChessTypes.White ?
                              "White Move" : "Black Move"
                    font.bold: true
                    font.pointSize: 14
                    color: chessGame.moveColor == ChessTypes.White ?
                               "white" : "black"
                }
            }
            Button {
                Layout.alignment: Qt.AlignRight
                //visible: chessGame.started
                text: "Prev"
            }
            Button {
                Layout.alignment: Qt.AlignRight
                //visible: chessGame.started
                text: "Next"
            }
        }
    }

    statusBar: StatusBar {
    }

    ChessGame {
        id: chessGame
    }

    RowLayout {
        spacing: 0
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right

        ChessGUI.ChessBoard {
            id: chessBoard
        }

        ColumnLayout {
            spacing: 2
            Layout.alignment: Qt.AlignRight

            ChessGUI.NotationList {
                id: notationList
                Layout.fillWidth: true
                Layout.fillHeight: true

                chessGame: chessGame
            }
        }
    }

    Component.onCompleted: {
        // Just for debug
        //startGame();
    }

    function startGame(){
        console.log("Start game.");
        chessBoard.selectPiece(null);
        chessGame.startNewGame(chessBoard);
    }

    function stopGame(){
        console.log("Stop game.");
        chessBoard.selectPiece(null);
        chessGame.stopGame();
    }
}
