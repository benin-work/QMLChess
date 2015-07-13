TEMPLATE = app

QT += quick qml

HEADERS += \
    src/ChessGame.h \
    src/ChessPlayer.h \
    src/ChessPiece.h \
    src/ChessPieces.h \
    src/ChessPos.h \
    src/ChessTypes.h \
    src/ChessMove.h \
    src/ChessGameplay.h

SOURCES += \
    src/main.cpp \
    src/ChessGame.cpp \
    src/ChessPlayer.cpp \
    src/ChessPiece.cpp \
    src/ChessPieces.cpp \
    src/ChessPos.cpp \
    src/ChessTypes.cpp \
    src/ChessMove.cpp \
    src/ChessGameplay.cpp

RESOURCES += QMLChess.qrc

OTHER_FILES = ./QMLChess.qml \
              ./gui/*.qml

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

isEmpty(TARGET_EXT) {
    win32 {
        TARGET_CUSTOM_EXT = .exe
    }
} else {
    TARGET_CUSTOM_EXT = $${TARGET_EXT}
}

win32 {
    DEPLOY_COMMAND = windeployqt
}

CONFIG( debug, debug|release ) {
    # debug
    DEPLOY_TARGET = $$shell_quote($$shell_path($${OUT_PWD}/debug/$${TARGET}$${TARGET_CUSTOM_EXT}))
} else {
    # release
    DEPLOY_TARGET = $$shell_quote($$shell_path($${OUT_PWD}/release/$${TARGET}$${TARGET_CUSTOM_EXT}))
}

QMAKE_POST_LINK = $${DEPLOY_COMMAND} $${DEPLOY_TARGET}

#  # Uncomment the following line to help debug the deploy command when running qmake
#  warning($${DEPLOY_COMMAND} $${DEPLOY_TARGET})

