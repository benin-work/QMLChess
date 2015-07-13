// Copyright (C) 2015 Vladimir Karlov <vkarlov.work@gmail.com>
// All rights reserved.
//
// Name:        NotationList .qml
// Date:        2015.07.13
// Author:      Vladimir Karlov
// Description: Movement history information

import QtQuick 2.0
import QtQuick.Controls 1.2
import QtQuick.Layouts 1.0
import ChessLib 1.0

Rectangle {
    width: 200
    height: 100

    color: "transparent"

    property ChessGameplay chessGame: null

    GridView {
        id: mainList

        anchors.fill: parent
        anchors.margins: 5

        //focus: true

        model: chessGame.chessMoves
        delegate: moveDelegate

        cellWidth: chessBoard.gridSize * 1.5
        cellHeight: chessBoard.gridSize / 2

        width: cellWidth * 2

        highlight: Rectangle { color: "#FBD19C" ; radius: 4 }

        header: Item {
            id: listHeader
            width: parent.width
            height: mainList.cellHeight - 5

            Rectangle {
                anchors.fill: parent
                color: "transparent"

                Text {
                    anchors.left: parent.left
                    renderType: Text.NativeRendering
                    font.pixelSize: chessBoard.gridSize / 3
                    text: "Movement notation:"
                }
            }
        }

        Component {
            id: moveDelegate
            Item {
                width: mainList.cellWidth - 2
                height: mainList.cellHeight - 2
                Rectangle {
                    anchors.fill: parent

                    color: "transparent"
                    border.color: "black"
                    border.width: ma.containsMouse ? 2 : 0
                    radius: 4

                    Text {
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.left: parent.left
                        anchors.margins: 5

                        font.pixelSize: chessBoard.gridSize / 4
                        text: (model.index % 2) === 0 ?
                                  ("<b>" + ((model.index)/2 + 1) + ".</b> " + model.modelData.name) : model.modelData.name
                    }
                }

                MouseArea {
                    id: ma
                    anchors.fill: parent
                    hoverEnabled: true;
                    onClicked: {
                        chessGame.moveAt(model.index);
                        mainList.currentIndex = model.index
                    }
                }
            }
        }


        Connections {
            target: chessGame
            onActiveMoveChanged: { mainList.currentIndex = activeMove }
        }

        onCurrentIndexChanged: {
            //console.log("Current index changed to:" + currentIndex + " ActiveMove: " + chessGame.activeMove);
            //notationList.positionViewAtIndex(currentIndex, GridView.Contain);
        }
    }
}
