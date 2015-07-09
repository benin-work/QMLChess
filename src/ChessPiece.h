#ifndef CHESSPIECE_H
#define CHESSPIECE_H

#include <QQuickItem>
#include <QPointer>

#include "ChessTypes.h"
#include "ChessPos.h"

class ChessPlayer;

class ChessPiece : public QObject
{
    Q_OBJECT
    Q_ENUMS(ChessTypes::PieceColor)
    Q_ENUMS(ChessTypes::PieceType)

    Q_ENUMS(MoveState)

    Q_PROPERTY(ChessTypes::PieceType type READ type)
    Q_PROPERTY(ChessTypes::PieceColor color READ color)
    Q_PROPERTY(int boardPos READ boardPos WRITE setBoardPos NOTIFY boardPosChanged)
public:
    enum MoveState
    {
        MoveNotAvailable = 0,
        MoveAvailable,
        MoveCapture
    };

public:
    explicit ChessPiece(QObject* parent = Q_NULLPTR);
    ChessPiece(const ChessTypes::PieceColor pieceColor, const ChessTypes::PieceType pieceType, QQuickItem* chessBoard, const int boardPos = 0);
    virtual ~ChessPiece();

    const ChessTypes::PieceColor color() const;
    const ChessTypes::PieceType type() const;

    // Position
    const int boardPos() const;
    void setBoardPos(const int boardPos);
    const ChessPos& pos() const;

    // Return piece move availability
    Q_INVOKABLE MoveState moveAvailableState(const int newBoardPos) const;

public slots:

signals:
    void boardPosChanged(const int boardPos);

protected:
    bool isParentPiece(const int boardPos) const;
    bool isOpponentPiece(const int boardPos) const;

    // Check move horizontally, vertically or diagonal
    // through any number of unoccupied squares
    // return MoveState for last occupied square
    MoveState moveThroughAvailable(const ChessPos& newPos) const;

protected:
    // Determine base piece move logic
    virtual MoveState moveAvailable(const ChessPos& newPos) const;

protected:
    QQuickItem* m_chessPieceGUI;
    QQuickItem* m_chessBoardGUI;

private:
    ChessTypes::PieceColor m_color;
    ChessTypes::PieceType m_type;
    ChessPos m_pos;

    friend class ChessPlayer;
    QWeakPointer<ChessPlayer> m_parentPlayer;
};

#endif // CHESSPIECE_H
