// Copyright (C) 2015 Vladimir Karlov <vkarlov.work@gmail.com>
// All rights reserved.
//
// Name:        ChessGame.cpp
// Date:        2015.07.13
// Author:      Vladimir Karlov

#include <QDebug>
#include <QQmlEngine>
#include <QQmlComponent>

#include "ChessGame.h"
#include "ChessPlayer.h"
#include "ChessMove.h"

ChessGame::ChessGame(QQuickItem *parent /*= 0*/)
: QQuickItem(parent)
, m_moveColor(ChessTypes::White)
, m_state(ChessTypes::GameOff)
{
}

ChessTypes::GameState ChessGame::state() const
{
    return m_state;
}

void ChessGame::clearHistory()
{
    // Presave items,
    // Hack to allow QML remove items from list
    auto movesCopy = m_moves;

    m_moves.clear();
    emit chessMovesChanged(chessMoves());

    movesCopy.clear();
}

void ChessGame::alternateMove()
{
    setMoveColor(moveColor() == ChessTypes::White ?
                     ChessTypes::Black : ChessTypes::White);
}

QSharedPointer<ChessPlayer> ChessGame::chessPlayer(const ChessTypes::Color playerColor)
{
    return playerColor == ChessTypes::White ? m_whitePlayer : m_blackPlayer;
}

ChessTypes::Color ChessGame::moveColor() const
{
    return m_moveColor;
}

void ChessGame::setMoveColor(ChessTypes::Color newMoveColor)
{
    if (m_moveColor == newMoveColor)
        return;

    m_moveColor = newMoveColor;

    m_whitePlayer->setEnable(moveColor() == ChessTypes::White);
    m_blackPlayer->setEnable(moveColor() == ChessTypes::Black);

    emit moveColorChanged(newMoveColor);
}

void ChessGame::moveMade(const ChessMovePtr chessMove)
{
    qDebug() << QString("%1: %2-%3").
        arg(ChessTypes::colorName(chessMove->pieceColor()),
            chessMove->oldPos().name(),
            chessMove->newPos().name());

    Q_ASSERT(moveColor() == chessMove->pieceColor());
    m_moves << chessMove;

    emit chessMovesChanged(chessMoves());

    alternateMove();
}

// Accessors for move list
namespace
{
    typedef QList<ChessMovePtr> MoveList;
    static void mlist_append(QQmlListProperty<ChessMove> *p, ChessMove *v) {
    reinterpret_cast<MoveList *>(p->data)->append(ChessMovePtr(v));
    }
    static int mlist_count(QQmlListProperty<ChessMove> *p) {
        return reinterpret_cast<MoveList *>(p->data)->count();
    }
    static ChessMove* mlist_at(QQmlListProperty<ChessMove> *p, int idx) {
        return reinterpret_cast<MoveList *>(p->data)->at(idx).data();
    }
    static void mlist_clear(QQmlListProperty<ChessMove> *p) {
        return reinterpret_cast<MoveList *>(p->data)->clear();
    }
}

QQmlListProperty<ChessMove> ChessGame::chessMoves()
{
    return QQmlListProperty<ChessMove>(this, &m_moves, &mlist_append, &mlist_count,
                                       &mlist_at, &mlist_clear);
}

void ChessGame::startNewGame(const QVariant &chessBoard)
{
    qDebug() << "Start new game";

    QQuickItem* chessBoardObject = qobject_cast<QQuickItem*>(chessBoard.value<QQuickItem*>());

    stopGame();
    m_whitePlayer->fillInitialPieces(chessBoardObject);
    m_blackPlayer->fillInitialPieces(chessBoardObject);

    QObject::connect(m_whitePlayer.data(), SIGNAL(moveMade(ChessMovePtr)),
               this, SLOT(moveMade(const ChessMovePtr)));
    QObject::connect(m_blackPlayer.data(), SIGNAL(moveMade(ChessMovePtr)),
               this, SLOT(moveMade(const ChessMovePtr)));

    // Clear movement history
    clearHistory();

    // Set initial move
    m_moveColor = ChessTypes::Black; // To trigger setMove
    setMoveColor(ChessTypes::White);

    setState(ChessTypes::GameLive);
}

void ChessGame::stopGame()
{
    // Prepeare players
    m_whitePlayer.reset(new ChessPlayer(ChessTypes::White));
    m_blackPlayer.reset(new ChessPlayer(ChessTypes::Black));

    m_whitePlayer->setOpponentPlayer(m_blackPlayer);
    m_blackPlayer->setOpponentPlayer(m_whitePlayer);

    // Clear movement history
    clearHistory();

    setState(ChessTypes::GameOff);
}

void ChessGame::setState(ChessTypes::GameState newState)
{
    if (m_state == newState)
        return;

    m_state = newState;
    emit stateChanged(newState);

    if (state() == ChessTypes::GameLive)
    {
        m_whitePlayer->setEnable(moveColor() == ChessTypes::White);
        m_blackPlayer->setEnable(moveColor() == ChessTypes::Black);
    } else
    {
        m_whitePlayer->setEnable(false);
        m_blackPlayer->setEnable(false);
    }
}
