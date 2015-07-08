#include <QDebug>
#include <QQmlEngine>
#include <QQmlComponent>

#include "ChessPlayer.h"
#include "ChessPieces.h"


ChessPlayer::ChessPlayer(const ChessPiece::PieceColor playerColor)
: QObject()
, m_color(playerColor)
{
}

ChessPlayer::~ChessPlayer()
{
    qDebug() << "Player " << m_color << " destroyed";
}

void ChessPlayer::fillInitialPieces(QQuickItem* chessBoard)
{
    qDebug() << "Fill initial pieces: " << Q_FUNC_INFO;

    Q_ASSERT(chessBoard);

    m_listPieces.clear();

    // Pawns
    int dxPos = m_color == ChessPiece::White ? 48 : 8;
    for(int i = 0; i < 8; i++)
        addChessPiece(QSharedPointer<ChessPiece>(new ChessPiecePawn(m_color, chessBoard, dxPos + i)));

    // Pieces
    dxPos = m_color == ChessPiece::White ? 56 : 0;
    addChessPiece(QSharedPointer<ChessPiece>(new ChessPieceRock(m_color, chessBoard, dxPos + 0)));
    addChessPiece(QSharedPointer<ChessPiece>(new ChessPieceRock(m_color, chessBoard, dxPos + 7)));
    addChessPiece(QSharedPointer<ChessPiece>(new ChessPieceKing(m_color, chessBoard, dxPos + 4)));
}

QSharedPointer<ChessPiece> ChessPlayer::chessPieceAt(const int boardPos) const
{
    foreach(auto chessPiece, m_listPieces)
        if (chessPiece->boardPos() == boardPos)
            return chessPiece;

    return QSharedPointer<ChessPiece>();
}

void ChessPlayer::addChessPiece(QSharedPointer<ChessPiece> newChessPiece)
{
    newChessPiece->m_parentPlayer = sharedFromThis();
    m_listPieces.append(newChessPiece);
}

const ChessPiece::PieceColor ChessPlayer::color() const
{
    return m_color;
}

void ChessPlayer::setOppositPlayer(QSharedPointer<ChessPlayer> oppositePlayer)
{
    m_oppositPlayer = oppositePlayer;
}



