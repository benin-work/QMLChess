#ifndef CHESSGAMEPLAYER_H
#define CHESSGAMEPLAYER_H

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

public slots:
    virtual void madeMove(const ChessMovePtr chessMove) override;

    void setActiveMove(int activeMove);

signals:
    void hasNextMoveChanged(bool hasNextMove);
    void hasPrevMoveChanged(bool hasPrevMove);
    void activeMoveChanged(int activeMove);

private:
    int m_activeMove;
};

#endif // CHESSGAMEPLAYER_H
