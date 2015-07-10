#include "ChessPos.h"

ChessPos::ChessPos(QObject* parent /*=0*/)
: QObject(parent)
, m_boardPos(0)
{
}

ChessPos::ChessPos(const int boardPos)
: QObject()
, m_boardPos(boardPos)
{
}

ChessPos::ChessPos(const int row, const int col)
: QObject()
, m_boardPos(ChessPos::boardPos(row, col))
{
}

ChessPos::ChessPos(const ChessPos &pos)
: QObject()
, m_boardPos(pos.boardPos())
{
}

ChessPos& ChessPos::operator=(const ChessPos& pos)
{
    if (this != &pos)
    {
        setBoardPos(pos.boardPos());
    }

    return *this;
}

ChessPos::operator int() const
{
    return boardPos();
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
    return row(m_boardPos);
}

const int ChessPos::col() const
{
    return col(m_boardPos);
}

const int ChessPos::row(const int boardPos)
{
    return boardPos / 8;
}

const int ChessPos::col(const int boardPos)
{
    return boardPos % 8;
}

const int ChessPos::boardPos(const int row, const int col)
{
    return row * 8 + col;
}

const QString ChessPos::name() const
{
    return QString(QChar('a' + col())) + QString::number(8 - row());
}
