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
    virtual bool moveAvailable(const ChessPos& newPos) const override;
};

// Chess Piece Rook
class ChessPieceRook : public ChessPiece
{
    Q_OBJECT
public:
    ChessPieceRook(const PieceColor pieceColor, QQuickItem* chessBoard, const int boardPos = 0);

protected:
    virtual bool moveAvailable(const ChessPos& newPos) const override;
};

// Chess Piece King
class ChessPieceKing : public ChessPiece
{
    Q_OBJECT
public:
    ChessPieceKing(const PieceColor pieceColor, QQuickItem* chessBoard, const int boardPos = 0);

protected:
    virtual bool moveAvailable(const ChessPos& newPos) const override;
};

// Chess Piece Queen
class ChessPieceQueen : public ChessPiece
{
    Q_OBJECT
public:
    ChessPieceQueen(const PieceColor pieceColor, QQuickItem* chessBoard, const int boardPos = 0);

protected:
    virtual bool moveAvailable(const ChessPos& newPos) const override;
};

// Chess Piece Knight
class ChessPieceKnight : public ChessPiece
{
    Q_OBJECT
public:
    ChessPieceKnight(const PieceColor pieceColor, QQuickItem* chessBoard, const int boardPos = 0);

protected:
    virtual bool moveAvailable(const ChessPos& newPos) const override;
};

// Chess Piece Bishop
class ChessPieceBishop : public ChessPiece
{
    Q_OBJECT
public:
    ChessPieceBishop(const PieceColor pieceColor, QQuickItem* chessBoard, const int boardPos = 0);

protected:
    virtual bool moveAvailable(const ChessPos& newPos) const override;
};

#endif // CHESSPIECES_H
