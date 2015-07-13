// Copyright (C) 2015 Vladimir Karlov <vkarlov.work@gmail.com>
// All rights reserved.
//
// Name:        ChessPiece.h
// Date:        2015.07.13
// Author:      Vladimir Karlov
// Description: Basic chess piece logic (creation, movement, etc)

#ifndef CHESSPIECE_H
#define CHESSPIECE_H

#include <QQuickItem>
#include <QPointer>

#include "ChessTypes.h"

class ChessPlayer;


class ChessPiece : public QObject
{
    Q_OBJECT
    Q_PROPERTY(ChessTypes::Piece type READ type)
    Q_PROPERTY(ChessTypes::Color color READ color)
    Q_PROPERTY(int boardPos READ boardPos WRITE setBoardPos NOTIFY boardPosChanged)
    Q_PROPERTY(bool enable READ enable WRITE setEnable NOTIFY enableChanged)
public:
    explicit ChessPiece(QObject* parent = Q_NULLPTR);
    ChessPiece(const ChessTypes::Color pieceColor, const ChessTypes::Piece pieceType,
               QQuickItem* chessBoard, const int boardPos = 0);
    virtual ~ChessPiece();

    const ChessTypes::Color color() const;
    const ChessTypes::Piece type() const;

    // Position
    const int boardPos() const;
    void setBoardPos(const int boardPos);
    const ChessPos& pos() const;

    bool enable() const;

    // Return piece move availability
    // int as ChessTypes::MoveState
    Q_INVOKABLE int moveAvailableStates(const int newBoardPos) const;

    // Make move
    Q_INVOKABLE void move(const int newBoardPos);

public slots:
    void setEnable(bool enable);

signals:
    void boardPosChanged(const int boardPos);
    void moved(ChessMovePtr chessMove);

    void enableChanged(bool enable);

protected:
    bool isParentPiece(const int boardPos) const;
    bool isOpponentPiece(const int boardPos) const;
    bool isOpponentPieceEnPassant(const int boardPos) const;

    // Check move horizontally, vertically or diagonal
    // through any number of unoccupied squares
    // return MoveState for last occupied square
    ChessTypes::MoveState moveThroughAvailable(const ChessPos& newPos) const;

protected:
    // Determine base piece move logic
    virtual ChessTypes::MoveStates moveAvailable(const ChessPos& newPos) const;

protected:
    friend class ChessPlayer;
    QQuickItem* m_chessPieceGUI;
    QQuickItem* m_chessBoardGUI;

private:
    ChessTypes::Color m_color;
    ChessTypes::Piece m_type;
    ChessPos m_pos;

    friend class ChessPlayer;
    QWeakPointer<ChessPlayer> m_parentPlayer;
    bool m_enable;
};

#endif // CHESSPIECE_H
