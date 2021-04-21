//
// Created by ascle on 20/04/2021.
//

#ifndef CONSOLE_CHESS_BOARD_H
#define CONSOLE_CHESS_BOARD_H

#include "Pieces_I.h"

class Board
{
public:
    Board()
    {
        for (int iRow = 0; iRow < 8; ++iRow)
        {
            for (int iCol = 0; iCol < 8; ++iCol)
            {
                mqpaaBoard[iRow][iCol] = nullptr;
            }
        }
        // Allocate and place black pieces
        for (int iCol = 0; iCol < 8; ++iCol)
        {
            mqpaaBoard[6][iCol] = new P_Pawn('B');
        }
        mqpaaBoard[7][0] = new P_Rook('B');
        mqpaaBoard[7][1] = new P_Knight('B');
        mqpaaBoard[7][2] = new P_Bishop('B');
        mqpaaBoard[7][3] = new P_King('B');
        mqpaaBoard[7][4] = new P_Queen('B');
        mqpaaBoard[7][5] = new P_Bishop('B');
        mqpaaBoard[7][6] = new P_Knight('B');
        mqpaaBoard[7][7] = new P_Rook('B');
        // Allocate and place white pieces
        for (int iCol = 0; iCol < 8; ++iCol)
        {
            mqpaaBoard[1][iCol] = new P_Pawn('W');
        }
        mqpaaBoard[0][0] = new P_Rook('W');
        mqpaaBoard[0][1] = new P_Knight('W');
        mqpaaBoard[0][2] = new P_Bishop('W');
        mqpaaBoard[0][3] = new P_King('W');
        mqpaaBoard[0][4] = new P_Queen('W');
        mqpaaBoard[0][5] = new P_Bishop('W');
        mqpaaBoard[0][6] = new P_Knight('W');
        mqpaaBoard[0][7] = new P_Rook('W');
    }

    ~Board()
    {
        for (auto &iRow : mqpaaBoard)
        {
            for (auto &iCol : iRow)
            {
                delete iCol;
                iCol = nullptr;
            }
        }
    }

    void Print()
    {
        using namespace std;
        cout << endl;
        const int kiSquareWidth = 6;
        const int kiSquareHeight = 3;
        for (int iRow = 0; iRow < 8 * kiSquareHeight; ++iRow)
        {
            int iSquareRow = iRow / kiSquareHeight;
            // Print side border with numbering
            if (iRow % 3 == 1)
            {
                cout << '-' << (char) ('1' + 7 - iSquareRow) << '-';
            }
            else
            {
                cout << "---";
            }
            // Print the chess board
            for (int iCol = 0; iCol < 8 * kiSquareWidth; ++iCol)
            {
                int iSquareCol = iCol / kiSquareWidth;
                if (((iRow % kiSquareHeight) == 1) && ((iCol % kiSquareWidth) == 1 || (iCol % kiSquareWidth) == 2 || (iCol % kiSquareWidth) == 3 || (iCol % kiSquareWidth) == 4) &&
                    mqpaaBoard[7 - iSquareRow][iSquareCol] != nullptr)
                {
                    if ((iCol % kiSquareWidth) == 2)
                    {
                        cout << mqpaaBoard[7 - iSquareRow][iSquareCol]->GetColor();
                    }
                    else if ((iCol % kiSquareWidth) == 3)
                    {
                        cout << mqpaaBoard[7 - iSquareRow][iSquareCol]->GetPiece();
                    }
                    else
                    {
                        cout << '|';
                    }
                }
                else
                {
                    if ((iSquareRow + iSquareCol) % 2 == 1)
                    {
                        cout << '*';
                    }
                    else
                    {
                        cout << ' ';
                    }
                }
            }
            cout << endl;
        }
        // Print the bottom border with numbers
        for (int iRow = 0; iRow < kiSquareHeight; ++iRow)
        {
            if (iRow % kiSquareHeight == 1)
            {
                cout << "-----";
                for (int iCol = 0; iCol < 8 * kiSquareWidth; ++iCol)
                {
                    int iSquareCol = iCol / kiSquareWidth;
                    if ((iCol % kiSquareWidth) == 1)
                    {
                        cout << (iSquareCol + 1);
                    }
                    else
                    {
                        cout << '-';
                    }
                }
                cout << endl;
            }
            else
            {
                for (int iCol = 1; iCol < 9 * kiSquareWidth; ++iCol)
                {
                    cout << '-';
                }
                cout << endl;
            }
        }
    }

    bool IsInCheck(char type)
    {
        // Find the king
        int iKingRow;
        int iKingCol;
        for (int iRow = 0; iRow < 8; ++iRow)
        {
            for (int iCol = 0; iCol < 8; ++iCol)
            {
                if (mqpaaBoard[iRow][iCol] != nullptr)
                {
                    if (mqpaaBoard[iRow][iCol]->GetColor() == type)
                    {
                        if (mqpaaBoard[iRow][iCol]->GetPiece() == 'K')
                        {
                            iKingRow = iRow;
                            iKingCol = iCol;
                        }
                    }
                }
            }
        }
        // Run through the opponent's pieces and see if any can take the king
        for (int iRow = 0; iRow < 8; ++iRow)
        {
            for (int iCol = 0; iCol < 8; ++iCol)
            {
                if (mqpaaBoard[iRow][iCol] != nullptr)
                {
                    if (mqpaaBoard[iRow][iCol]->GetColor() != type)
                    {
                        Move m(iRow, iCol, iKingRow, iKingCol);
                        if (mqpaaBoard[iRow][iCol]->IsLegalMove(m, Board()))
                        {
                            return true;
                        }
                    }
                }
            }
        }

        return false;
    }

    static bool IsInBounds(Move m)
    {
        if ((m.iStartRow >= 0 && m.iStartRow <= 7) & (m.iStartCol >= 0 && m.iStartCol <= 7) && (m.iEndRow >= 0 && m.iEndRow <= 7) && (m.iEndCol >= 0 && m.iEndCol <= 7))
            return true;

        return false;
    }

    bool CanMove(char cColor)
    {
        // Run through all pieces
        for (int iRow = 0; iRow < 8; ++iRow)
        {
            for (int iCol = 0; iCol < 8; ++iCol)
            {
                if (mqpaaBoard[iRow][iCol] != nullptr)
                {
                    // If it is a piece of the current player, see if it has a legal move
                    if (mqpaaBoard[iRow][iCol]->GetColor() == cColor)
                    {
                        for (int iMoveRow = 0; iMoveRow < 8; ++iMoveRow)
                        {
                            for (int iMoveCol = 0; iMoveCol < 8; ++iMoveCol)
                            {
                                Move m(iRow, iCol, iMoveRow, iMoveCol);
                                if (mqpaaBoard[iRow][iCol]->IsLegalMove(m, Board()))
                                {
                                    // Make move and check whether king is in check
                                    Piece *qpTemp = mqpaaBoard[iMoveRow][iMoveCol];
                                    mqpaaBoard[iMoveRow][iMoveCol] = mqpaaBoard[iRow][iCol];
                                    mqpaaBoard[iRow][iCol] = nullptr;
                                    bool bCanMove = !IsInCheck(cColor);
                                    // Undo the move
                                    mqpaaBoard[iRow][iCol] = mqpaaBoard[iMoveRow][iMoveCol];
                                    mqpaaBoard[iMoveRow][iMoveCol] = qpTemp;
                                    if (bCanMove)
                                    {
                                        return true;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        return false;
    }

    Piece *mqpaaBoard[8][8];

    bool DoTheMove(Move m, int type)
    {
        bool notCheck = false;
        // Make the move
        Piece *qpTemp = mqpaaBoard[m.iEndRow][m.iEndCol];
        mqpaaBoard[m.iEndRow][m.iEndCol] = mqpaaBoard[m.iStartRow][m.iStartCol];
        mqpaaBoard[m.iStartRow][m.iStartCol] = nullptr;
        // Make sure that the current player is not in check
        if (!IsInCheck(type))
        {
            delete qpTemp;
            notCheck = true;
        }
        else
        { // Undo the last move
            mqpaaBoard[m.iStartRow][m.iStartCol] = mqpaaBoard[m.iEndRow][m.iEndCol];
            mqpaaBoard[m.iEndRow][m.iEndCol] = qpTemp;
        }

        //Check for pawn promotion
        if (CheckPromotion(m))
            PawnPromotion(m, type);

        return notCheck;
    }

    bool CheckPromotion(Move m)
    {
        Piece *p = mqpaaBoard[m.iEndRow][m.iEndCol];
        if (p->GetColor() == 'W' && m.iEndRow == 7)
            return true;
        if (p->GetColor() == 'B' && m.iEndRow == 0)
            return true;

        return false;
    }

    void PawnPromotion(Move m, char type)
    {
        using namespace std;
        cout << "You can promote your pawn! What piece would you like?   [B]ishop, k[N]ight, [Q]een, or [R]ook" << endl;
        char piece;
        cin >> piece;

        delete mqpaaBoard[m.iEndRow][m.iEndCol];

        switch (piece)
        {
            case 'B':
                mqpaaBoard[m.iEndRow][m.iEndCol] = new P_Bishop(type);
                break;
            case 'N':
                mqpaaBoard[m.iEndRow][m.iEndCol] = new P_Knight(type);
                break;
            case 'R':
                mqpaaBoard[m.iEndRow][m.iEndCol] = new P_Rook(type);
                break;
            case 'Q':
                mqpaaBoard[m.iEndRow][m.iEndCol] = new P_Queen(type);
                break;
            default:
                cout << "Invalid input so I'll make it a Queen for you." << endl;
                mqpaaBoard[m.iEndRow][m.iEndCol] = new P_Queen(type);
        }
    }
};

#endif //CONSOLE_CHESS_BOARD_H
