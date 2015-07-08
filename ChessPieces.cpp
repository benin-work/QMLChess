#include <QDebug>
#include <QQmlEngine>
#include <QQmlComponent>

#include "ChessPieces.h"

// ChessPiecePawn
ChessPiecePawn::ChessPiecePawn(const ChessPiece::PieceColor pieceColor,
    QQuickItem* chessBoard, const int iPos)
: ChessPiece(pieceColor, ChessPiece::Pawn, chessBoard, iPos)
{
}

ChessPiecePawn::~ChessPiecePawn()
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

// ChessPieceRock
ChessPieceRock::ChessPieceRock(const ChessPiece::PieceColor pieceColor,
    QQuickItem *chessBoard, const int iPos)
: ChessPiece(pieceColor, ChessPiece::Rock, chessBoard, iPos)
{
}

ChessPieceRock::~ChessPieceRock()
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
