#include <QDebug>
#include <QQmlEngine>
#include <QQmlComponent>

#include "ChessGame.h"
#include "ChessPlayer.h"

ChessGame::ChessGame(QQuickItem *parent /*= 0*/)
: QQuickItem(parent)
, m_moveColor(ChessTypes::White)
{
}

void ChessGame::startNewGame(const QVariant &chessBoard)
{
    qDebug() << "Start new game on board: " << chessBoard;

    QQuickItem* chessBoardObject = qobject_cast<QQuickItem*>(chessBoard.value<QQuickItem*>());

    // Prepeare players
    m_whitePlayer.reset(new ChessPlayer(ChessTypes::White));
    m_blackPlayer.reset(new ChessPlayer(ChessTypes::Black));

    m_whitePlayer->setOpponentPlayer(m_blackPlayer);
    m_blackPlayer->setOpponentPlayer(m_whitePlayer);

    m_whitePlayer->fillInitialPieces(chessBoardObject);
    m_blackPlayer->fillInitialPieces(chessBoardObject);

    // Set initial move
    setMoveColor(ChessTypes::White);
}

void ChessGame::alternateMove()
{
    setMoveColor(moveColor() == ChessTypes::White ?
        ChessTypes::Black : ChessTypes::White);
}

ChessTypes::PieceColor ChessGame::moveColor() const
{
    return m_moveColor;
}

void ChessGame::setMoveColor(ChessTypes::PieceColor moveColor)
{
    if (m_moveColor == moveColor)
        return;

    m_moveColor = moveColor;
    emit moveColorChanged(moveColor);
}
