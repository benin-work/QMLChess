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

void ChessPlayer::fillInitialPieces(QQuickItem* chessBoard)
{
    qDebug() << "Fill initial pieces: " << Q_FUNC_INFO;

    Q_ASSERT(chessBoard);

    m_listPieces.clear();


    // Pawns
    int dxPos = m_color == ChessPiece::White ? 48 : 8;
    for(int i = 0; i < 8; i++)
    {
        QSharedPointer<ChessPiece> piecePawn(new ChessPiecePawn(m_color, chessBoard, dxPos + i));
        m_listPieces.append(piecePawn);
    }

    dxPos = m_color == ChessPiece::White ? 56 : 0;
    QSharedPointer<ChessPiece> pieceRockL(new ChessPieceRock(m_color, chessBoard, dxPos + 0));
    QSharedPointer<ChessPiece> pieceRockR(new ChessPieceRock(m_color, chessBoard, dxPos + 7));

    m_listPieces.append(pieceRockL);
    m_listPieces.append(pieceRockR);
}

const ChessPiece::PieceColor ChessPlayer::color() const
{
    return m_color;
}



