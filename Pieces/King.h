//
//  Author: Broderick Westrope
//  Date: 20/04/21
//
#include "Piece.h"

#ifndef CONSOLE_CHESS_KING_H
#define CONSOLE_CHESS_KING_H

class P_King : public Piece
{
private:
    virtual char GetPiece()
    {
        return 'K';
    }

    bool AreSquaresLegal(Move m, Piece *qpaaBoard[8][8])
    {
        int iRowDelta = m.iEndRow - m.iStartRow;
        int iColDelta = m.iEndCol - m.iStartCol;
        if (((iRowDelta >= -1) && (iRowDelta <= 1)) &&
            ((iColDelta >= -1) && (iColDelta <= 1)))
        {
            return true;
        }
        return false;
    }

public:
    P_King(char cColor) : Piece(cColor)
    {}

    ~P_King()
    {}
};


#endif //CONSOLE_CHESS_KING_H
