#ifndef CHESSPIECES_H
#define CHESSPIECES_H

#include "ChessPiece.h"

// Chess Piece Pawn
class ChessPiecePawn : public ChessPiece
{
    Q_OBJECT
public:
    ChessPiecePawn(const PieceColor pieceColor, QQuickItem* chessBoard, const int boardPos = 0);

protected:
    virtual bool moveAvailable(const int newBoardPos) const override;
};

// Chess Piece Rock
class ChessPieceRock : public ChessPiece
{
    Q_OBJECT
public:
    ChessPieceRock(const PieceColor pieceColor, QQuickItem* chessBoard, const int boardPos = 0);

protected:
    virtual bool moveAvailable(const int newBoardPos) const override;
};

// Chess Piece King
class ChessPieceKing : public ChessPiece
{
    Q_OBJECT
public:
    ChessPieceKing(const PieceColor pieceColor, QQuickItem* chessBoard, const int boardPos = 0);

protected:
    virtual bool moveAvailable(const int newBoardPos) const override;
};

#endif // CHESSPIECES_H
