//
//  Author: Broderick Westrope
//  Date: 20/04/21
//

#ifndef CONSOLE_CHESS_PAWN_H
#define CONSOLE_CHESS_PAWN_H

#include "Piece.h"

class P_Pawn : public Piece
{
private:
    virtual char GetPiece()
    {
        return 'P';
    }

    bool AreSquaresLegal(Move m, Board *board)
    {
        Piece *qpEnd = board[m.iEndRow][m.iEndCol];
        if (qpEnd == 0) //If Endination is unnocupied
        {
            if (m.iStartCol == m.iEndCol) //If src and dest are in the same column (ie we arent going across)
            {
                if (GetColor() == 'W') //if the peice is white
                {
                    if (m.iEndRow == m.iStartRow + 1) //check if we are going up 1
                    {
                        return true;
                    }
                    else if (m.iEndRow == m.iStartRow + 2) //check if we are going up 2 (double pawn move)
                    {
                        return true;
                    }
                }
                else //if the peice is black
                {
                    if (m.iEndRow == m.iStartRow - 1) //check if we are going down 1
                    {
                        return true;
                    }
                    else if (m.iEndRow == m.iStartRow - 2) //check if we are going up 2 (double pawn move)
                    {
                        return true;
                    }
                }
            }
        }
        else //if dest is taken
        {
            // End holds piece of opposite color
            if ((m.iStartCol == m.iEndCol + 1) || (m.iStartCol == m.iEndCol - 1))
            {
                if (GetColor() == 'W')
                {
                    if (m.iEndRow == m.iStartRow + 1)
                    {
                        return true;
                    }
                }
                else
                {
                    if (m.iEndRow == m.iStartRow - 1)
                    {
                        return true;
                    }
                }
            }
        }
        return false;
    }

public:
    P_Pawn(char cColor) : Piece(cColor)
    {}

    ~P_Pawn()
    {}
};

#endif //CONSOLE_CHESS_PAWN_H
