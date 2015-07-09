#ifndef CHESSTYPES
#define CHESSTYPES

#include <QObject>

class ChessTypes: public QObject
{
    Q_OBJECT
    Q_ENUMS(PieceColor PieceType)
public:

    enum PieceColor
    {
        White = 0,
        Black
    };

    enum PieceType
    {
        Pawn = 0,
        Bishop,
        Knight,
        Rook,
        Queen,
        King
    };
};

#endif // CHESSTYPES

