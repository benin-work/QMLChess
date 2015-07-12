#include "ChessGameplay.h"
#include "ChessPlayer.h"

ChessGameplay::ChessGameplay(QQuickItem* parent /*=0*/)
: ChessGame(parent)
{

}

void ChessGameplay::madeMove(const ChessMovePtr chessMove)
{
    ChessGame::madeMove(chessMove);

//    m_activeMoveIter = m_moves;
//    m_activeMoveIter.toBack();

    setActiveMove(m_moves.length() - 1);
}

int ChessGameplay::activeMove() const
{
    return m_activeMove;
}

void ChessGameplay::setActiveMove(int activeMove)
{
    if (m_activeMove == activeMove)
        return;

    m_activeMove = activeMove;

    emit activeMoveChanged(activeMove);
    emit hasPrevMoveChanged(hasPrevMove());
    emit hasNextMoveChanged(hasNextMove());
}

void ChessGameplay::movePrev()
{
    if (!hasPrevMove())
        return;

    ChessMovePtr chessMove(m_moves.at(activeMove()));
    Q_ASSERT(chessMove);
    setActiveMove(activeMove() - 1);

    chessPlayer(chessMove->pieceColor())->movePrev(chessMove);
}

void ChessGameplay::moveNext()
{
    if (!hasNextMove())
        return;

    setActiveMove(activeMove() + 1);
    ChessMovePtr chessMove(m_moves.at(activeMove()));
    Q_ASSERT(chessMove);

    chessPlayer(chessMove->pieceColor())->moveNext(chessMove);
}

void ChessGameplay::moveAt(const int moveIndex)
{
    if (moveIndex > m_moves.length() || moveIndex < 0)
        return;

    while (moveIndex > activeMove())
        moveNext();
    while (moveIndex < activeMove())
        movePrev();
}

bool ChessGameplay::hasNextMove() const
{
    return !m_moves.empty() && activeMove() < m_moves.length() - 1;
}

bool ChessGameplay::hasPrevMove() const
{
    return !m_moves.empty() && activeMove() >= 0;
}

