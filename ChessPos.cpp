#include "ChessPos.h"

ChessPos::ChessPos(const int boardPos /*= 0*/)
: m_boardPos(boardPos)
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
    return rowFromPos(m_boardPos);
}

const int ChessPos::col() const
{
    return colFromPos(m_boardPos);
}

const int ChessPos::rowFromPos(const int boardPos)
{
    return boardPos / 8;
}

const int ChessPos::colFromPos(const int boardPos)
{
    return boardPos % 8;
}

const QString ChessPos::chessPosName() const
{
    return QString(QChar('a' + col())) + QString::number(8 - row());
}
