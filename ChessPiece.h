#ifndef CHESSPIECE_H
#define CHESSPIECE_H

#include <QQuickItem>

class ChessPiece : public QObject
{
    Q_OBJECT
    Q_ENUMS(PieceColor)
    Q_ENUMS(PieceType)

    Q_PROPERTY(PieceType type READ type)
    Q_PROPERTY(PieceColor color READ color)
    Q_PROPERTY(int boardPos READ boardPos WRITE setBoardPos)
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
        Rock,
        Queen,
        King
    };

public:
    explicit ChessPiece(QObject* parent = Q_NULLPTR);
    ChessPiece(const PieceColor pieceColor, const PieceType pieceType, QQuickItem* chessBoard, const int boardPos = 0);
    virtual ~ChessPiece();

    const PieceColor color() const;
    const PieceType type() const;

    Q_INVOKABLE bool isMoveAvailable(const int newBoardPos) const;

    const int boardPos() const;
    void setBoardPos(const int pos);

    static const int rowFromPos(const int boardPos);
    static const int colFromPos(const int boardPos);

protected:
    virtual bool moveAvailable(const int newBoardPos) const;

protected:
    QQuickItem* m_chessPieceGUI;
    QQuickItem* m_chessBoardGUI;

private:
    PieceColor m_color;
    PieceType m_type;
    int m_boardPos;
};

#endif // CHESSPIECE_H
