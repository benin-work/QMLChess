#ifndef CHESSPLAYER_H
#define CHESSPLAYER_H

#include <QQuickItem>
#include <QPointer>

#include "ChessPiece.h"

class ChessPlayer : public QObject, public QEnableSharedFromThis<ChessPlayer>
{
    Q_OBJECT

public:
    ChessPlayer(const ChessPiece::PieceColor playerColor);
    virtual ~ChessPlayer();

    const ChessPiece::PieceColor color() const;

    void setOppositPlayer(QSharedPointer<ChessPlayer> oppositePlayer);

    // Clear all pieces and reset new one on board
    void fillInitialPieces(QQuickItem* chessBoard);

    QSharedPointer<ChessPiece> chessPieceAt(const int boardPos) const;

signals:

public slots:

protected:
    void addChessPiece(QSharedPointer<ChessPiece> newChessPiece);

private:
    ChessPiece::PieceColor m_color;
    QList<QSharedPointer<ChessPiece>> m_listPieces;
    QWeakPointer<ChessPlayer> m_oppositPlayer;
};

#endif // CHESSPLAYER_H
