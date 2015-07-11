#include <QDebug>
#include "ChessMove.h"

ChessMove::ChessMove(QObject *parent)
: QObject(parent)
{
}

ChessMove::ChessMove(const ChessTypes::Color pieceColor,
    ChessTypes::Piece pieceType,
    const ChessPos& oldPos, const ChessPos& newPos,
    ChessTypes::MoveStates moveState)
: QObject()
, m_pieceColor(pieceColor)
, m_pieceType(pieceType)
, m_oldPos(oldPos)
, m_newPos(newPos)
, m_moveStates(moveState)
{
}

ChessMove::ChessMove(const ChessMove& pos)
: QObject()
, m_pieceColor(pos.m_pieceColor)
, m_pieceType(pos.m_pieceType)
, m_oldPos(pos.m_oldPos)
, m_newPos(pos.m_newPos)
, m_moveStates(pos.m_moveStates)
{
}

ChessMove& ChessMove::operator =(const ChessMove& pos)
{
    if (this != &pos)
    {
        m_pieceColor = pos.m_pieceColor;
        m_pieceType = pos.m_pieceType;
        m_oldPos = pos.m_oldPos;
        m_newPos = pos.m_newPos;
        m_moveStates = pos.m_moveStates;
    }

    return *this;
}

ChessMove::~ChessMove()
{
}

ChessTypes::Color ChessMove::pieceColor() const
{
    return m_pieceColor;
}

ChessTypes::Piece ChessMove::pieceType() const
{
    return m_pieceType;
}

const ChessPos& ChessMove::oldPos() const
{
    return m_oldPos;
}

const ChessPos& ChessMove::newPos() const
{
    return m_newPos;
}

const QString ChessMove::name() const
{
    QString strName(ChessTypes::pieceTypeName(pieceType()));

    if (moveStates().testFlag(ChessTypes::MoveCapture))
        strName += ChessTypes::moveStateName(ChessTypes::MoveCapture);

    strName += newPos().name();

    if (moveStates().testFlag(ChessTypes::MoveEnPassant) && moveStates().testFlag(ChessTypes::MoveCapture))
        strName += ChessTypes::moveStateName(ChessTypes::MoveEnPassant);

    return strName;
}

ChessTypes::MoveStates ChessMove::moveStates() const
{
    return m_moveStates;
}

void ChessMove::setPieceColor(ChessTypes::Color pieceColor)
{
    if (m_pieceColor == pieceColor)
        return;

    m_pieceColor = pieceColor;
}

void ChessMove::setPieceType(ChessTypes::Piece pieceType)
{
    if (m_pieceType == pieceType)
        return;

    m_pieceType = pieceType;
}

void ChessMove::setOldPos(const ChessPos& oldPos)
{
    m_oldPos = oldPos;
}

void ChessMove::setNewPos(const ChessPos& newPos)
{
    m_newPos = newPos;
}

void ChessMove::setMoveStates(ChessTypes::MoveStates moveStates)
{
    m_moveStates = moveStates;
}

