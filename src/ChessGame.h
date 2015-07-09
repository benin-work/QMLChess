#ifndef CHESSGAME_H
#define CHESSGAME_H

#include <QQuickItem>
#include <QSharedPointer>

#include "ChessPiece.h"

class ChessPlayer;

class ChessGame : public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY(ChessTypes::PieceColor moveColor READ moveColor WRITE setMoveColor NOTIFY moveColorChanged)
public:
    explicit ChessGame(QQuickItem *parent = 0);

    Q_INVOKABLE void startNewGame(const QVariant &chessBoard);
    Q_INVOKABLE void alternateMove();

    ChessTypes::PieceColor moveColor() const;

signals:
    void moveColorChanged(ChessTypes::PieceColor moveColor);

public slots:

void setMoveColor(ChessTypes::PieceColor moveColor);

private:
    QSharedPointer<ChessPlayer> m_whitePlayer;
    QSharedPointer<ChessPlayer> m_blackPlayer;

    ChessTypes::PieceColor m_moveColor;
};


#endif // CHESSGAME_H
