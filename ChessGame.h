#ifndef CHESSGAME_H
#define CHESSGAME_H

#include <QQuickItem>
#include <QSharedPointer>

class ChessPlayer;

class ChessGame : public QQuickItem
{
    Q_OBJECT
public:
    explicit ChessGame(QQuickItem *parent = 0);

    Q_INVOKABLE void startNewGame(const QVariant &chessBoard);

signals:

public slots:

private:
    QSharedPointer<ChessPlayer> m_whitePlayer;
    QSharedPointer<ChessPlayer> m_blackPlayer;
};

#endif // CHESSGAME_H
