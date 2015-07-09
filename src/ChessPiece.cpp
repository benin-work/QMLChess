#include <QDebug>
#include <QQmlEngine>
#include <QQmlApplicationEngine>
#include <QQmlComponent>
#include <QMetaObject>

#include "ChessPiece.h"
#include "ChessPlayer.h"

namespace Utils
{
    // Fast implementation of signum (-1, 0, 1)
    template <typename T> int sign(T val) {
        return (T(0) < val) - (val < T(0));
    }
}

ChessPiece::ChessPiece(QObject *parent /*=Q_NULLPTR*/)
: QObject(parent)
{
}

ChessPiece::ChessPiece(const ChessTypes::PieceColor pieceColor,
                       const ChessTypes::PieceType pieceType,
                       QQuickItem* chessBoard, const int boardPos /*=0*/)
: QObject()
, m_chessPieceGUI(nullptr)
, m_chessBoardGUI(chessBoard)
, m_color(pieceColor)
, m_type(pieceType)
, m_pos(boardPos)
{
    Q_ASSERT(chessBoard);

    QQmlEngine* engine = QtQml::qmlEngine(m_chessBoardGUI);

    QQmlComponent component(engine, QUrl("qrc:///ChessGUI/ChessPiece.qml"));
    m_chessPieceGUI = qobject_cast<QQuickItem*>(component.create());

    if (m_chessPieceGUI != Q_NULLPTR)
    {
        m_chessPieceGUI->setParentItem(m_chessBoardGUI);
        m_chessPieceGUI->setProperty("chessPieceLogic", QVariant::fromValue(this));

        QMetaObject::invokeMethod(m_chessBoardGUI, "placePiece",
            Q_ARG(QVariant,  QVariant::fromValue(m_chessPieceGUI)),
            Q_ARG(QVariant, QVariant::fromValue(pos().boardPos())));
    }
}

ChessPiece::~ChessPiece()
{
    delete m_chessPieceGUI;
}

const ChessTypes::PieceColor ChessPiece::color() const
{
    return m_color;
}

const ChessTypes::PieceType ChessPiece::type() const
{
    return m_type;
}

const int ChessPiece::boardPos() const
{
    return pos().boardPos();
}

void ChessPiece::setBoardPos(const int newBoardPos)
{
    if (pos().boardPos() == newBoardPos)
        return;

    qDebug() << QString("Piece move: %1-%2").arg(pos().chessPosName(), ChessPos(newBoardPos).chessPosName());

    m_pos.setBoardPos(newBoardPos);
    emit boardPosChanged(newBoardPos);
}

const ChessPos &ChessPiece::pos() const
{
    return m_pos;
}

bool ChessPiece::isParentPiece(const int boardPos) const
{
    Q_ASSERT(!m_parentPlayer.isNull());

    auto parentPlayer = m_parentPlayer.toStrongRef();

    // Check for parent pieces
    if (parentPlayer->chessPieceAt(boardPos))
        return true;

    return false;
}

bool ChessPiece::isOpponentPiece(const int boardPos) const
{
    Q_ASSERT(!m_parentPlayer.isNull());

    auto opponentPlayer = m_parentPlayer.toStrongRef()->opponentPlayer();

    // Check for parent pieces
    if (opponentPlayer->chessPieceAt(boardPos))
        return true;

    return false;
}

ChessPiece::MoveState ChessPiece::moveAvailableState(const int newBoardPos) const
{
    if (isParentPiece(newBoardPos))
        return ChessPiece::MoveNotAvailable;

    return moveAvailable(ChessPos(newBoardPos));
}

ChessPiece::MoveState ChessPiece::moveThroughAvailable(const ChessPos &newPos) const
{
    // Check transit for accupated squares
    const int colMove = Utils::sign(newPos.col() - pos().col());
    const int rowMove = Utils::sign(newPos.row() - pos().row());
    int row = pos().row();
    int col = pos().col();
    while ((colMove == 0 || (col += colMove) != newPos.col()) &&
           (rowMove == 0 || (row += rowMove) != newPos.row()))
    {
        ChessPos chessPos(row, col);
        if (isParentPiece(chessPos.boardPos()) ||
            isOpponentPiece(chessPos.boardPos()))
            return ChessPiece::MoveNotAvailable;
    }

    // Check capture
    if (isOpponentPiece(newPos.boardPos()))
        return ChessPiece::MoveCapture;

    return ChessPiece::MoveAvailable;
}

ChessPiece::MoveState ChessPiece::moveAvailable(const ChessPos & /*newPos*/) const
{
    // Should be called from derived classes
    Q_ASSERT(false);
    return ChessPiece::MoveNotAvailable;
}



