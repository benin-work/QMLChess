#ifndef CHESSMOVE_H
#define CHESSMOVE_H

#include <QObject>
#include "ChessTypes.h"

class ChessMove : public QObject
{
    Q_OBJECT
    Q_PROPERTY(ChessTypes::Color pieceColor READ pieceColor WRITE setPieceColor)
    Q_PROPERTY(ChessTypes::Piece pieceType READ pieceType WRITE setPieceType)
    Q_PROPERTY(ChessTypes::Piece operationType READ operationType WRITE setPieceOperationType NOTIFY pieceOperationTypeChanged)
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

    // Operation pice target
    // for capture - capture figure Type
    // for promotion - promotion figure Type
    ChessTypes::Piece operationType() const;

    const ChessPos& oldPos() const;
    const ChessPos& newPos() const;

    ChessTypes::MoveStates moveStates() const;

    // Return move name in Algebraic notation (e.g. Kb6, xe4, Rd7+)
    Q_INVOKABLE const QString name() const;


signals:
    void nameChanged(const QString& name);
    void pieceOperationTypeChanged(ChessTypes::Piece operationType);

public slots:
    void setPieceColor(ChessTypes::Color pieceColor);
    void setPieceType(ChessTypes::Piece pieceType);

    void setOldPos(const ChessPos& oldPos);
    void setNewPos(const ChessPos& newPos);

    void setMoveStates(ChessTypes::MoveStates moveStates);

    void setPieceOperationType(ChessTypes::Piece operationType);

private:
    ChessTypes::Color m_pieceColor;
    ChessTypes::Piece m_pieceType;
    ChessPos m_oldPos;
    ChessPos m_newPos;
    ChessTypes::MoveStates m_moveStates;
    ChessTypes::Piece m_pieceOperationType;
};

Q_DECLARE_METATYPE(ChessMove)

inline bool operator==(const ChessMove& lhs, const ChessMove& rhs)
{
    return lhs.pieceColor() == rhs.pieceColor() &&
            lhs.pieceType() == rhs.pieceType() &&
            lhs.oldPos() == rhs.oldPos() &&
            lhs.newPos() == rhs.newPos() &&
            lhs.moveStates() == rhs.moveStates() &&
            lhs.operationType() == rhs.operationType();
}

#endif // CHESSMOVE_H
