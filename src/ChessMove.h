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
    Q_PROPERTY(const QString name READ name NOTIFY nameChanged)
public:
    explicit ChessMove(QObject* parent = 0);
    ChessMove(const ChessTypes::Color pieceColor, ChessTypes::Piece pieceType,
              const ChessPos& oldPos, const ChessPos& newPos, ChessTypes::MoveStates moveState);

    ChessMove(const ChessMove& pos);
    ChessMove& operator =(const ChessMove& pos);

    virtual ~ChessMove();

    ChessTypes::Color pieceColor() const;
    ChessTypes::Piece pieceType() const;

    const ChessPos& oldPos() const;
    const ChessPos& newPos() const;

    ChessTypes::MoveStates moveStates() const;

    // Return move name in Algebraic notation (e.g. Kb6, xe4, Rd7+)
    Q_INVOKABLE const QString name() const;

signals:
    void nameChanged(const QString& name);

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

Q_DECLARE_METATYPE(ChessMove)

inline bool operator==(const ChessMove& lhs, const ChessMove& rhs)
{
    return lhs.pieceColor() == rhs.pieceColor() &&
            lhs.pieceType() == rhs.pieceType() &&
            lhs.oldPos() == rhs.oldPos() &&
            lhs.newPos() == rhs.newPos() &&
            lhs.moveStates() == rhs.moveStates();
}

#endif // CHESSMOVE_H
