//
// Created by ascle on 20/04/2021.
//

#ifndef CONSOLE_CHESS_ROOK_H
#define CONSOLE_CHESS_ROOK_H

#include "Piece.h"

class P_Rook : public Piece
{
private:
    virtual char GetPiece()
    {
        return 'R';
    }

    bool AreSquaresLegal(Move m, Board *board)
    {
        if (m.iStartRow == m.iEndRow)
        {
            // Make sure that all invervening squares are empty
            int iColOffset = (m.iEndCol - m.iStartCol > 0) ? 1 : -1;
            for (int iCheckCol = m.iStartCol + iColOffset; iCheckCol != m.iEndCol; iCheckCol = iCheckCol + iColOffset)
            {
                if (board->mqpaaBoard[m.iStartRow][iCheckCol] != nullptr)
                {
                    return false;
                }
            }
            return true;
        }
        else if (m.iEndCol == m.iStartCol)
        {
            // Make sure that all invervening squares are empty
            int iRowOffset = (m.iEndRow - m.iStartRow > 0) ? 1 : -1;
            for (int iCheckRow = m.iStartRow + iRowOffset; iCheckRow != m.iEndRow; iCheckRow = iCheckRow + iRowOffset)
            {
                if (board->mqpaaBoard[iCheckRow][m.iStartCol] != nullptr)
                {
                    return false;
                }
            }
            return true;
        }
        return false;
    }

public:
    P_Rook(char cColor) : Piece(cColor)
    {}

    ~P_Rook()
    {}

    bool canCastle = true;
};


#endif //CONSOLE_CHESS_ROOK_H
