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
    int piecePos = 2; // Overjump for Pawn first move
    if (color() == ChessPiece::White)
    {
        oldRow = 7 - oldRow;
        newRow = 7 - newRow;
        piecePos = 5;
    }

    if (newPos.col() == pos().col())
    {
        if (newRow - oldRow == 1)
            return true;

        if ((oldRow == 1 && newRow == 3) &&
            !isParentPiece(ChessPos::boardPos(piecePos, newPos.col())))
            return true;
    }

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
    if (pos().col() != newPos.col() && pos().row() != newPos.row())
        return false;

    if (pos().col() == newPos.col())
    {
        const int rowMove = pos().row() > newPos.row() ? -1 : 1;
        int row = pos().row();
        while ((row += rowMove) != newPos.row())
            if (isParentPiece(ChessPos::boardPos(row, newPos.col())))
                return false;
    }
    else
    {
        const int colMove = pos().col() > newPos.col() ? -1 : 1;
        int col = pos().col();
        while ((col += colMove) != newPos.col())
            if (isParentPiece(ChessPos::boardPos(newPos.row(), col)))
                return false;
    }

    return true;
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

// Chess Piece Bishop
ChessPieceBishop::ChessPieceBishop(const ChessPiece::PieceColor pieceColor,
    QQuickItem *chessBoard, const int boardPos)
: ChessPiece(pieceColor, ChessPiece::Bishop, chessBoard, boardPos)
{
}

bool ChessPieceBishop::moveAvailable(const ChessPos &newPos) const
{
    return true;
}


ChessPieceQueen::ChessPieceQueen(const ChessPiece::PieceColor pieceColor,
    QQuickItem *chessBoard, const int boardPos)
: ChessPiece(pieceColor, ChessPiece::Queen, chessBoard, boardPos)
{
}

bool ChessPieceQueen::moveAvailable(const ChessPos &newPos) const
{
    if (pos().col() != newPos.col() && pos().row() != newPos.row())
        return false;

    if (pos().col() == newPos.col())
    {
        const int rowMove = pos().row() > newPos.row() ? -1 : 1;
        int row = pos().row();
        while ((row += rowMove) != newPos.row())
            if (isParentPiece(ChessPos::boardPos(row, newPos.col())))
                return false;
    }
    else
    {
        const int colMove = pos().col() > newPos.col() ? -1 : 1;
        int col = pos().col();
        while ((col += colMove) != newPos.col())
            if (isParentPiece(ChessPos::boardPos(newPos.row(), col)))
                return false;
    }

    return true;
}
