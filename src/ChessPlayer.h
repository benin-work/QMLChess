#ifndef CHESSPLAYER_H
#define CHESSPLAYER_H

#include <QQuickItem>
#include <QPointer>

#include "ChessTypes.h"

class ChessPiece;
class ChessMove;

class ChessPlayer : public QObject, public QEnableSharedFromThis<ChessPlayer>
{
    Q_OBJECT
    Q_PROPERTY(ChessTypes::Color color READ color)
    Q_PROPERTY(bool enable READ enable WRITE setEnable NOTIFY enableChanged)
public:
    ChessPlayer(const ChessTypes::Color playerColor);
    virtual ~ChessPlayer();

    const ChessTypes::Color color() const;

    bool enable() const;

    void setOpponentPlayer(QSharedPointer<ChessPlayer> opponentPlayer);
    QSharedPointer<ChessPlayer> opponentPlayer();

    // Clear all pieces and reset new one on board
    void fillInitialPieces(QQuickItem* chessBoard);

    QSharedPointer<ChessPiece> chessPieceAt(const int boardPos) const;

signals:
    void madeMove(QSharedPointer<ChessMove> chessMove);
    void enableChanged(bool enable);

public slots:
    void setEnable(bool enable);
    void chessMoved(QSharedPointer<ChessMove> chessMove);

protected:
    void addChessPiece(QSharedPointer<ChessPiece> newChessPiece);
    void removeChessPiece(const int boardPos);

private:
    ChessTypes::Color m_color;
    QList<QSharedPointer<ChessPiece>> m_listPieces;
    QWeakPointer<ChessPlayer> m_opponentPlayer;
    bool m_enable;
};

#endif // CHESSPLAYER_H
