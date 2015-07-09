#ifndef CHESSPIECES_H
#define CHESSPIECES_H

#include "ChessPiece.h"

// Chess Piece Pawn
class ChessPiecePawn : public ChessPiece
{
    Q_OBJECT
public:
    ChessPiecePawn::ChessPiecePawn(const ChessTypes::PieceColor pieceColor,
        QQuickItem* chessBoard, const int boardPos = 0)
    : ChessPiece(pieceColor, ChessTypes::Pawn, chessBoard, boardPos)
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
    ChessPieceBishop::ChessPieceBishop(const ChessTypes::PieceColor pieceColor,
        QQuickItem *chessBoard, const int boardPos = 0)
    : ChessPiece(pieceColor, ChessTypes::Bishop, chessBoard, boardPos)
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
    ChessPieceKnight::ChessPieceKnight(const ChessTypes::PieceColor pieceColor,
        QQuickItem *chessBoard, const int boardPos = 0)
    : ChessPiece(pieceColor, ChessTypes::Knight, chessBoard, boardPos)
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
    ChessPieceRook::ChessPieceRook(const ChessTypes::PieceColor pieceColor,
        QQuickItem *chessBoard, const int boardPos = 0)
    : ChessPiece(pieceColor, ChessTypes::Rook, chessBoard, boardPos)
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
    ChessPieceQueen::ChessPieceQueen(const ChessTypes::PieceColor pieceColor,
        QQuickItem *chessBoard, const int boardPos = 0)
    : ChessPiece(pieceColor, ChessTypes::Queen, chessBoard, boardPos)
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
    ChessPieceKing::ChessPieceKing(const ChessTypes::PieceColor pieceColor,
        QQuickItem *chessBoard, const int boardPos = 0)
    : ChessPiece(pieceColor, ChessTypes::King, chessBoard, boardPos)
    {
    }

protected:
    virtual ChessPiece::MoveState moveAvailable(const ChessPos& newPos) const override;
};

#endif // CHESSPIECES_H
