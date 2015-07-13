// Copyright (C) 2015 Vladimir Karlov <vkarlov.work@gmail.com>
// All rights reserved.
//
// Name:        QMLChess.qml
// Date:        2015.07.13
// Author:      Vladimir Karlov
// Description: CHess Game main window

import QtQuick 2.2
import QtQuick.Layouts 1.1
import QtQuick.Controls 1.2
import QtQuick.Dialogs 1.0
import "." as ChessGUI
import ChessLib 1.0

ApplicationWindow {
    id: mainWindow

    minimumWidth: 800
    minimumHeight: 650

    width: minimumWidth
    height: minimumHeight
    visible: true

    title: "QML Chess"

    toolBar: ToolBar {
        RowLayout {
            anchors.fill: parent
            RowLayout {
                id: playControls
                visible: chessGame.state !== ChessTypes.GameOff
                Button {
                    text: "Stop"
                    onClicked: stopGame();
                }
                Button {
                    text: "Save..."
                    onClicked: saveFileDialog.open()
                }

                Item {
                    anchors { top: parent.top; bottom: parent.bottom }
                    Layout.fillWidth: true
                }
                Text {
                    anchors.verticalCenter: parent.verticalCenter
                    visible: chessGame.chessCheck
                    text: "Check!"
                    font { bold: true; pointSize: 14 }
                    color: "red"
                }
                Text {
                    anchors.verticalCenter: parent.verticalCenter
                    visible: chessGame.state === ChessTypes.GameLive
                    text: chessGame.moveColor === ChessTypes.White ?
                              "White Move" : "Black Move"
                    font {bold: true; pointSize: 14 }
                    color: chessGame.moveColor === ChessTypes.White ?
                               "white" : "black"
                }
                Text {
                    anchors.verticalCenter: parent.verticalCenter
                    visible: chessGame.state === ChessTypes.GamePlay
                    text: "Playback"
                    font {bold: true; pointSize: 14 }
                }
                Item {
                    anchors { top: parent.top; bottom: parent.bottom }
                    Layout.fillWidth: true
                }
                Button {
                    Layout.alignment: Qt.AlignRight
                    text: "Prev"
                    enabled: chessGame.hasPrevMove
                    onClicked: chessGame.movePrev()
                }
                Button {
                    Layout.alignment: Qt.AlignRight
                    text: "Next"
                    enabled: chessGame.hasNextMove
                    onClicked: chessGame.moveNext()
                }
            }
            RowLayout {
                id: offControls
                visible: chessGame.state === ChessTypes.GameOff
                Button {
                    text: "Start"
                    onClicked: startGame();
                }
                Button {
                    text: "Load...";
                    onClicked: loadFileDialog.open();
                }
                Item {
                    Layout.fillWidth: true

                }
            }

        }
    }

    statusBar: StatusBar {
    }

    ChessGameplay {
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

    FileDialog {
        id: saveFileDialog
        title: "Save current Chess Game"
        selectExisting: false
        //folder: shortcuts.home
        nameFilters: [ "Chess Game files (*.cgf)", "All files (*)" ]
        onAccepted: {
            chessGame.save(saveFileDialog.fileUrls);
        }
    }

    FileDialog {
        id: loadFileDialog
        title: "Open Chess Game"
        //folder: shortcuts.home
        nameFilters: [ "Chess Game files (*.cgf)", "All files (*)" ]
        onAccepted: {
            chessGame.load(loadFileDialog.fileUrls, chessBoard);
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
