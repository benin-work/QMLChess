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

    const int boardPos() const;
    void setBoardPos(const int newBoardPos);

    const int row() const;
    const int col() const;

    static const int rowFromPos(const int boardPos);
    static const int colFromPos(const int boardPos);

    const QString chessPosName() const;

private:
    int m_boardPos;
};

#endif // PIECEPOS_H
