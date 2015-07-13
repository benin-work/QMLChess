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
                    Layout.fillWidth: true
                    Text {
                        Layout.fillWidth: true
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.horizontalCenter: parent.horizontalCenter
                        visible: chessGame.state === ChessTypes.GamePlay
                        text: "Playback"
                        font.bold: true
                        font.pointSize: 14
                    }
                    Text {
                        Layout.fillWidth: true
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.horizontalCenter: parent.horizontalCenter
                        visible: chessGame.state === ChessTypes.GameLive
                        text: chessGame.moveColor === ChessTypes.White ?
                                  "White Move" : "Black Move"
                        font.bold: true
                        font.pointSize: 14
                        color: chessGame.moveColor === ChessTypes.White ?
                                   "white" : "black"
                    }
                }
                Button {
                    Layout.alignment: Qt.AlignRight
                    enabled: chessGame.hasPrevMove
                    text: "Prev"
                    onClicked: chessGame.movePrev()
                }
                Button {
                    Layout.alignment: Qt.AlignRight
                    enabled: chessGame.hasNextMove
                    text: "Next"
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
