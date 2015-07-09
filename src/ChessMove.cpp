#include "ChessMove.h"

ChessMove::ChessMove(QObject *parent)
: QObject(parent)
{
}

ChessMove::ChessMove(const ChessTypes::Color pieceColor,
    ChessTypes::Piece pieceType,
    const ChessPos& oldPos, const ChessPos& newPos,
    ChessTypes::MoveState moveState)
: m_pieceColor(pieceColor)
, m_pieceType(pieceType)
, m_oldPos(oldPos)
, m_newPos(newPos)
, m_moveState(moveState)
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
    return ChessTypes::pieceTypeName(pieceType()) +
           ChessTypes::moveStateName(moveState()) +
            newPos().name();
}

ChessTypes::MoveState ChessMove::moveState() const
{
    return m_moveState;
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

void ChessMove::setMoveState(ChessTypes::MoveState moveState)
{
    m_moveState = moveState;
}

