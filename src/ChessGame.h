#ifndef CHESSGAME_H
#define CHESSGAME_H

#include <QQuickItem>
#include <QSharedPointer>

#include "ChessTypes.h"
#include "ChessMove.h"

class ChessPlayer;
class ChessMove;

class ChessGame : public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY(ChessTypes::Color moveColor READ moveColor WRITE setMoveColor NOTIFY moveColorChanged)
    Q_PROPERTY(bool started READ started WRITE setStarted NOTIFY startedChanged)
    Q_PROPERTY(QQmlListProperty<ChessMove> chessMoves READ chessMoves NOTIFY chessMovesChanged)
    Q_PROPERTY(ChessMove activeMove READ activeMove NOTIFY activeMoveChanged)
public:
    explicit ChessGame(QQuickItem *parent = 0);

    bool started() const;

    ChessTypes::Color moveColor() const;

    QQmlListProperty<ChessMove> chessMoves();
    const ChessMove& activeMove() const;

    // Actionable
    Q_INVOKABLE void startNewGame(const QVariant &chessBoard);
    Q_INVOKABLE void stopGame();

    // Move through history
    Q_INVOKABLE void moveBackward();
    Q_INVOKABLE void moveForward();


signals:
    void startedChanged(bool started);
    void moveColorChanged(ChessTypes::Color moveColor);

    void chessMovesChanged(QQmlListProperty<ChessMove> chessMoves);
    void activeMoveChanged(const ChessMove& activeMove);

public slots:
    void setStarted(bool started);
    void setMoveColor(ChessTypes::Color newMoveColor);
    void madeMove(const ChessMovePtr chessMove);

    void setActiveMove(ChessMovePtr activeMove);

private:
    void clearHistory();
    void alternateMove();

private:
    bool m_started;
    QSharedPointer<ChessPlayer> m_whitePlayer;
    QSharedPointer<ChessPlayer> m_blackPlayer;

    ChessTypes::Color m_moveColor;

    QList<ChessMovePtr> m_moves;
    ChessMovePtr m_activeMove;
    QListIterator<ChessMovePtr> m_activeMoveIter;
};


#endif // CHESSGAME_H
