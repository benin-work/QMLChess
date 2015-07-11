import QtQuick 2.0
import QtQuick.Controls 1.2
import QtQuick.Layouts 1.0
import ChessLib 1.0

Rectangle {
    width: 200
    height: 100

    property ChessGame chessGame: null

//    ListModel {
//        id: libraryModel
//        ListElement {
//            num: "1"
//            black: "e2"
//            white: "e4"
//        }
//    }

//    TableView {
//        alternatingRowColors: false
//        anchors.fill: parent

//        TableViewColumn {
//            role: "num"
//            title: "#"
//            //width: 100
//        }
//        TableViewColumn {
//            role: "white"
//            title: "White"
//            //width: 100
//        }
//        TableViewColumn {
//            role: "black"
//            title: "Black"
//            //width: 200
//        }
//        model: libraryModel
//    }

//    ListModel {
//        id: movesModel
//        ListElement {
//            pieceColor: 1
//            move: "e2"
//        }
//    }

    Component {
        id: moveDelegate
        //Text { text: model.modelData.pieceColor + " " + model.modelData.pieceType}
        Text { text: model.modelData.name}
    }

    ListView {
        id: mainList
        anchors.fill: parent
        model: chessGame.chessMoves
        //model: movesModel
        delegate: moveDelegate
        focus: true
    }

    Component.onCompleted:
    {
        //for(var i = 0; i < chessGame.chessMoves.Count; i++)
    }

}
