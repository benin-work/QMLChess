#include <QDebug>
#include <QQmlEngine>
#include <QQmlComponent>

#include "ChessGame.h"
#include "ChessPlayer.h"
#include "ChessMove.h"

ChessGame::ChessGame(QQuickItem *parent /*= 0*/)
: QQuickItem(parent)
, m_moveColor(ChessTypes::White)
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

    // Set initial move
    m_moveColor = ChessTypes::Black; // To trigger setMove
    setMoveColor(ChessTypes::White);
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

    alternateMove();
}
