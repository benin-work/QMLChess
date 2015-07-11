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
, m_activeMoveIter(m_moves)
{
}

void ChessGame::clearHistory()
{
    // Presave items,
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

void ChessGame::madeMove(const ChessMovePtr chessMove)
{
    qDebug() << QString("%1: %2").
        arg(ChessTypes::colorName(chessMove->pieceColor()), chessMove->name());

    Q_ASSERT(moveColor() == chessMove->pieceColor());
    m_moves << chessMove;

    setActiveMove(chessMove);
    m_activeMoveIter = m_moves;
    m_activeMoveIter.toBack();

    emit chessMovesChanged(chessMoves());

    alternateMove();
}

void ChessGame::setActiveMove(ChessMovePtr activeMove)
{
    if (m_activeMove == activeMove)
        return;

    m_activeMove = activeMove;
    emit activeMoveChanged(*activeMove.data());
}

// Accessors for move list
namespace
{
typedef QList<ChessMovePtr> MoveList;
static void mlist_append(QQmlListProperty<ChessMove> *p, ChessMove *v) {
    reinterpret_cast<MoveList *>(p->data)->append(ChessMovePtr(v));
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
}
QQmlListProperty<ChessMove> ChessGame::chessMoves()
{
    return QQmlListProperty<ChessMove>(this, &m_moves, &mlist_append, &mlist_count,
                                       &mlist_at, &mlist_clear);
}

const ChessMove &ChessGame::activeMove() const
{
    return *m_activeMove.data();
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

    QObject::connect(m_whitePlayer.data(), SIGNAL(madeMove(ChessMovePtr)),
               this, SLOT(madeMove(const ChessMovePtr)));
    QObject::connect(m_blackPlayer.data(), SIGNAL(madeMove(ChessMovePtr)),
               this, SLOT(madeMove(const ChessMovePtr)));

    // Clear movement history
    clearHistory();

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

    // Clear movement history
    clearHistory();
}

void ChessGame::moveBackward()
{
    if (!m_moves.empty() && m_activeMoveIter.hasPrevious())
    {
        ChessMovePtr movePrev(m_activeMoveIter.previous());

        auto player = movePrev->pieceColor() == ChessTypes::White ?
                    m_whitePlayer : m_blackPlayer;

        ChessMovePtr moveBack(new ChessMove(*movePrev));
        auto oldPos = moveBack->oldPos();
        moveBack->setOldPos(moveBack->newPos());
        moveBack->setNewPos(oldPos);

        player->movePiece(moveBack);

        //player->;
    }
}

void ChessGame::moveForward()
{
    if (!m_moves.empty() && m_activeMoveIter.hasNext())
    {
        ChessMovePtr moveNext(m_activeMoveIter.next());

        auto player = moveNext->pieceColor() == ChessTypes::White ?
                    m_whitePlayer : m_blackPlayer;

        player->movePiece(moveNext);

        //player->;
    }
}
