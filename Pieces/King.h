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
//        else if (CanCastleThisKing(qpaaBoard))
//        {
//            printf("CAN CASTLE!\n");
//            if (((iRowDelta >= -2) && (iRowDelta <= 2)) && iColDelta == 0)
//            {
//                return true;
//            }
//        }
        return false;
    }

//    bool CanCastleThisKing(Piece *qpaaBoard[8][8])
//    {
//        if (canCastle)
//        {
//            printf("L1\n");
//            if (GetColor() == 'W')
//            {
//                printf("L2 - W\n");
//                std::cout << qpaaBoard[0][0]->GetPiece() << " " << dynamic_cast<P_Rook *>(qpaaBoard[0][0])->canCastle << std::endl;
//                if ((qpaaBoard[0][0]->GetPiece() == 'R' && dynamic_cast<P_Rook *>(qpaaBoard[0][0])->canCastle) &&
//                    (qpaaBoard[0][7]->GetPiece() == 'R' && dynamic_cast<P_Rook *>(qpaaBoard[0][7])->canCastle))
//                {
//                    dynamic_cast<P_Rook *>(qpaaBoard[0][0])->canCastle = false;
//                    dynamic_cast<P_Rook *>(qpaaBoard[0][7])->canCastle = false;
//                    return true;
//                }
//            }
//            else if (GetColor() == 'B')
//            {
//                printf("L2 - B\n");
//                if ((qpaaBoard[7][0]->GetPiece() == 'R' && dynamic_cast<P_Rook *>(qpaaBoard[7][0])->canCastle) &&
//                    (qpaaBoard[7][7]->GetPiece() == 'R' && dynamic_cast<P_Rook *>(qpaaBoard[0][7])->canCastle))
//                {
//                    dynamic_cast<P_Rook *>(qpaaBoard[7][0])->canCastle = false;
//                    dynamic_cast<P_Rook *>(qpaaBoard[7][7])->canCastle = false;
//                    return true;
//                }
//            }
//            else
//                std::cout << "FATAL ERROR: Can't Castle the king because the king's color is not recognised." << std::endl;
//        }
//        printf("CANNOT CASTLE!\n");
//        return false;
//    }

public:
    P_King(char cColor) : Piece(cColor)
    {}

    ~P_King()
    {}

    //bool canCastle = true;
};


#endif //CONSOLE_CHESS_KING_H
