#ifndef CHESSPLAYER_H
#define CHESSPLAYER_H

#include <QQuickItem>
#include <QPointer>

#include "ChessTypes.h"

class ChessPiece;

class ChessPlayer : public QObject, public QEnableSharedFromThis<ChessPlayer>
{
    Q_OBJECT
    Q_PROPERTY(ChessTypes::Color color READ color)
    Q_PROPERTY(bool enable READ enable WRITE setEnable NOTIFY enableChanged)
    Q_PROPERTY(ChessMovePtr lastMove READ lastMove WRITE setLastMove)
public:
    ChessPlayer(const ChessTypes::Color playerColor);
    virtual ~ChessPlayer();

    const ChessTypes::Color color() const;

    bool enable() const;

    void setOpponentPlayer(QSharedPointer<ChessPlayer> opponentPlayer);
    QSharedPointer<ChessPlayer> opponentPlayer();

    // Clear all pieces and reset new one on board
    void fillInitialPieces(QQuickItem* chessBoard);

    // Retrive piece at board position
    ChessPiecePtr chessPieceAt(const int boardPos) const;

    ChessMovePtr lastMove() const;

    // Operations for playback
    void moveNext(ChessMovePtr chessMove);
    void movePrev(ChessMovePtr chessMove);

signals:
    void madeMove(ChessMovePtr chessMove);
    void enableChanged(bool enable);

public slots:
    void setEnable(bool enable);
    void chessMoved(ChessMovePtr chessMove);

    void setLastMove(ChessMovePtr lastMove);

protected:
    void addChessPiece(ChessPiecePtr newChessPiece);
    ChessPiecePtr removeChessPiece(const int boardPos);

private:
    ChessTypes::Color m_color;
    bool m_enable;

    QList<ChessPiecePtr> m_listPieces;
    QWeakPointer<ChessPlayer> m_opponentPlayer;
    ChessMovePtr m_lastMove;
};

#endif // CHESSPLAYER_H
