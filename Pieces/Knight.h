//
//  Author: Broderick Westrope
//  Date: 20/04/21
//
#include "Piece.h"

#ifndef CONSOLE_CHESS_KNIGHT_H
#define CONSOLE_CHESS_KNIGHT_H

class P_Knight : public Piece
{
private:
    virtual char GetPiece()
    {
        return 'N';
    }

    bool AreSquaresLegal(Move m, Piece *qpaaBoard[8][8])
    {
        if ((m.iStartCol == m.iEndCol + 1) || (m.iStartCol == m.iEndCol - 1))
        {
            if ((m.iStartRow == m.iEndRow + 2) || (m.iStartRow == m.iEndRow - 2))
            {
                return true;
            }
        }
        if ((m.iStartCol == m.iEndCol + 2) || (m.iStartCol == m.iEndCol - 2))
        {
            if ((m.iStartRow == m.iEndRow + 1) || (m.iStartRow == m.iEndRow - 1))
            {
                return true;
            }
        }
        return false;
    }

public:
    P_Knight(char cColor) : Piece(cColor)
    {}

    ~P_Knight()
    {}
};

#endif //CONSOLE_CHESS_KNIGHT_H
