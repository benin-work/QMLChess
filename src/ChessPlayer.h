#ifndef CHESSPLAYER_H
#define CHESSPLAYER_H

#include <QQuickItem>
#include <QPointer>

#include "ChessTypes.h"

class ChessPiece;

class ChessPlayer : public QObject, public QEnableSharedFromThis<ChessPlayer>
{
    Q_OBJECT
public:
    ChessPlayer(const ChessTypes::PieceColor playerColor);
    virtual ~ChessPlayer();

    const ChessTypes::PieceColor color() const;

    void setOpponentPlayer(QSharedPointer<ChessPlayer> opponentPlayer);
    QSharedPointer<ChessPlayer> opponentPlayer();

    // Clear all pieces and reset new one on board
    void fillInitialPieces(QQuickItem* chessBoard);

    QSharedPointer<ChessPiece> chessPieceAt(const int boardPos) const;

signals:

public slots:

protected:
    void addChessPiece(QSharedPointer<ChessPiece> newChessPiece);

private:
    ChessTypes::PieceColor m_color;
    QList<QSharedPointer<ChessPiece>> m_listPieces;
    QWeakPointer<ChessPlayer> m_opponentPlayer;
};

#endif // CHESSPLAYER_H
