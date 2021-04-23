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

        const int tileWidth = 6;
        const int tileHeight = 3;

        cout << endl; //Add our empty line above the board for error messages

        //region - Top Numbers
        //Loop through the variable tileHeight for each row of the margin/border. We add one so that the top can be closed
        //using an underscore without interfering with the spacing inside the margin
        for (int row = 0; row < tileHeight + 1; ++row)
        {
            if (row % tileHeight == 2)  //If we are on the third row (second within the margin) --this is the row where our numbers are placed
            {
                if (row != 0) //If its not the first row (the row of only underscores)
                    cout << "   |     "; //Add the left edge
                for (int col = 0; col < 8 * tileWidth; ++col) //For each tile (+1) * the number of digits in a tile. Basically loop through each digit in our board's width
                {
                    int tileCol = col / tileWidth;
                    if (col % tileWidth == 1) //If we are on column of index 1 (relative to the tile width)
                    {
                        cout << "0"; //Print a 0. This gives us the aligned look because all of our numbers (1-8) are 1 digit and hence of odd length
                    }
                    else if (col % tileWidth == 2) //Else if we are on the column index of 2
                    {
                        cout << (tileCol + 1); //Print the index of this column (+1 for the user ease)
                    }
                    else if (col % tileWidth == 0 || col % tileWidth == 3) //Else if we are on the column of index 0 or 3 (either before or after our 2 digit number) then add those fancy ~ things
                    {
                        cout << '~';
                    }
                    else //Else we just want blank space to fill it in
                    {
                        cout << ' ';
                    }
                }
                for (int i = 0; i < tileWidth / 2; i++) //Use a for loop to determine how many spaces are needed. This allows us to customise the board easily and keep things relative
                    cout << ' '; //Add spaces to align the right edge
            }
            else //Else if we are on any other row
            {
                if (row == 0) //If we are on row 0 add blank space only
                    cout << "    ";
                else //If not, add blank space and align the left edge
                    cout << "   |";

                for (int col = 1; col < 9 * tileWidth; ++col) //For all of the digits in our relative board width
                {
                    //If its row 0 then we only want to add underscored, OR if the row is the last row and the column is beyond the left margin (the tile height)
                    if (row == 0 || (row == tileHeight && col > tileHeight))
                        cout << '_';
                    else //If not, add spaces to fill in
                        cout << ' ';
                }

                for (int i = 0; i < tileWidth / 2; i++)
                {
                    if (row == 0) //If the row is index 0 then finish it with some underscores
                        cout << '_';
                    else //If not, finish it with some blank space
                        cout << ' ';
                }
            }

            if (row != 0) //If its any row other than 0, add the right edge
                cout << "|";
            cout << endl;
        }
        //endregion

        //region - Middle
        //For each digit in our relative board width (+1)
        for (int row = 0; row < 8 * tileHeight; ++row)
        {
            int tileRow = row / tileHeight;
            //region - Left Margin
            if (row % tileHeight == 1)  //If the row is index 1
            {
                cout << "   |~" << (char) ('1' + 7 - tileRow) << "~|"; //Print the number inside the margin
            }
            else //Else, print an empty margin row
            {
                cout << "   |   |";
            }
            //endregion

            //region - Print Board Tiles
            for (int col = 0; col < 8 * tileWidth; ++col) //For all of the digits in the board width
            {
                int tileCol = col / tileWidth;

                //If this tile isn't taken, it's row 1 within the tile (the middle row), and the column is between 1 and 4 (we only customize the middle 4, and this is only done when there is a piece)
                if (grid[7 - tileRow][tileCol] != nullptr && (row % tileHeight) == 1 && ((col % tileWidth) >= 1 && (col % tileWidth) <= 4))
                {
                    if ((col % tileWidth) == 2) //If it's column 2
                    {
                        cout << grid[7 - tileRow][tileCol]->GetColor(); //Print the color value
                    }
                    else if ((col % tileWidth) == 3) //If it's column 3
                    {
                        cout << grid[7 - tileRow][tileCol]->GetPiece(); //Print the piece value
                    }
                    else //Else we want to print the left or right outline of the piece (this is just for aesthetics)
                    {
                        cout << '|';
                    }
                }
                else //If not
                {
                    if ((tileRow + tileCol) % 2 == 1) //If it's a while tile (Even)
                    {
                        cout << '@'; //Use a symbol to make it white
                    }
                    else //If not, it's a black tile (odd)
                    {
                        if (row == (tileHeight * 8) - 1) //If its the final/bottom row of tiles
                            cout << '_'; //Use underscores to make it black but add and edge effect
                        else
                            cout << ' '; //Use spaces to make it black
                    }
                }
            }
            //endregion

            //region - Right Margin
            if (row % 3 == 1) //If its the middle row (aligns with the middle of the tile)
            {
                cout << "|~" << (char) ('1' + 7 - tileRow) << "~|"; //Print the value with the margin edges
            }
            else //If not, just print margin edges
            {
                cout << "|   |";
            }
            //endregion

            cout << endl;
        }
        //endregion

        //region - Bottom Numbers
        //Loop through the variable tileHeight for each row of the margin/border.
        for (int row = 0; row < tileHeight; ++row)
        {
            if (row % tileHeight == 1) //If its row of index 1
            {
                cout << "   |     "; //Add the left edge
                for (int col = 0; col < 8 * tileWidth; ++col) //For each digit of the board's width
                {
                    int tileCol = col / tileWidth;
                    if (col % tileWidth == 1)  //If we are on column of index 1 (relative to the tile width)
                    {
                        cout << "0"; //Print a 0. This gives us the aligned look because all of our numbers (1-8) are 1 digit and hence of odd length
                    }
                    else if ((col % tileWidth) == 2) //Else if we are on the column index of 2
                    {
                        cout << (tileCol + 1); //Print the index of this column (+1 for the user ease)
                    }
                    else if (col % tileWidth == 0 || col % tileWidth == 3) //Else if we are on the column of index 0 or 3 (either before or after our 2 digit number) then add those fancy ~ things
                    {
                        cout << '~';
                    }
                    else //Else we just want blank space to fill it in
                    {
                        cout << ' ';
                    }
                }
                for (int i = 0; i < tileWidth / 2; i++) //Use a for loop to determine how many spaces are needed. This allows us to customise the board easliy and keep things relative
                    cout << " "; //Add spaces to align the right edge
            }
            else //If it's not the row of index 1
            {
                cout << "   |"; //Print the right edge
                for (int col = 1; col < 9 * tileWidth; ++col) //For each digit in the board's width
                {
                    if (row % tileHeight == tileHeight - 1) //If we are on the last row (last iteration of the row for loop)
                        cout << '_'; //Print an underscore for the bottom edge of the board
                    else //If not, print blank space
                        cout << ' ';
                }

                for (int i = 0; i < tileWidth / 2; i++) //Use a for loop to determine how many spaces or underscores are needed. This allows us to customise the board easliy and keep things relative
                    if (row % tileHeight == tileHeight - 1) //If we are on the last row (last iteration of the row for loop) print an underscore
                        cout << '_';
                    else //If not, print blank space
                        cout << ' ';
            }

            cout << "|"; //Add the edge at the end of the row
            cout << endl;
        }
        //endregion

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
