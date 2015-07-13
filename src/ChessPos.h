// Copyright (C) 2015 Vladimir Karlov <vkarlov.work@gmail.com>
// All rights reserved.
//
// Name:        ChessPos.h
// Date:        2015.07.13
// Author:      Vladimir Karlov
// Description: Helper class for Chess Pieces position. Determine
//              the position in Chess Board index position [0 - 63]
//              from top left to bottom down

#ifndef CHESSPOS_H
#define CHESSPOS_H

#include <QObject>

class ChessPos: public QObject
{
    Q_OBJECT
public:
    explicit ChessPos(QObject* parent = 0);
    ChessPos(const int boardPos);
    ChessPos(const int row, const int col);

    ChessPos(const ChessPos& pos);
    ChessPos& operator =(const ChessPos& pos);

    // Return boardPos
    operator int () const;

    const int boardPos() const;
    void setBoardPos(const int newBoardPos);

    const int row() const;
    const int col() const;

    static const int row(const int boardPos);
    static const int col(const int boardPos);
    static const int boardPos(const int row, const int col);

    // Return position in Algebraic notation (i.e. a1, f5, c2 etc)
    const QString name() const;

private:
    int m_boardPos;
};

Q_DECLARE_METATYPE(ChessPos)

inline bool operator==(const ChessPos& lhs, const ChessPos& rhs)
{
    return (lhs.boardPos() == rhs.boardPos());
}

#endif // CHESSPOS_H
