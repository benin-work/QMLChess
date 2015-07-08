#ifndef CHESSPIECE_H
#define CHESSPIECE_H

#include <QQuickItem>
#include <QPointer>

#include "ChessPos.h"

class ChessPlayer;

class ChessPiece : public QObject
{
    Q_OBJECT
    Q_ENUMS(PieceColor)
    Q_ENUMS(PieceType)

    Q_PROPERTY(PieceType type READ type)
    Q_PROPERTY(PieceColor color READ color)
    Q_PROPERTY(int boardPos READ boardPos WRITE setBoardPos NOTIFY boardPosChanged)
public:
    enum PieceColor
    {
        White = 0,
        Black
    };

    enum PieceType
    {
        Pawn = 0,
        Bishop,
        Knight,
        Rook,
        Queen,
        King
    };

public:
    explicit ChessPiece(QObject* parent = Q_NULLPTR);
    ChessPiece(const PieceColor pieceColor, const PieceType pieceType, QQuickItem* chessBoard, const int boardPos = 0);
    virtual ~ChessPiece();

    const PieceColor color() const;
    const PieceType type() const;

    // Position
    const int boardPos() const;
    void setBoardPos(const int boardPos);
    const ChessPos& pos() const;

    Q_INVOKABLE bool isMoveAvailable(const int newBoardPos) const;

public slots:

signals:
    void boardPosChanged(const int boardPos);

protected:
    bool isParentPiece(const int boardPos) const;

    bool moveDiagonalAvailable(const ChessPos& newPos) const;
    bool moveHorVertAvailable(const ChessPos& newPos) const;

protected:
    // Determine base piece move logic
    virtual bool moveAvailable(const ChessPos& newPos) const;

protected:
    QQuickItem* m_chessPieceGUI;
    QQuickItem* m_chessBoardGUI;

private:
    PieceColor m_color;
    PieceType m_type;
    ChessPos m_pos;

    friend class ChessPlayer;
    QWeakPointer<ChessPlayer> m_parentPlayer;
};

#endif // CHESSPIECE_H
