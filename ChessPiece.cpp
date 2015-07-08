#include <QDebug>
#include <QQmlEngine>
#include <QQmlApplicationEngine>
#include <QQmlComponent>
#include <QMetaObject>

#include "ChessPiece.h"
#include "ChessPlayer.h"

ChessPiece::ChessPiece(QObject *parent /*=Q_NULLPTR*/)
: QObject(parent)
{
}

ChessPiece::ChessPiece(const ChessPiece::PieceColor pieceColor,
                       const ChessPiece::PieceType pieceType,
                       QQuickItem* chessBoard, const int boardPos /*=0*/)
: QObject()
, m_chessPieceGUI(nullptr)
, m_chessBoardGUI(chessBoard)
, m_color(pieceColor)
, m_type(pieceType)
, m_boardPos(boardPos)
{
    Q_ASSERT(chessBoard);

    QQmlEngine* engine = QtQml::qmlEngine(m_chessBoardGUI);

    QQmlComponent component(engine, QUrl("qrc:///QMLChess/ChessGUI/ChessPiece.qml"));
    m_chessPieceGUI = qobject_cast<QQuickItem*>(component.create());

    if (m_chessPieceGUI != Q_NULLPTR)
    {
        m_chessPieceGUI->setParentItem(m_chessBoardGUI);
        m_chessPieceGUI->setProperty("chessPieceLogic", QVariant::fromValue(this));

        QMetaObject::invokeMethod(m_chessBoardGUI, "placePiece",
            Q_ARG(QVariant,  QVariant::fromValue(m_chessPieceGUI)),
            Q_ARG(QVariant, QVariant::fromValue(m_boardPos)));
    }
}

ChessPiece::~ChessPiece()
{
    delete m_chessPieceGUI;
}

const ChessPiece::PieceColor ChessPiece::color() const
{
    return m_color;
}

const ChessPiece::PieceType ChessPiece::type() const
{
    return m_type;
}

bool ChessPiece::isMoveAvailable(const int newBoardPos) const
{
    return moveAvailable(newBoardPos);
}

const int ChessPiece::boardPos() const
{
    return m_boardPos;
}

void ChessPiece::setBoardPos(const int pos)
{
    m_boardPos = pos;
}

const int ChessPiece::rowFromPos(const int boardPos)
{
    return boardPos / 8;
}

const int ChessPiece::colFromPos(const int boardPos)
{
    return boardPos % 8;
}

bool ChessPiece::moveAvailable(const int /*newBoardPos*/) const
{
    // Should be called from derived classes
    Q_ASSERT(false);
    return false;
}



