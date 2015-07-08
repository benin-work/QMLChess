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
, m_pos(boardPos)
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
            Q_ARG(QVariant, QVariant::fromValue(pos().boardPos())));
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

bool ChessPiece::isMoveAvailable(const int newBoardPos) const
{
    if (isParentPiece(newBoardPos))
        return false;

    return moveAvailable(ChessPos(newBoardPos));
}

bool ChessPiece::isParentPiece(const int boardPos) const
{
    Q_ASSERT(!m_parentPlayer.isNull());

    // Check for parent pieces
    if (m_parentPlayer.toStrongRef()->chessPieceAt(boardPos))
        return true;

    return false;
}

bool ChessPiece::moveDiagonalAvailable(const ChessPos &newPos) const
{
    return false;
}

bool ChessPiece::moveHorVertAvailable(const ChessPos &newPos) const
{
    return false;
}

bool ChessPiece::moveAvailable(const ChessPos & /*newPos*/) const
{
    // Should be called from derived classes
    Q_ASSERT(false);
    return false;
}



