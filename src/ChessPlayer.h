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
    Q_PROPERTY(QSharedPointer<ChessMove> lastMove READ lastMove WRITE setLastMove)
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

    QSharedPointer<ChessMove> lastMove() const;

signals:
    void madeMove(QSharedPointer<ChessMove> chessMove);
    void enableChanged(bool enable);

public slots:
    void setEnable(bool enable);
    void chessMoved(QSharedPointer<ChessMove> chessMove);

    void setLastMove(QSharedPointer<ChessMove> lastMove);

protected:
    void addChessPiece(QSharedPointer<ChessPiece> newChessPiece);
    QSharedPointer<ChessPiece> removeChessPiece(const int boardPos);

private:
    ChessTypes::Color m_color;
    bool m_enable;

    QList<QSharedPointer<ChessPiece>> m_listPieces;
    QWeakPointer<ChessPlayer> m_opponentPlayer;
    QSharedPointer<ChessMove> m_lastMove;
};

#endif // CHESSPLAYER_H
