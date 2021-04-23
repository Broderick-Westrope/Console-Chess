//
// Created by ascle on 20/04/2021.
//

#ifndef CONSOLE_CHESS_BOARD_H
#define CONSOLE_CHESS_BOARD_H

class Board
{
public:
    Board()
    {
        for (int iRow = 0; iRow < 8; ++iRow)
        {
            for (int iCol = 0; iCol < 8; ++iCol)
            {
                grid[iRow][iCol] = nullptr;
            }
        }
        // Allocate and place black pieces
        for (int iCol = 0; iCol < 8; ++iCol)
        {
            grid[6][iCol] = new P_Pawn('B');
        }
        grid[7][0] = new P_Rook('B');
        grid[7][1] = new P_Knight('B');
        grid[7][2] = new P_Bishop('B');
        grid[7][3] = new P_King('B');
        grid[7][4] = new P_Queen('B');
        grid[7][5] = new P_Bishop('B');
        grid[7][6] = new P_Knight('B');
        grid[7][7] = new P_Rook('B');
        // Allocate and place white pieces
        for (int iCol = 0; iCol < 8; ++iCol)
        {
            grid[1][iCol] = new P_Pawn('W');
        }
        grid[0][0] = new P_Rook('W');
        grid[0][1] = new P_Knight('W');
        grid[0][2] = new P_Bishop('W');
        grid[0][3] = new P_King('W');
        grid[0][4] = new P_Queen('W');
        grid[0][5] = new P_Bishop('W');
        grid[0][6] = new P_Knight('W');
        grid[0][7] = new P_Rook('W');
    }

    ~Board()
    {
        for (auto &iRow : grid)
        {
            for (auto &iCol : iRow)
            {
                delete iCol;
                iCol = nullptr;
            }
        }
    }

    Piece *grid[8][8];

    void Print()
    {
        using namespace std;
        cout << endl;
        const int tileWidth = 6;
        const int tileHeight = 3;
        //Top Numbers
        // Print the bottom border with numbers
        for (int row = 0; row < tileHeight + 1; ++row)
        {
            if (row % tileHeight == 2)
            {
                if (row != 0)
                    cout << "   |     ";
                for (int col = 0; col < 8 * tileWidth; ++col)
                {
                    int tileCol = col / tileWidth;
                    if (col % tileWidth == 1)
                    {
                        cout << "0";
                    }
                    else if ((col % tileWidth) == 2)
                    {
                        cout << (tileCol + 1);
                    }
                    else if (col % tileWidth == 0 || col % tileWidth == 3)
                    {
                        cout << '~';
                    }
                    else
                    {
                        cout << ' ';
                    }
                }
                cout << "   ";
            }
            else
            {
                if (row == 0)
                    cout << "    ";
                else
                    cout << "   |";
                for (int col = 1; col < 9 * tileWidth; ++col)
                {
                    if (row == 0)
                        cout << '_';
                    else
                        cout << ' ';
                }
                if (row == 0)
                    cout << "___";
                else
                    cout << "   ";
            }

            if (row != 0)
                cout << "|";
            cout << endl;
        }
        //Middle
        for (int row = 0; row < 8 * tileHeight; ++row)
        {
            int tileRow = row / tileHeight;
            // Print side border with numbering
            if (row % 3 == 1)
            {
                cout << "   |~" << (char) ('1' + 7 - tileRow) << "~|";
            }
            else
            {
                cout << "   |   |";
            }
            // Print the chess board
            for (int col = 0; col < 8 * tileWidth; ++col)
            {
                int tileCol = col / tileWidth;
                if (((row % tileHeight) == 1) && ((col % tileWidth) == 1 || (col % tileWidth) == 2 || (col % tileWidth) == 3 || (col % tileWidth) == 4) &&
                    grid[7 - tileRow][tileCol] != nullptr)
                {
                    if ((col % tileWidth) == 2)
                    {
                        cout << grid[7 - tileRow][tileCol]->GetColor();
                    }
                    else if ((col % tileWidth) == 3)
                    {
                        cout << grid[7 - tileRow][tileCol]->GetPiece();
                    }
                    else
                    {
                        cout << '|';
                    }
                }
                else
                {
                    if ((tileRow + tileCol) % 2 == 1)
                    {
                        cout << '@';
                    }
                    else
                    {
                        cout << ' ';
                    }
                }
            }
            //RHS Numbers
            if (row % 3 == 1)
            {
                cout << "|~" << (char) ('1' + 7 - tileRow) << "~|";
            }
            else
            {
                cout << "|   |";
            }

            cout << endl;
        }
        // Print the bottom border with numbers
        for (int row = 0; row < tileHeight; ++row)
        {
            if (row % tileHeight == 1)
            {
                cout << "   |     ";
                for (int col = 0; col < 8 * tileWidth; ++col)
                {
                    int tileCol = col / tileWidth;
                    if (col % tileWidth == 1)
                    {
                        cout << "0";
                    }
                    else if ((col % tileWidth) == 2)
                    {
                        cout << (tileCol + 1);
                    }
                    else if (col % tileWidth == 0 || col % tileWidth == 3)
                    {
                        cout << '~';
                    }
                    else
                    {
                        cout << ' ';
                    }
                }
                cout << "   ";
            }
            else
            {
                cout << "   |";
                for (int col = 1; col < 9 * tileWidth; ++col)
                {
                    if (row == tileHeight - 1)
                        cout << '_';
                    else
                        cout << ' ';
                }
                if (row == tileHeight - 1)
                    cout << "___";
                else
                    cout << "   ";
            }

            cout << "|";
            cout << endl;
        }
        cout << endl;
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
                if (grid[iRow][iCol] != nullptr)
                {
                    if (grid[iRow][iCol]->GetColor() == type)
                    {
                        if (grid[iRow][iCol]->GetPiece() == 'K')
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
                if (grid[iRow][iCol] != nullptr)
                {
                    if (grid[iRow][iCol]->GetColor() != type)
                    {
                        Move m(iRow, iCol, iKingRow, iKingCol);
                        if (grid[iRow][iCol]->IsLegalMove(m, grid))
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
                if (grid[iRow][iCol] != nullptr)
                {
                    // If it is a piece of the current player, see if it has a legal move
                    if (grid[iRow][iCol]->GetColor() == cColor)
                    {
                        for (int iMoveRow = 0; iMoveRow < 8; ++iMoveRow)
                        {
                            for (int iMoveCol = 0; iMoveCol < 8; ++iMoveCol)
                            {
                                Move m(iRow, iCol, iMoveRow, iMoveCol);
                                if (grid[iRow][iCol]->IsLegalMove(m, grid))
                                {
                                    // Make move and check whether king is in check
                                    Piece *qpTemp = grid[iMoveRow][iMoveCol];
                                    grid[iMoveRow][iMoveCol] = grid[iRow][iCol];
                                    grid[iRow][iCol] = nullptr;
                                    bool bCanMove = !IsInCheck(cColor);
                                    // Undo the move
                                    grid[iRow][iCol] = grid[iMoveRow][iMoveCol];
                                    grid[iMoveRow][iMoveCol] = qpTemp;
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

    bool DoTheMove(Move m, char type)
    {
        bool notCheck = false;
        // Make the move
        Piece *qpTemp = grid[m.iEndRow][m.iEndCol];
        grid[m.iEndRow][m.iEndCol] = grid[m.iStartRow][m.iStartCol];
        grid[m.iStartRow][m.iStartCol] = nullptr;
        // Make sure that the current player is not in check
        if (!IsInCheck(type))
        {
            delete qpTemp;
            notCheck = true;
        }
        else
        { // Undo the last move
            grid[m.iStartRow][m.iStartCol] = grid[m.iEndRow][m.iEndCol];
            grid[m.iEndRow][m.iEndCol] = qpTemp;
        }

        //Check for pawn promotion
        if (CheckPromotion(m))
            PawnPromotion(m, type);
        else if (EnPassant(m, type))
            std::cout << "You did an En Passant move. Well Done!" << std::endl;

//        UpdateCastlingBools(m);

        return notCheck;
    }

//    void UpdateCastlingBools(Move m)
//    {
//        if (grid[m.iEndRow][m.iEndCol]->GetPiece() == 'R')
//        {
//            std::cout << "Rook at " << m.iEndRow << m.iEndCol << " can no longer castle" << std::endl;
//            static_cast<P_Rook *>(grid[m.iEndRow][m.iEndCol])->canCastle = false;
//        }
//        else if (grid[m.iEndRow][m.iEndCol]->GetPiece() == 'K')
//        {
//            std::cout << "King at " << m.iEndRow << m.iEndCol << " can no longer castle" << std::endl;
//            static_cast<P_King *>(grid[m.iEndRow][m.iEndCol])->canCastle = false;
//        }
//    }

    bool EnPassant(Move m, char type)
    {
        if ((type == 'W' && m.iEndRow == m.iStartRow + 2))
        {
            if (m.iEndCol - 1 >= 0 && grid[m.iEndRow][m.iEndCol - 1] != nullptr && grid[m.iEndRow][m.iEndCol - 1]->GetColor() == 'B')
            {
                delete grid[m.iEndRow][m.iEndCol - 1];
                grid[m.iEndRow][m.iEndCol - 1] = nullptr;
                return true;
            }
            else if (m.iEndCol + 1 <= 7 && grid[m.iEndRow][m.iEndCol + 1] != nullptr && grid[m.iEndRow][m.iEndCol + 1]->GetColor() == 'B')
            {
                delete grid[m.iEndRow][m.iEndCol + 1];
                grid[m.iEndRow][m.iEndCol + 1] = nullptr;
                return true;
            }
        }
        else if (type == 'B' && m.iEndRow == m.iStartRow - 2)
        {
            if (m.iEndCol - 1 >= 0 && grid[m.iEndRow][m.iEndCol - 1] != nullptr && grid[m.iEndRow][m.iEndCol - 1]->GetColor() == 'W')
            {
                delete grid[m.iEndRow][m.iEndCol - 1];
                grid[m.iEndRow][m.iEndCol - 1] = nullptr;
                return true;
            }
            else if (m.iEndCol + 1 <= 7 && grid[m.iEndRow][m.iEndCol + 1] != nullptr && grid[m.iEndRow][m.iEndCol + 1]->GetColor() == 'W')
            {
                delete grid[m.iEndRow][m.iEndCol + 1];
                grid[m.iEndRow][m.iEndCol + 1] = nullptr;
                return true;
            }
        }
        return false;
    }

    bool CheckPromotion(Move m)
    {
        Piece *p = grid[m.iEndRow][m.iEndCol];
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

        delete grid[m.iEndRow][m.iEndCol];

        switch (piece)
        {
            case 'B':
                grid[m.iEndRow][m.iEndCol] = new P_Bishop(type);
                break;
            case 'N':
                grid[m.iEndRow][m.iEndCol] = new P_Knight(type);
                break;
            case 'R':
                grid[m.iEndRow][m.iEndCol] = new P_Rook(type);
                break;
            case 'Q':
                grid[m.iEndRow][m.iEndCol] = new P_Queen(type);
                break;
            default:
                cout << "Invalid input so I'll make it a Queen for you." << endl;
                grid[m.iEndRow][m.iEndCol] = new P_Queen(type);
        }
    }

};

#endif //CONSOLE_CHESS_BOARD_H
