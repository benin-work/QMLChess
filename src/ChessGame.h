#ifndef CHESSGAME_H
#define CHESSGAME_H

#include <QQuickItem>
#include <QSharedPointer>

#include "ChessTypes.h"
#include "ChessMove.h"

class ChessPlayer;

class ChessGame : public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY(ChessTypes::Color moveColor READ moveColor WRITE setMoveColor NOTIFY moveColorChanged)
    Q_PROPERTY(bool started READ started WRITE setStarted NOTIFY startedChanged)
    Q_PROPERTY(QQmlListProperty<ChessMove> chessMoves READ chessMoves NOTIFY chessMovesChanged)
public:
    explicit ChessGame(QQuickItem *parent = 0);

    Q_INVOKABLE void startNewGame(const QVariant &chessBoard);
    Q_INVOKABLE void stopGame();

    bool started() const;

    void alternateMove();

    ChessTypes::Color moveColor() const;

    QQmlListProperty<ChessMove> chessMoves();

signals:
    void startedChanged(bool started);
    void moveColorChanged(ChessTypes::Color moveColor);

    void chessMovesChanged(QQmlListProperty<ChessMove> chessMoves);

public slots:
    void setStarted(bool started);
    void setMoveColor(ChessTypes::Color newMoveColor);
    void madeMove(const QSharedPointer<ChessMove> chessMove);

private:
    void clearHistory();

private:
    QSharedPointer<ChessPlayer> m_whitePlayer;
    QSharedPointer<ChessPlayer> m_blackPlayer;

    ChessTypes::Color m_moveColor;

    QList<QSharedPointer<ChessMove>> m_moves;
    bool m_started;

    typedef QList<QSharedPointer<ChessMove>> MoveList;
    static void mlist_append(QQmlListProperty<ChessMove> *p, ChessMove *v) {
        reinterpret_cast<MoveList *>(p->data)->append(QSharedPointer<ChessMove>(v));
    }
    static int mlist_count(QQmlListProperty<ChessMove> *p) {
        return reinterpret_cast<MoveList *>(p->data)->count();
    }
    static ChessMove* mlist_at(QQmlListProperty<ChessMove> *p, int idx) {
        return reinterpret_cast<MoveList *>(p->data)->at(idx).data();
    }
    static void mlist_clear(QQmlListProperty<ChessMove> *p) {
        return reinterpret_cast<MoveList *>(p->data)->clear();
    }
};


#endif // CHESSGAME_H
