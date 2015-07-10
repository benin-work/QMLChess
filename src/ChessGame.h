#ifndef CHESSGAME_H
#define CHESSGAME_H

#include <QQuickItem>
#include <QSharedPointer>

#include "ChessTypes.h"

class ChessPlayer;
class ChessMove;

class ChessGame : public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY(ChessTypes::Color moveColor READ moveColor WRITE setMoveColor NOTIFY moveColorChanged)
    Q_PROPERTY(bool started READ started WRITE setStarted NOTIFY startedChanged)
public:
    explicit ChessGame(QQuickItem *parent = 0);

    Q_INVOKABLE void startNewGame(const QVariant &chessBoard);
    Q_INVOKABLE void stopGame();

    bool started() const;

    void alternateMove();

    ChessTypes::Color moveColor() const;

signals:
    void startedChanged(bool started);
    void moveColorChanged(ChessTypes::Color moveColor);

public slots:
    void setStarted(bool started);
    void setMoveColor(ChessTypes::Color newMoveColor);
    void madeMove(const QSharedPointer<ChessMove> chessMove);

private:
    QSharedPointer<ChessPlayer> m_whitePlayer;
    QSharedPointer<ChessPlayer> m_blackPlayer;

    ChessTypes::Color m_moveColor;

    QList<QSharedPointer<ChessMove>> m_moves;
    bool m_started;
};


#endif // CHESSGAME_H
