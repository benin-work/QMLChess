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

bool ChessPiecePawn::moveAvailable(const int newBoardPos) const
{
    int oldCol(ChessPiece::colFromPos(boardPos()));
    int oldRow(ChessPiece::rowFromPos(boardPos()));
    int newCol(ChessPiece::colFromPos(newBoardPos));
    int newRow(ChessPiece::rowFromPos(newBoardPos));

    // Reverse board index for White side
    if (color() == ChessPiece::White)
    {
        oldRow = 7 - oldRow;
        newRow = 7 - newRow;
    }

    if ((newCol == oldCol && newRow - oldRow == 1) ||
        (newCol == oldCol && oldRow == 1 && newRow - oldRow == 2))
        return true;

    return false;
}

// Chess Piece Rock
ChessPieceRock::ChessPieceRock(const ChessPiece::PieceColor pieceColor,
    QQuickItem *chessBoard, const int boardPos)
: ChessPiece(pieceColor, ChessPiece::Rock, chessBoard, boardPos)
{
}

bool ChessPieceRock::moveAvailable(const int newBoardPos) const
{
    const int oldCol(ChessPiece::colFromPos(boardPos()));
    const int oldRow(ChessPiece::rowFromPos(boardPos()));
    const int newCol(ChessPiece::colFromPos(newBoardPos));
    const int newRow(ChessPiece::rowFromPos(newBoardPos));

    return (oldCol == newCol || oldRow == newRow);
}

// Chess Piece King
ChessPieceKing::ChessPieceKing(const ChessPiece::PieceColor pieceColor,
   QQuickItem *chessBoard, const int boardPos)
: ChessPiece(pieceColor, ChessPiece::King, chessBoard, boardPos)
{
}

bool ChessPieceKing::moveAvailable(const int newBoardPos) const
{
    const int oldCol(ChessPiece::colFromPos(boardPos()));
    const int oldRow(ChessPiece::rowFromPos(boardPos()));
    const int newCol(ChessPiece::colFromPos(newBoardPos));
    const int newRow(ChessPiece::rowFromPos(newBoardPos));

    return (qAbs(oldCol - newCol) <= 1 && qAbs(oldRow - newRow) <= 1);
}

