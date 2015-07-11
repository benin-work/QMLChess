#include <QDebug>
#include <QQmlEngine>
#include <QQmlComponent>

#include "ChessGame.h"
#include "ChessPlayer.h"
#include "ChessMove.h"

ChessGame::ChessGame(QQuickItem *parent /*= 0*/)
: QQuickItem(parent)
, m_moveColor(ChessTypes::White)
, m_started(false)
{
}

void ChessGame::startNewGame(const QVariant &chessBoard)
{
    qDebug() << "Start new game";

    QQuickItem* chessBoardObject = qobject_cast<QQuickItem*>(chessBoard.value<QQuickItem*>());

    // Prepeare players
    m_whitePlayer.reset(new ChessPlayer(ChessTypes::White));
    m_blackPlayer.reset(new ChessPlayer(ChessTypes::Black));

    m_whitePlayer->setOpponentPlayer(m_blackPlayer);
    m_blackPlayer->setOpponentPlayer(m_whitePlayer);

    m_whitePlayer->fillInitialPieces(chessBoardObject);
    m_blackPlayer->fillInitialPieces(chessBoardObject);

    QObject::connect(m_whitePlayer.data(), SIGNAL(madeMove(QSharedPointer<ChessMove>)),
               this, SLOT(madeMove(const QSharedPointer<ChessMove>)));
    QObject::connect(m_blackPlayer.data(), SIGNAL(madeMove(QSharedPointer<ChessMove>)),
               this, SLOT(madeMove(const QSharedPointer<ChessMove>)));

    // Clear history
    m_moves.clear();
    emit chessMovesChanged(chessMoves());

    // Set initial move
    m_moveColor = ChessTypes::Black; // To trigger setMove
    setMoveColor(ChessTypes::White);

    setStarted(true);
}

void ChessGame::stopGame()
{
    // Clear Players
    m_whitePlayer.reset();
    m_blackPlayer.reset();

    setStarted(false);

    // Clear history
    clearHistory();
}

void ChessGame::clearHistory()
{
    // Hack to allow QML remove items from list
    auto movesCopy = m_moves;

    m_moves.clear();
    emit chessMovesChanged(chessMoves());

    movesCopy.clear();
}

bool ChessGame::started() const
{
    return m_started;
}

void ChessGame::setStarted(bool started)
{
    if (m_started == started)
        return;

    m_started = started;
    emit startedChanged(m_started);
}

void ChessGame::alternateMove()
{
    setMoveColor(moveColor() == ChessTypes::White ?
        ChessTypes::Black : ChessTypes::White);
}

ChessTypes::Color ChessGame::moveColor() const
{
    return m_moveColor;
}

void ChessGame::setMoveColor(ChessTypes::Color newMoveColor)
{
    if (m_moveColor == newMoveColor)
        return;

    m_moveColor = newMoveColor;

    m_whitePlayer->setEnable(moveColor() == ChessTypes::White);
    m_blackPlayer->setEnable(moveColor() == ChessTypes::Black);

    emit moveColorChanged(newMoveColor);
}

void ChessGame::madeMove(const QSharedPointer<ChessMove> chessMove)
{
    qDebug() << QString("%1: %2").
        arg(ChessTypes::colorName(chessMove->pieceColor()), chessMove->name());

    //Q_ASSERT(moveColor() == chessMove->pieceColor());
    m_moves << chessMove;

    emit chessMovesChanged(chessMoves());

    alternateMove();
}

QQmlListProperty<ChessMove> ChessGame::chessMoves()
{
    return QQmlListProperty<ChessMove>(this, &m_moves, &ChessGame::mlist_append, &ChessGame::mlist_count,
                                       &ChessGame::mlist_at, &ChessGame::mlist_clear);
}
