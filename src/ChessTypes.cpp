// Copyright (C) 2015 Vladimir Karlov <vkarlov.work@gmail.com>
// All rights reserved.
//
// Name:        ChessTypes.cpp
// Date:        2015.07.13
// Author:      Vladimir Karlov
// Description: Basic Chess Types with helpers

#include "ChessTypes.h"

const QString ChessTypes::colorName(const ChessTypes::Color color)
{
    return color == White ? QString("White") : QString("Black");
}

const QString ChessTypes::pieceTypeFullName(const ChessTypes::Piece pieceType)
{
    switch(pieceType)
    {
        case King: return QString("King");
        case Queen: return QString("Queen");
        case Rook: return QString("Rook");
        case Knight: return QString("Knight");
        case Bishop: return QString("Bishop");
        case Pawn: return QString("Pawn");
    }
    return QString("?");
}

const QString ChessTypes::pieceTypeName(const ChessTypes::Piece pieceType)
{
    switch(pieceType)
    {
        case King: return QString("K");
        case Queen: return QString("Q");
        case Rook: return QString("R");
        case Knight: return QString("N");
        case Bishop: return QString("B");
        case Pawn: return QString("");
    }
    return QString("?");
}

const QString ChessTypes::moveStateName(const ChessTypes::MoveState moveState)
{
    switch(moveState)
    {
        case MoveAvailable: return QString("");
        case MoveCapture: return QString("x");
        case MoveEnPassant: return QString("e.p.");
        case MoveCheck: return QString("+");
        case MoveCheckMate: return QString("#");
        case MovePawnPromotion: return QString("=");
        case MoveKingsideCastling: return QString("0-0");
        case MoveQueensideCastling: return QString("0-0-0");
    }
    return QString("");
}
