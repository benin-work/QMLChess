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
        addChessPiece(ChessPiecePtr(new ChessPiecePawn(m_color, chessBoard, dxPos++)));

    // Pieces
    dxPos = color() == ChessTypes::White ? 56 : 0;
    addChessPiece(ChessPiecePtr(new ChessPieceRook(m_color, chessBoard, dxPos++)));
    addChessPiece(ChessPiecePtr(new ChessPieceKnight(m_color, chessBoard, dxPos++)));
    addChessPiece(ChessPiecePtr(new ChessPieceBishop(m_color, chessBoard, dxPos++)));
    addChessPiece(ChessPiecePtr(new ChessPieceQueen(m_color, chessBoard, dxPos++)));
    addChessPiece(ChessPiecePtr(new ChessPieceKing(m_color, chessBoard, dxPos++)));
    addChessPiece(ChessPiecePtr(new ChessPieceBishop(m_color, chessBoard, dxPos++)));
    addChessPiece(ChessPiecePtr(new ChessPieceKnight(m_color, chessBoard, dxPos++)));
    addChessPiece(ChessPiecePtr(new ChessPieceRook(m_color, chessBoard, dxPos++)));
}

ChessPiecePtr ChessPlayer::chessPieceAt(const int boardPos) const
{
    foreach(auto chessPiece, m_listPieces)
        if (chessPiece->boardPos() == boardPos)
            return chessPiece;

    return ChessPiecePtr();
}

ChessMovePtr ChessPlayer::lastMove() const
{
    return m_lastMove;
}

void ChessPlayer::movePiece(ChessMovePtr chessMove)
{
    auto movePiece = chessPieceAt(chessMove->oldPos());
    Q_ASSERT(movePiece);

    if (movePiece)
    {
        movePiece->setBoardPos(chessMove->newPos());
    }
}

void ChessPlayer::setLastMove(ChessMovePtr lastMove)
{
    m_lastMove = lastMove;
}

void ChessPlayer::chessMoved(ChessMovePtr chessMove)
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

        auto pieceCapture = opponentPlayer()->chessPieceAt(boaradPos);
        Q_ASSERT(pieceCapture);

        chessMove->setPieceOperationType(pieceCapture->type());
        opponentPlayer()->removeChessPiece(boaradPos);
    }

    // Pawn promotion check
    if (chessMove->moveStates() & ChessTypes::MovePawnPromotion)
    {
        // Capture the figure by Pawn ONLY one step behind
        Q_ASSERT(chessMove->pieceType() == ChessTypes::Pawn);

        auto promotePawn = chessPieceAt(chessMove->newPos());
        if (promotePawn)
        {
            removeChessPiece(promotePawn->pos());

            // TODO in GUI select figure
            ChessPiecePtr newPiece(
                        new ChessPieceQueen(color(), promotePawn->m_chessBoardGUI, promotePawn->pos()));
            addChessPiece(newPiece);
            chessMove->setPieceOperationType(newPiece->type());
        }
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

void ChessPlayer::addChessPiece(ChessPiecePtr newChessPiece)
{
    newChessPiece->m_parentPlayer = sharedFromThis();
    m_listPieces.append(newChessPiece);

    QObject::connect(newChessPiece.data(), SIGNAL(moved(ChessMovePtr)),
                     this, SLOT(chessMoved(ChessMovePtr)));
    QObject::connect(this, SIGNAL(enableChanged(bool)),
                     newChessPiece.data(), SLOT(setEnable(bool)));
}

ChessPiecePtr ChessPlayer::removeChessPiece(const int boardPos)
{
    auto capturedPiece = chessPieceAt(boardPos);
    Q_ASSERT(!capturedPiece.isNull());

    m_listPieces.removeAll(capturedPiece);

    return capturedPiece;
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



