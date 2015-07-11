#include <QDebug>
#include <QQmlEngine>
#include <QQmlComponent>

#include "ChessPieces.h"

// Chess Piece Pawn
ChessTypes::MoveStates ChessPiecePawn::moveAvailable(const ChessPos& newPos) const
{
    ChessTypes::MoveStates moveState(ChessTypes::MoveNotAvailable);

    // Reverse board index for White side
    int oldRow(pos().row());
    int newRow(newPos.row());
    if (color() == ChessTypes::White)
    {
        oldRow = 7 - oldRow;
        newRow = 7 - newRow;
    }

    if (newPos.col() == pos().col())
    {
        if ((newRow - oldRow == 1 || oldRow == 1 && newRow == 3) &&
                moveThroughAvailable(newPos) == ChessTypes::MoveAvailable)
        {
            moveState = ChessTypes::MoveAvailable;
            if (newRow - oldRow == 2)
                moveState |= ChessTypes::MoveEnPassant;
        }
    } else
    if (qAbs(newPos.col() - pos().col()) == 1 && newRow - oldRow == 1)
    {
        // Check for capture
        if (isOpponentPiece(newPos))
            moveState = ChessTypes::MoveCapture;

        // Check En Passant
        if (isOpponentPieceEnPassant(newPos))
            moveState = ChessTypes::MoveCapture | ChessTypes::MoveEnPassant;
    }

    if (newRow == 7 && moveState & (ChessTypes::MoveAvailable | ChessTypes::MoveCapture))
        moveState |= ChessTypes::MovePawnPromotion;

    return moveState;
}

// Chess Piece Bishop
ChessTypes::MoveStates ChessPieceBishop::moveAvailable(const ChessPos &newPos) const
{
    // Check Diagonal move
    if (qAbs(newPos.row() - pos().row()) != qAbs(newPos.col() - pos().col()))
        return ChessTypes::MoveNotAvailable;

    return moveThroughAvailable(newPos);
}

// Chess Piece Knight
ChessTypes::MoveStates ChessPieceKnight::moveAvailable(const ChessPos &newPos) const
{
    // Check Knight move
    if((qAbs(newPos.row() - pos().row()) == 2 && qAbs(newPos.col() - pos().col()) == 1) ||
       (qAbs(newPos.col() - pos().col())== 2 && qAbs(newPos.row() - pos().row()) == 1))
    {
        if (isOpponentPiece(newPos.boardPos()))
            return ChessTypes::MoveCapture;

        return ChessTypes::MoveAvailable;
    }

    return ChessTypes::MoveNotAvailable;
}

// Chess Piece Rook
ChessTypes::MoveStates ChessPieceRook::moveAvailable(const ChessPos &newPos) const
{
    // Check Horizontal or Vertical move
    if (pos().col() != newPos.col() && pos().row() != newPos.row())
        return ChessTypes::MoveNotAvailable;

    return moveThroughAvailable(newPos);
}

// Chess Piece Queen
ChessTypes::MoveStates ChessPieceQueen::moveAvailable(const ChessPos &newPos) const
{
    // Check Horizontal, Vertical or Diagonal move
    if ((qAbs(newPos.row() - pos().row()) != qAbs(newPos.col() - pos().col())) &&
        (pos().col() != newPos.col() && pos().row() != newPos.row()))
        return ChessTypes::MoveNotAvailable;

    return moveThroughAvailable(newPos);
}

// Chess Piece King
ChessTypes::MoveStates ChessPieceKing::moveAvailable(const ChessPos &newPos) const
{
    // Check nearest
    if (qAbs(pos().col() - newPos.col()) <= 1 && qAbs(pos().row() - newPos.row()) <= 1)
    {
        if (isOpponentPiece(newPos.boardPos()))
            return ChessTypes::MoveCapture;

        return ChessTypes::MoveAvailable;
    }

    return ChessTypes::MoveNotAvailable;
}

