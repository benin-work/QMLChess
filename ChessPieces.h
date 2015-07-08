#ifndef CHESSPIECES_H
#define CHESSPIECES_H

#include "ChessPiece.h"

// ChessPiecePawn
class ChessPiecePawn : public ChessPiece
{
    Q_OBJECT
public:
    ChessPiecePawn(const PieceColor pieceColor, QQuickItem* chessBoard, const int iPos = 0);
    virtual ~ChessPiecePawn();

protected:
    virtual bool moveAvailable(const int newBoardPos) const override;
};

// ChessPieceRock
class ChessPieceRock : public ChessPiece
{
    Q_OBJECT
public:
    ChessPieceRock(const PieceColor pieceColor, QQuickItem* chessBoard, const int iPos = 0);
    virtual ~ChessPieceRock();

protected:
    virtual bool moveAvailable(const int newBoardPos) const override;
};

#endif // CHESSPIECES_H
