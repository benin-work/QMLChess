#include "ChessPos.h"

ChessPos::ChessPos(const int boardPos /*= 0*/)
: m_boardPos(boardPos)
{
}

ChessPos::ChessPos(const int rowPos, const int colPos)
: m_boardPos(ChessPos::boardPos(rowPos, colPos))
{
}

const int ChessPos::boardPos() const
{
    return m_boardPos;
}

void ChessPos::setBoardPos(const int newBoardPos)
{
    m_boardPos = newBoardPos;
}

const int ChessPos::row() const
{
    return rowPos(m_boardPos);
}

const int ChessPos::col() const
{
    return colPos(m_boardPos);
}

const int ChessPos::rowPos(const int boardPos)
{
    return boardPos / 8;
}

const int ChessPos::colPos(const int boardPos)
{
    return boardPos % 8;
}

const int ChessPos::boardPos(const int rowPos, const int colPos)
{
    return rowPos * 8 + colPos;
}

const QString ChessPos::chessPosName() const
{
    return QString(QChar('a' + col())) + QString::number(8 - row());
}
