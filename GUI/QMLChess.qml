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
    width: 1024
    height: 768
    minimumHeight: 768
    minimumWidth: 1024
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
            ToolButton {
                text: chessGame.started ? "Stop" : "Start";
                onClicked: chessGame.started ? stopGame() : startGame();
            }
            ToolButton {
                visible: !chessGame.started
                text: "Load"
            }
            Text {
                visible: chessGame.started
                text: chessGame.moveColor == ChessTypes.White ?
                          "White Move" : "Black Move"
                font.bold: true
            }
            Item { Layout.fillWidth: true }
//            CheckBox {
//                text: "Enabled"
//                checked: true
//                Layout.alignment: Qt.AlignRight
//            }
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
            objectName: "chessBoard"
        }

        ChessGUI.NotationList {
            Layout.fillWidth: true
            Layout.fillHeight: true
            //Layout.alignment: Qt.AlignRight | Qt.AlignTop
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
