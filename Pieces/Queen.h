//
//  Author: Broderick Westrope
//  Date: 20/04/21
//
#include "Piece.h"
#include "../Board.h"

#ifndef CONSOLE_CHESS_QUEEN_H
#define CONSOLE_CHESS_QUEEN_H

class P_Queen : public Piece
{
private:
    virtual char GetPiece()
    {
        return 'Q';
    }

    bool AreSquaresLegal(Move m, Board *board)
    {
        if (m.iStartRow == m.iEndRow)
        {
            // Make sure that all intervening squares are empty
            int iColOffset = (m.iEndCol - m.iStartCol > 0) ? 1 : -1;
            for (int iCheckCol = m.iStartCol + iColOffset; iCheckCol != m.iEndCol; iCheckCol = iCheckCol + iColOffset)
            {
                if (board[m.iStartRow][iCheckCol] != 0)
                {
                    return false;
                }
            }
            return true;
        }
        else if (m.iEndCol == m.iStartCol)
        {
            // Make sure that all intervening squares are empty
            int iRowOffset = (m.iEndRow - m.iStartRow > 0) ? 1 : -1;
            for (int iCheckRow = m.iStartRow + iRowOffset; iCheckRow != m.iEndRow; iCheckRow = iCheckRow + iRowOffset)
            {
                if (board[iCheckRow][m.iStartCol] != 0)
                {
                    return false;
                }
            }
            return true;
        }
        else if ((m.iEndCol - m.iStartCol == m.iEndRow - m.iStartRow) || (m.iEndCol - m.iStartCol == m.iStartRow - m.iEndRow))
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
                if (board[iCheckRow][iCheckCol] != nullptr)
                {
                    return false;
                }
            }
            return true;
        }
        return false;
    }

public:
    P_Queen(char cColor) : Piece(cColor)
    {}

    ~P_Queen()
    {}
};

#endif //CONSOLE_CHESS_QUEEN_H
