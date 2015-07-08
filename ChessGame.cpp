#include <QDebug>
#include <QQmlEngine>
#include <QQmlComponent>

#include "ChessGame.h"
#include "ChessPlayer.h"

ChessGame::ChessGame(QQuickItem *parent /*= 0*/)
: QQuickItem(parent)
{
}

void ChessGame::startNewGame(const QVariant &chessBoard)
{
    qDebug() << "Start new game on board: " << chessBoard;

    QQuickItem* chessBoardObject = qobject_cast<QQuickItem*>(chessBoard.value<QQuickItem*>());

    m_whitePlayer.reset(new ChessPlayer(ChessPiece::White));
    m_blackPlayer.reset(new ChessPlayer(ChessPiece::Black));

    m_whitePlayer->setOppositPlayer(m_blackPlayer);
    m_blackPlayer->setOppositPlayer(m_whitePlayer);

    m_whitePlayer->fillInitialPieces(chessBoardObject);
    m_blackPlayer->fillInitialPieces(chessBoardObject);
}

