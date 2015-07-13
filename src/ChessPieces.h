// Copyright (C) 2015 Vladimir Karlov <vkarlov.work@gmail.com>
// All rights reserved.
//
// Name:        ChessPieces.h
// Date:        2015.07.13
// Author:      Vladimir Karlov
// Description: Certain chess pieces implementation

#ifndef CHESSPIECES_H
#define CHESSPIECES_H

#include "ChessPiece.h"

// Primitive factory
class ChessPieces
{
public:
    static ChessPiecePtr create(const ChessTypes::Piece type,
                                const ChessTypes::Color color,
                                QQuickItem* board, const int pos = 0);
};

// Chess Piece Pawn
class ChessPiecePawn : public ChessPiece
{
    Q_OBJECT
public:
    ChessPiecePawn::ChessPiecePawn(const ChessTypes::Color pieceColor,
        QQuickItem* chessBoard, const int boardPos = 0)
    : ChessPiece(pieceColor, ChessTypes::Pawn, chessBoard, boardPos)
    {
    }

protected:
    virtual ChessTypes::MoveStates moveAvailable(const ChessPos& newPos) const override;
};

// Chess Piece Bishop
class ChessPieceBishop : public ChessPiece
{
    Q_OBJECT
public:
    ChessPieceBishop::ChessPieceBishop(const ChessTypes::Color pieceColor,
        QQuickItem *chessBoard, const int boardPos = 0)
    : ChessPiece(pieceColor, ChessTypes::Bishop, chessBoard, boardPos)
    {
    }

protected:
    virtual ChessTypes::MoveStates moveAvailable(const ChessPos& newPos) const override;
};

// Chess Piece Knight
class ChessPieceKnight : public ChessPiece
{
    Q_OBJECT
public:
    ChessPieceKnight::ChessPieceKnight(const ChessTypes::Color pieceColor,
        QQuickItem *chessBoard, const int boardPos = 0)
    : ChessPiece(pieceColor, ChessTypes::Knight, chessBoard, boardPos)
    {
    }

protected:
    virtual ChessTypes::MoveStates moveAvailable(const ChessPos& newPos) const override;
};

// Chess Piece Rook
class ChessPieceRook : public ChessPiece
{
    Q_OBJECT
public:
    ChessPieceRook::ChessPieceRook(const ChessTypes::Color pieceColor,
        QQuickItem *chessBoard, const int boardPos = 0)
    : ChessPiece(pieceColor, ChessTypes::Rook, chessBoard, boardPos)
    {
    }

protected:
    virtual ChessTypes::MoveStates moveAvailable(const ChessPos& newPos) const override;
};

// Chess Piece Queen
class ChessPieceQueen : public ChessPiece
{
    Q_OBJECT
public:
    ChessPieceQueen::ChessPieceQueen(const ChessTypes::Color pieceColor,
        QQuickItem *chessBoard, const int boardPos = 0)
    : ChessPiece(pieceColor, ChessTypes::Queen, chessBoard, boardPos)
    {
    }

protected:
    virtual ChessTypes::MoveStates moveAvailable(const ChessPos& newPos) const override;
};

// Chess Piece King
class ChessPieceKing : public ChessPiece
{
    Q_OBJECT
public:
    ChessPieceKing::ChessPieceKing(const ChessTypes::Color pieceColor,
        QQuickItem *chessBoard, const int boardPos = 0)
    : ChessPiece(pieceColor, ChessTypes::King, chessBoard, boardPos)
    {
    }

protected:
    virtual ChessTypes::MoveStates moveAvailable(const ChessPos& newPos) const override;
};

#endif // CHESSPIECES_H
