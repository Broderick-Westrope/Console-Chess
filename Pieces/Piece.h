//
//  Author: Broderick Westrope
//  Date: 20/04/21
//
#ifndef CONSOLE_CHESS_PIECE_H
#define CONSOLE_CHESS_PIECE_H

class Piece
{
private:
    virtual bool AreSquaresLegal(Move m, Piece *qpaaBoard[8][8]) = 0;

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

    bool IsLegalMove(Move m, Piece *qpaaBoard[8][8])
    {
        Piece *qpDest = qpaaBoard[m.iEndRow][m.iEndCol];
        if ((qpDest == 0) || (mcColor != qpDest->GetColor()))
        {
            return AreSquaresLegal(m, qpaaBoard);
        }
        return false;
    }
};

#endif //CONSOLE_CHESS_PIECE_H
