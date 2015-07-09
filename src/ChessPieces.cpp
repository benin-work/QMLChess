#include <QDebug>
#include <QQmlEngine>
#include <QQmlComponent>

#include "ChessPieces.h"

// Chess Piece Pawn
ChessPiece::MoveState ChessPiecePawn::moveAvailable(const ChessPos& newPos) const
{
    // Reverse board index for White side
    int oldRow(pos().row());
    int newRow(newPos.row());
    int piecePos = 2; // Overjump for Pawn first move
    if (color() == ChessTypes::White)
    {
        oldRow = 7 - oldRow;
        newRow = 7 - newRow;
        piecePos = 5;
    }

    if (newPos.col() == pos().col())
    {
        if ((newRow - oldRow == 1 || oldRow == 1 && newRow == 3) &&
                moveThroughAvailable(newPos) == ChessPiece::MoveAvailable)
            return ChessPiece::MoveAvailable;
    } else
    if (qAbs(newPos.col() - pos().col()) == 1 && newRow - oldRow == 1)
    {
        // Check for capture
        if (isOpponentPiece(newPos.boardPos()))
            return ChessPiece::MoveCapture;
    }

    return ChessPiece::MoveNotAvailable;
}

// Chess Piece Bishop
ChessPiece::MoveState ChessPieceBishop::moveAvailable(const ChessPos &newPos) const
{
    // Check Diagonal move
    if (qAbs(newPos.row() - pos().row()) != qAbs(newPos.col() - pos().col()))
        return ChessPiece::MoveNotAvailable;

    return moveThroughAvailable(newPos);
}

// Chess Piece Knight
ChessPiece::MoveState ChessPieceKnight::moveAvailable(const ChessPos &newPos) const
{
    // Check Knight move
    if((qAbs(newPos.row() - pos().row()) == 2 && qAbs(newPos.col() - pos().col()) == 1) ||
       (qAbs(newPos.col() - pos().col())== 2 && qAbs(newPos.row() - pos().row()) == 1))
    {
        if (isOpponentPiece(newPos.boardPos()))
            return ChessPiece::MoveCapture;

        return ChessPiece::MoveAvailable;
    }

    return ChessPiece::MoveNotAvailable;
}

// Chess Piece Rook
ChessPiece::MoveState ChessPieceRook::moveAvailable(const ChessPos &newPos) const
{
    // Check Horizontal or Vertical move
    if (pos().col() != newPos.col() && pos().row() != newPos.row())
        return ChessPiece::MoveNotAvailable;

    return moveThroughAvailable(newPos);
}

// Chess Piece Queen
ChessPiece::MoveState ChessPieceQueen::moveAvailable(const ChessPos &newPos) const
{
    // Check Horizontal, Vertical or Diagonal move
    if ((qAbs(newPos.row() - pos().row()) != qAbs(newPos.col() - pos().col())) &&
        (pos().col() != newPos.col() && pos().row() != newPos.row()))
        return ChessPiece::MoveNotAvailable;

    return moveThroughAvailable(newPos);
}

// Chess Piece King
ChessPiece::MoveState ChessPieceKing::moveAvailable(const ChessPos &newPos) const
{
    // Check nearest
    if (qAbs(pos().col() - newPos.col()) <= 1 && qAbs(pos().row() - newPos.row()) <= 1)
    {
        if (isOpponentPiece(newPos.boardPos()))
            return ChessPiece::MoveCapture;

        return ChessPiece::MoveAvailable;
    }

    return ChessPiece::MoveNotAvailable;
}

