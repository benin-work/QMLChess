// Copyright (C) 2015 Vladimir Karlov <vkarlov.work@gmail.com>
// All rights reserved.
//
// Name:        ChessGame.h
// Date:        2015.07.13
// Author:      Vladimir Karlov
// Description: Base game logic (Start/Stop, Turn by turn..)

#ifndef CHESSGAME_H
#define CHESSGAME_H

#include <QQuickItem>
#include <QSharedPointer>

#include "ChessTypes.h"
#include "ChessMove.h"

class ChessPlayer;
class ChessMove;

class ChessGame : public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY(ChessTypes::GameState state READ state WRITE setState NOTIFY stateChanged)
    Q_PROPERTY(ChessTypes::Color moveColor READ moveColor WRITE setMoveColor NOTIFY moveColorChanged)
    Q_PROPERTY(QQmlListProperty<ChessMove> chessMoves READ chessMoves NOTIFY chessMovesChanged)
public:
    explicit ChessGame(QQuickItem *parent = 0);

    ChessTypes::GameState state() const;

    ChessTypes::Color moveColor() const;

    QQmlListProperty<ChessMove> chessMoves();

    // Actionable
    Q_INVOKABLE void startNewGame(const QVariant& chessBoard);
    Q_INVOKABLE void stopGame();

signals:
    void stateChanged(ChessTypes::GameState state);
    void moveColorChanged(ChessTypes::Color moveColor);
    void chessMovesChanged(QQmlListProperty<ChessMove> chessMoves);

public slots:
    void setState(ChessTypes::GameState state);
    void setMoveColor(ChessTypes::Color newMoveColor);
    virtual void moveMade(const ChessMovePtr chessMove);

protected:
    void clearHistory();
    void alternateMove();
    QSharedPointer<ChessPlayer> chessPlayer(const ChessTypes::Color playerColor);

protected:
    QSharedPointer<ChessPlayer> m_whitePlayer;
    QSharedPointer<ChessPlayer> m_blackPlayer;
    QList<ChessMovePtr> m_moves;

private:
    ChessTypes::Color m_moveColor;
    ChessTypes::GameState m_state;
};


#endif // CHESSGAME_H
