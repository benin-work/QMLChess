TEMPLATE = app

QT += quick qml

HEADERS += \
    ChessGame.h \
    ChessPlayer.h \
    ChessPiece.h \
    ChessPieces.h \
    ChessPos.h

SOURCES += main.cpp \
    ChessGame.cpp \
    ChessPlayer.cpp \
    ChessPiece.cpp \
    ChessPieces.cpp \
    ChessPos.cpp

RESOURCES += \
    QMLChess.qrc \
    ./shared/shared.qrc

OTHER_FILES = QMLChess.qml \
              ./ChessGUI/*.qml \
              ./shared/*.qml \
              ./shared/images/*

Release:DESTDIR = release
Release:OBJECTS_DIR = release/.obj
Release:MOC_DIR = release/.moc
Release:RCC_DIR = release/.rcc
Release:UI_DIR = release/.ui

Debug:DESTDIR = debug
Debug:OBJECTS_DIR = debug/.obj
Debug:MOC_DIR = debug/.moc
Debug:RCC_DIR = debug/.rcc
Debug:UI_DIR = debug/.ui
