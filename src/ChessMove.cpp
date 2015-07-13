// Copyright (C) 2015 Vladimir Karlov <vkarlov.work@gmail.com>
// All rights reserved.
//
// Name:        ChessMove.cpp
// Date:        2015.07.13
// Author:      Vladimir Karlov
// Description: Information about one move

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
, m_pieceOperationType(ChessTypes::Undefined)
, m_oldPos(oldPos)
, m_newPos(newPos)
, m_moveStates(moveState)
{
}

ChessMove::ChessMove(const ChessMove& pos)
: QObject()
, m_pieceColor(pos.m_pieceColor)
, m_pieceType(pos.m_pieceType)
, m_pieceOperationType(pos.m_pieceOperationType)
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
        m_pieceOperationType = pos.m_pieceOperationType;
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

ChessTypes::Piece ChessMove::operationType() const
{
    return m_pieceOperationType;
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

    if (moveStates() & ChessTypes::MoveCapture)
        strName += ChessTypes::moveStateName(ChessTypes::MoveCapture);

    strName += newPos().name();

    if ((moveStates() & ChessTypes::MoveEnPassant) && (moveStates() & ChessTypes::MoveCapture))
        strName += ChessTypes::moveStateName(ChessTypes::MoveEnPassant);

    if (moveStates() & ChessTypes::MovePawnPromotion)
    {
        strName += ChessTypes::moveStateName(ChessTypes::MovePawnPromotion);
        strName += ChessTypes::pieceTypeName(operationType());
    }

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

void ChessMove::setPieceOperationType(ChessTypes::Piece pieceOperationType)
{
    if (m_pieceOperationType == pieceOperationType)
        return;

    m_pieceOperationType = pieceOperationType;
    emit pieceOperationTypeChanged(pieceOperationType);
}

void ChessMove::read(const QJsonObject &json)
{
    m_pieceColor = ChessTypes::Color(qRound(json["color"].toDouble()));
    m_pieceType = ChessTypes::Piece(qRound(json["type"].toDouble()));
    m_pieceOperationType = ChessTypes::Piece(qRound(json["operationType"].toDouble()));
    m_oldPos = qRound(json["oldPos"].toDouble());
    m_newPos = qRound(json["newPos"].toDouble());
    m_moveStates = ChessTypes::MoveStates(qRound(json["moveStates"].toDouble()));
}

void ChessMove::write(QJsonObject &json) const
{
    json["color"] = m_pieceColor;
    json["type"] = m_pieceType;
    json["operationType"] = m_pieceOperationType;
    json["oldPos"] = (int)m_oldPos;
    json["newPos"] = (int)m_newPos;
    json["moveStates"] = (int)m_moveStates;
}
