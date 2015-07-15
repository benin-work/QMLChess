// Copyright (C) 2015 Vladimir Karlov <vkarlov.work@gmail.com>
// All rights reserved.
//
// Name:        main.cpp
// Date:        2015.07.13
// Author:      Vladimir Karlov
// Description: Chess Game another one implementation

#include <QDir>
#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "../version.h"

#include "ChessTypes.h"
#include "ChessMove.h"
#include "ChessGameplay.h"
#include "ChessPiece.h"

int main(int argc, char* argv[])
{
    QGuiApplication app(argc,argv);
    app.setApplicationName(QFileInfo(app.applicationFilePath()).baseName());

    qmlRegisterSingletonType("Native", 1, 0, "AppInfo", appVersionSingletonProvider);

    qmlRegisterType<ChessTypes>("ChessLib", 1,0, "ChessTypes");
    qmlRegisterType<ChessMove>("ChessLib", 1,0, "ChessMove");
    qmlRegisterType<ChessPiece>("ChessLib", 1,0, "ChessPieceLogic");
    qmlRegisterType<ChessGameplay>("ChessLib", 1,0, "ChessGameplay");

    QQmlApplicationEngine engine;
    engine.load(QUrl("qrc:///gui/QMLChess.qml"));

    return app.exec();
}
