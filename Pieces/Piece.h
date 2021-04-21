//
//  Author: Broderick Westrope
//  Date: 20/04/21
//

#ifndef CONSOLE_CHESS_PIECE_H
#define CONSOLE_CHESS_PIECE_H

#include "../Board.h"

class Piece
{
private:
    virtual bool AreSquaresLegal(Move m, Board *board) = 0;

    char mcColor;

public:
    Piece(char cColor) : mcColor(cColor)
    {}

    ~Piece()
    {}

    virtual char GetPiece() = 0;

    char GetColor()
    {
        return mcColor;
    }

    bool IsLegalMove(Move m, Board *board)
    {
        Piece *qpDest = board->mqpaaBoard[m.iEndRow][m.iEndCol];
        if ((qpDest == 0) || (mcColor != qpDest->GetColor()))
        {
            return AreSquaresLegal(m, board);
        }
        return false;
    }
};

#endif //CONSOLE_CHESS_PIECE_H
