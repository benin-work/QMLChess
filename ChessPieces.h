#ifndef CHESSPIECES_H
#define CHESSPIECES_H

#include "ChessPiece.h"

// Chess Piece Pawn
class ChessPiecePawn : public ChessPiece
{
    Q_OBJECT
public:
    ChessPiecePawn::ChessPiecePawn(const ChessPiece::PieceColor pieceColor,
        QQuickItem* chessBoard, const int boardPos = 0)
    : ChessPiece(pieceColor, ChessPiece::Pawn, chessBoard, boardPos)
    {
    }

protected:
    virtual ChessPiece::MoveState moveAvailable(const ChessPos& newPos) const override;
};

// Chess Piece Bishop
class ChessPieceBishop : public ChessPiece
{
    Q_OBJECT
public:
    ChessPieceBishop::ChessPieceBishop(const ChessPiece::PieceColor pieceColor,
        QQuickItem *chessBoard, const int boardPos = 0)
    : ChessPiece(pieceColor, ChessPiece::Bishop, chessBoard, boardPos)
    {
    }

protected:
    virtual ChessPiece::MoveState moveAvailable(const ChessPos& newPos) const override;
};

// Chess Piece Knight
class ChessPieceKnight : public ChessPiece
{
    Q_OBJECT
public:
    ChessPieceKnight::ChessPieceKnight(const ChessPiece::PieceColor pieceColor,
        QQuickItem *chessBoard, const int boardPos = 0)
    : ChessPiece(pieceColor, ChessPiece::Knight, chessBoard, boardPos)
    {
    }

protected:
    virtual ChessPiece::MoveState moveAvailable(const ChessPos& newPos) const override;
};

// Chess Piece Rook
class ChessPieceRook : public ChessPiece
{
    Q_OBJECT
public:
    ChessPieceRook::ChessPieceRook(const ChessPiece::PieceColor pieceColor,
        QQuickItem *chessBoard, const int boardPos = 0)
    : ChessPiece(pieceColor, ChessPiece::Rook, chessBoard, boardPos)
    {
    }

protected:
    virtual ChessPiece::MoveState moveAvailable(const ChessPos& newPos) const override;
};

// Chess Piece Queen
class ChessPieceQueen : public ChessPiece
{
    Q_OBJECT
public:
    ChessPieceQueen::ChessPieceQueen(const ChessPiece::PieceColor pieceColor,
        QQuickItem *chessBoard, const int boardPos = 0)
    : ChessPiece(pieceColor, ChessPiece::Queen, chessBoard, boardPos)
    {
    }

protected:
    virtual ChessPiece::MoveState moveAvailable(const ChessPos& newPos) const override;
};

// Chess Piece King
class ChessPieceKing : public ChessPiece
{
    Q_OBJECT
public:
    ChessPieceKing::ChessPieceKing(const ChessPiece::PieceColor pieceColor,
        QQuickItem *chessBoard, const int boardPos = 0)
    : ChessPiece(pieceColor, ChessPiece::King, chessBoard, boardPos)
    {
    }

protected:
    virtual ChessPiece::MoveState moveAvailable(const ChessPos& newPos) const override;
};

#endif // CHESSPIECES_H
