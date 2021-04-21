//
//  Author: Broderick Westrope
//  Date: 20/04/21
//
#include "Piece.h"

#ifndef CONSOLE_CHESS_BISHOP_H
#define CONSOLE_CHESS_BISHOP_H

class P_Bishop : public Piece
{
private:
    virtual char GetPiece()
    {
        return 'B';
    }

    bool AreSquaresLegal(Move m, Piece *qpaaBoard[8][8])
    {
        if ((m.iEndCol - m.iStartCol == m.iEndRow - m.iStartRow) || (m.iEndCol - m.iStartCol == m.iStartRow - m.iEndRow))
        {
            // Make sure that all intervening squares are empty
            int iRowOffset = (m.iEndRow - m.iStartRow > 0) ? 1 : -1;
            int iColOffset = (m.iEndCol - m.iStartCol > 0) ? 1 : -1;
            int iCheckRow;
            int iCheckCol;
            for (iCheckRow = m.iStartRow + iRowOffset, iCheckCol = m.iStartCol + iColOffset;
                 iCheckRow != m.iEndRow;
                 iCheckRow = iCheckRow + iRowOffset, iCheckCol = iCheckCol + iColOffset)
            {
                if (qpaaBoard[iCheckRow][iCheckCol] != 0)
                {
                    return false;
                }
            }
            return true;
        }
        return false;
    }

public:
    P_Bishop(char cColor) : Piece(cColor)
    {}

    ~P_Bishop()
    {}
};

#endif //CONSOLE_CHESS_BISHOP_H
