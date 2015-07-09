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

ChessPos::ChessPos(const int rowPos, const int colPos)
: QObject()
, m_boardPos(ChessPos::boardPos(rowPos, colPos))
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

const QString ChessPos::name() const
{
    return QString(QChar('a' + col())) + QString::number(8 - row());
}
