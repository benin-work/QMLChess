#include <QJsonArray>
#include <QJsonDocument>

#include "ChessGameplay.h"
#include "ChessPlayer.h"

ChessGameplay::ChessGameplay(QQuickItem* parent /*=0*/)
: ChessGame(parent)
, m_activeMove(-1)
{

}

void ChessGameplay::moveMade(const ChessMovePtr chessMove)
{
    ChessGame::moveMade(chessMove);

    setActiveMove(m_moves.length() - 1);
}

int ChessGameplay::activeMove() const
{
    return m_activeMove;
}

void ChessGameplay::setActiveMove(int activeMove)
{
    if (m_activeMove == activeMove)
        return;

    m_activeMove = activeMove;

    emit activeMoveChanged(activeMove);
    emit hasPrevMoveChanged(hasPrevMove());
    emit hasNextMoveChanged(hasNextMove());
}

void ChessGameplay::movePrev()
{
    if (!hasPrevMove())
        return;

    ChessMovePtr chessMove(m_moves.at(activeMove()));
    Q_ASSERT(chessMove);
    setActiveMove(activeMove() - 1);

    chessPlayer(chessMove->pieceColor())->playPrev(chessMove);
}

void ChessGameplay::moveNext()
{
    if (!hasNextMove())
        return;

    setActiveMove(activeMove() + 1);
    ChessMovePtr chessMove(m_moves.at(activeMove()));
    Q_ASSERT(chessMove);

    chessPlayer(chessMove->pieceColor())->playNext(chessMove);
}

void ChessGameplay::moveAt(const int moveIndex)
{
    if (moveIndex > m_moves.length() || moveIndex < 0)
        return;

    while (moveIndex > activeMove())
        moveNext();
    while (moveIndex < activeMove())
        movePrev();
}

bool ChessGameplay::hasNextMove() const
{
    return !m_moves.empty() && activeMove() < m_moves.length() - 1;
}

bool ChessGameplay::hasPrevMove() const
{
    return !m_moves.empty() && activeMove() >= 0;
}

void ChessGameplay::save(const QString& fileName)
{
    qDebug() << "Save game to: " << fileName;

    QFile saveFile(QUrl(fileName).toLocalFile());

    if (!saveFile.open(QIODevice::WriteOnly)) {
        qWarning() << "Couldn't open file: " + fileName;
        return;
    }

    QJsonObject movesObject;
    QJsonArray movesJArray;
    foreach (const auto& chessMove, m_moves)
    {
        QJsonObject moveObject;
        chessMove->write(moveObject);
        movesJArray.append(moveObject);
    }
    movesObject["moves"] = movesJArray;

    QJsonDocument saveDoc(movesObject);
    saveFile.write(saveDoc.toJson());
    saveFile.close();
}

void ChessGameplay::load(const QString& fileName, const QVariant& chessBoard)
{
    qDebug() << "Load game from: " << fileName;

    QFile loadFile(QUrl(fileName).toLocalFile());

    if (!loadFile.open(QIODevice::ReadOnly)) {
        qWarning() << "Couldn't open file: " + fileName;
        return;
    }

    stopGame();
    startNewGame(chessBoard);

    QByteArray saveData = loadFile.readAll();
    QJsonDocument loadDoc(QJsonDocument::fromJson(saveData));

    QJsonArray movesJArray = loadDoc.object()["moves"].toArray();
    for (int moveIndex = 0; moveIndex < movesJArray.size(); ++moveIndex)
    {
        QJsonObject moveObject = movesJArray[moveIndex].toObject();
        ChessMove move;
        move.read(moveObject);
        m_moves << ChessMovePtr(new ChessMove(move));
    }

    emit chessMovesChanged(chessMoves());

    // To trigger setter
    m_activeMove = 0;
    setActiveMove(-1);
}
