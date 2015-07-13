// Copyright (C) 2015 Vladimir Karlov <vkarlov.work@gmail.com>
// All rights reserved.
//
// Name:        ChessGameplay.h
// Date:        2015.07.13
// Author:      Vladimir Karlov
// Description: Game replay logic. Save/Load moves. Play prev/next.

#ifndef CHESSGAMEPLAY_H
#define CHESSGAMEPLAY_H

#include "ChessGame.h"

class ChessGameplay : public ChessGame
{
    Q_OBJECT
    Q_PROPERTY(bool hasPrevMove READ hasPrevMove NOTIFY hasPrevMoveChanged)
    Q_PROPERTY(bool hasNextMove READ hasNextMove NOTIFY hasNextMoveChanged)
    Q_PROPERTY(int activeMove READ activeMove WRITE setActiveMove NOTIFY activeMoveChanged)
public:
    explicit ChessGameplay(QQuickItem *parent = 0);

    // Move through history
    Q_INVOKABLE void movePrev();
    Q_INVOKABLE void moveNext();
    Q_INVOKABLE void moveAt(const int moveIndex);
    bool hasNextMove() const;
    bool hasPrevMove() const;

    int activeMove() const;

    // Load game and start it on board
    Q_INVOKABLE void load(const QString& fileName, const QVariant& chessBoard);
    Q_INVOKABLE void save(const QString& fileName);

public slots:
    virtual void moveMade(const ChessMovePtr chessMove) override;

    void setActiveMove(int activeMove);

signals:
    void hasNextMoveChanged(bool hasNextMove);
    void hasPrevMoveChanged(bool hasPrevMove);
    void activeMoveChanged(int activeMove);

private:
    int m_activeMove;
};

#endif // CHESSGAMEPLAY
