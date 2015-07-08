#ifndef CHESSPLAYER_H
#define CHESSPLAYER_H

#include <QQuickItem>
#include <QSharedPointer>

#include "ChessPiece.h"

class ChessPlayer : public QObject
{
    Q_OBJECT

public:
    ChessPlayer(const ChessPiece::PieceColor playerColor);

    void fillInitialPieces(QQuickItem* chessBoard);

    const ChessPiece::PieceColor color() const;

signals:

public slots:

private:
    ChessPiece::PieceColor m_color;
    QList<QSharedPointer<ChessPiece>> m_listPieces;
};

#endif // CHESSPLAYER_H
