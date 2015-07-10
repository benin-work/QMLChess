#ifndef CHESSMOVE_H
#define CHESSMOVE_H

#include <QObject>
#include "ChessTypes.h"

class ChessMove : public QObject
{
    Q_OBJECT
    Q_PROPERTY(ChessTypes::Color pieceColor READ pieceColor WRITE setPieceColor)
    Q_PROPERTY(ChessTypes::Piece pieceType READ pieceType WRITE setPieceType)
    Q_PROPERTY(ChessPos oldPos READ oldPos WRITE setOldPos)
    Q_PROPERTY(ChessPos newPos READ newPos WRITE setNewPos)
    Q_PROPERTY(ChessTypes::MoveStates moveStates READ moveStates WRITE setMoveStates)
public:
    explicit ChessMove(QObject* parent = 0);
    ChessMove(const ChessTypes::Color pieceColor, ChessTypes::Piece pieceType,
              const ChessPos& oldPos, const ChessPos& newPos, ChessTypes::MoveStates moveState);

    ChessTypes::Color pieceColor() const;
    ChessTypes::Piece pieceType() const;

    const ChessPos& oldPos() const;
    const ChessPos& newPos() const;

    ChessTypes::MoveStates moveStates() const;

    // Return move name in Algebraic notation (e.g. Kb6, xe4, Rd7+)
    const QString name() const;

signals:


public slots:
    void setPieceColor(ChessTypes::Color pieceColor);
    void setPieceType(ChessTypes::Piece pieceType);

    void setOldPos(const ChessPos& oldPos);
    void setNewPos(const ChessPos& newPos);

    void setMoveStates(ChessTypes::MoveStates moveStates);

private:
    ChessTypes::Color m_pieceColor;
    ChessTypes::Piece m_pieceType;
    ChessPos m_oldPos;
    ChessPos m_newPos;
    ChessTypes::MoveStates m_moveStates;
};

#endif // CHESSMOVE_H
