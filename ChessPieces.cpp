#include <QDebug>
#include <QQmlEngine>
#include <QQmlComponent>

#include "ChessPieces.h"

// Chess Piece Pawn
ChessPiecePawn::ChessPiecePawn(const ChessPiece::PieceColor pieceColor,
    QQuickItem* chessBoard, const int boardPos)
: ChessPiece(pieceColor, ChessPiece::Pawn, chessBoard, boardPos)
{
}

bool ChessPiecePawn::moveAvailable(const ChessPos& newPos) const
{
    // Reverse board index for White side
    int oldRow(pos().row());
    int newRow(newPos.row());
    if (color() == ChessPiece::White)
    {
        oldRow = 7 - oldRow;
        newRow = 7 - newRow;
    }

    if ((newPos.col() == pos().col() && newRow - oldRow == 1) ||
        (newPos.col() == pos().col() && oldRow == 1 && newRow - oldRow == 2))
        return true;

    return false;
}

// Chess Piece Rock
ChessPieceRock::ChessPieceRock(const ChessPiece::PieceColor pieceColor,
    QQuickItem *chessBoard, const int boardPos)
: ChessPiece(pieceColor, ChessPiece::Rock, chessBoard, boardPos)
{
}

bool ChessPieceRock::moveAvailable(const ChessPos &newPos) const
{
    return (pos().col() == newPos.col() || pos().row() == newPos.row());
}

// Chess Piece King
ChessPieceKing::ChessPieceKing(const ChessPiece::PieceColor pieceColor,
   QQuickItem *chessBoard, const int boardPos)
: ChessPiece(pieceColor, ChessPiece::King, chessBoard, boardPos)
{
}

bool ChessPieceKing::moveAvailable(const ChessPos &newPos) const
{
    return qAbs(pos().col() - newPos.col()) <= 1 &&
            qAbs(pos().row() - newPos.row()) <= 1;
}

// Chess Piece Knight
ChessPieceKnight::ChessPieceKnight(const ChessPiece::PieceColor pieceColor,
   QQuickItem *chessBoard, const int boardPos)
: ChessPiece(pieceColor, ChessPiece::Knight, chessBoard, boardPos)
{
}

bool ChessPieceKnight::moveAvailable(const ChessPos &newPos) const
{
    if((qAbs(newPos.row() - pos().row()) == 2 && qAbs(newPos.col() - pos().col()) == 1) ||
       (qAbs(newPos.col() - pos().col())== 2 && qAbs(newPos.row() - pos().row()) == 1))
        return true;

    return false;
}
