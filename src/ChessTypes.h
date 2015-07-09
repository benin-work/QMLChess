#ifndef CHESSTYPES
#define CHESSTYPES

#include <QObject>
#include "ChessPos.h"

class ChessTypes: public QObject
{
    Q_OBJECT
    Q_ENUMS(Color)
    Q_ENUMS(Piece)
    Q_ENUMS(MoveState)
public:

    enum Color
    {
        White = 0,
        Black
    };

    enum Piece
    {
        Pawn = 0,
        Bishop,
        Knight,
        Rook,
        Queen,
        King
    };

    enum MoveState
    {
        MoveNotAvailable = 0,
        MoveAvailable,
        MoveCapture,
        MoveCaptureEnPassant,
        MoveCheck,
        MoveCheckMate,
        MovePawnPromotion,
        MoveKingsideCastling,
        MoveQueensideCastling
    };

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

#endif // CHESSTYPES

