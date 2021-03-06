// Copyright (C) 2015 Vladimir Karlov <vkarlov.work@gmail.com>
// All rights reserved.
//
// Name:        ChessTypes.h
// Date:        2015.07.13
// Author:      Vladimir Karlov
// Description: Basic Chess Types with helpers

#ifndef CHESSTYPES
#define CHESSTYPES

#include <QObject>
#include "ChessPos.h"

class ChessTypes: public QObject
{
    Q_OBJECT
    Q_ENUMS(GameState Color Piece MoveState)
public:

    enum GameState {
        GameOff = 0,
        GameLive,
        GamePlay
    };

    enum Color
    {
        White = 0,
        Black
    };

    enum Piece
    {
        Undefined = -1,
        Pawn = 0,
        Bishop,
        Knight,
        Rook,
        Queen,
        King
    };

    enum MoveState
    {
        MoveNotAvailable = 0x0,
        MoveAvailable = 0x1,
        MoveCapture = 0x2,
        MoveEnPassant = 0x4,
        MoveCheck = 0x8,
        MoveCheckMate = 0x10,
        MovePawnPromotion = 0x20,
        MoveKingsideCastling = 0x40,
        MoveQueensideCastling = 0x80
    };

    Q_DECLARE_FLAGS(MoveStates, MoveState)

    // Return color name (White or Black)
    static const QString colorName(const Color color);

    // Return full name (Panw, Knight, etc)
    static const QString pieceTypeFullName(const Piece pieceType);

    // Return short name in Algebraic notation:
    // K - King, Q - Queen,
    // R - Rook, N - Knight,
    // B - Bishop, ""(empty) - Pawn
    static const QString pieceTypeName(const Piece pieceType);

    // Return short name in Algebraic notation:
    // ""(empty) - Move
    // "x" - Capture
    // "+" - Check
    static const QString moveStateName(const MoveState moveState);
};

Q_DECLARE_OPERATORS_FOR_FLAGS(ChessTypes::MoveStates)


class ChessMove;
typedef QSharedPointer<ChessMove> ChessMovePtr;

class ChessPiece;
typedef QSharedPointer<ChessPiece> ChessPiecePtr;

#endif // CHESSTYPES

