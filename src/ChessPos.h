#ifndef PIECEPOS_H
#define PIECEPOS_H

#include <QString>

// Helper class for Chess Pieces position
// Determine position in Chess Board index position
// [0 - 63] from top left to bottom down
class ChessPos
{
public:
    ChessPos(const int boardPos = 0);
    ChessPos(const int rowPos, const int colPos);

    const int boardPos() const;
    void setBoardPos(const int newBoardPos);

    const int row() const;
    const int col() const;

    static const int rowPos(const int boardPos);
    static const int colPos(const int boardPos);
    static const int boardPos(const int rowPos, const int colPos);

    // Return position in Algebraic notation (i.e. a1, f5, c2 etc)
    const QString name() const;

private:
    int m_boardPos;
};

#endif // PIECEPOS_H
