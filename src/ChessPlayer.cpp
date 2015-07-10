#include <QDebug>
#include <QQmlEngine>
#include <QQmlComponent>

#include "ChessPlayer.h"
#include "ChessPieces.h"
#include "ChessMove.h"


ChessPlayer::ChessPlayer(const ChessTypes::Color playerColor)
: QObject()
, m_enable(false)
, m_color(playerColor)
{
}

ChessPlayer::~ChessPlayer()
{
    qDebug() << QString("%1 player destroyed").arg(ChessTypes::colorName(color()));
}

void ChessPlayer::fillInitialPieces(QQuickItem* chessBoard)
{
    qDebug() << "Fill initial pieces";

    Q_ASSERT(chessBoard);

    m_listPieces.clear();

    // Pawns
    int dxPos = color() == ChessTypes::White ? 48 : 8;
    for(int i = 0; i < 8; i++)
        addChessPiece(QSharedPointer<ChessPiece>(new ChessPiecePawn(m_color, chessBoard, dxPos++)));

    // Pieces
    dxPos = color() == ChessTypes::White ? 56 : 0;
    addChessPiece(QSharedPointer<ChessPiece>(new ChessPieceRook(m_color, chessBoard, dxPos++)));
    addChessPiece(QSharedPointer<ChessPiece>(new ChessPieceKnight(m_color, chessBoard, dxPos++)));
    addChessPiece(QSharedPointer<ChessPiece>(new ChessPieceBishop(m_color, chessBoard, dxPos++)));
    addChessPiece(QSharedPointer<ChessPiece>(new ChessPieceQueen(m_color, chessBoard, dxPos++)));
    addChessPiece(QSharedPointer<ChessPiece>(new ChessPieceKing(m_color, chessBoard, dxPos++)));
    addChessPiece(QSharedPointer<ChessPiece>(new ChessPieceBishop(m_color, chessBoard, dxPos++)));
    addChessPiece(QSharedPointer<ChessPiece>(new ChessPieceKnight(m_color, chessBoard, dxPos++)));
    addChessPiece(QSharedPointer<ChessPiece>(new ChessPieceRook(m_color, chessBoard, dxPos++)));
}

QSharedPointer<ChessPiece> ChessPlayer::chessPieceAt(const int boardPos) const
{
    foreach(auto chessPiece, m_listPieces)
        if (chessPiece->boardPos() == boardPos)
            return chessPiece;

    return QSharedPointer<ChessPiece>();
}

QSharedPointer<ChessMove> ChessPlayer::lastMove() const
{
    return m_lastMove;
}

void ChessPlayer::setLastMove(QSharedPointer<ChessMove> lastMove)
{
    m_lastMove = lastMove;
}

void ChessPlayer::chessMoved(QSharedPointer<ChessMove> chessMove)
{
    // Capture figure from opponent
    if (chessMove->moveStates() & ChessTypes::MoveCapture)
    {
        int boaradPos(chessMove->newPos());

        if (chessMove->moveStates() & ChessTypes::MoveEnPassant)
        {
            // Capture the figure by Pawn ONLY one step behind
            Q_ASSERT(chessMove->pieceType() == ChessTypes::Pawn);
            boaradPos = ChessPos(chessMove->oldPos().row(), chessMove->newPos().col());
        }

        opponentPlayer()->removeChessPiece(boaradPos);
    }

    setLastMove(chessMove);

    emit madeMove(chessMove);
}

void ChessPlayer::setEnable(bool enable)
{
    if (m_enable == enable)
        return;

    m_enable = enable;
    emit enableChanged(enable);
}

void ChessPlayer::addChessPiece(QSharedPointer<ChessPiece> newChessPiece)
{
    newChessPiece->m_parentPlayer = sharedFromThis();
    m_listPieces.append(newChessPiece);

    QObject::connect(newChessPiece.data(), SIGNAL(moved(QSharedPointer<ChessMove>)),
                     this, SLOT(chessMoved(QSharedPointer<ChessMove>)));

    QObject::connect(this, SIGNAL(enableChanged(bool)),
                     newChessPiece.data(), SLOT(setEnable(bool)));
}

void ChessPlayer::removeChessPiece(const int boardPos)
{
    auto capturedPiece = chessPieceAt(boardPos);

    Q_ASSERT(!capturedPiece.isNull());

    m_listPieces.removeAll(capturedPiece);
}

const ChessTypes::Color ChessPlayer::color() const
{
    return m_color;
}

bool ChessPlayer::enable() const
{
    return m_enable;
}

void ChessPlayer::setOpponentPlayer(QSharedPointer<ChessPlayer> opponentPlayer)
{
    m_opponentPlayer = opponentPlayer;
}

QSharedPointer<ChessPlayer> ChessPlayer::opponentPlayer()
{
    return m_opponentPlayer.toStrongRef();
}



