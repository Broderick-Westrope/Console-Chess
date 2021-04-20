//
// Created by ascle on 20/04/2021.
//

#ifndef CONSOLE_CHESS_HUMANPLAYER_H
#define CONSOLE_CHESS_HUMANPLAYER_H

class HumanPlayer : public Player
{
public:
    HumanPlayer(char t, string symbol = "Undefined (ERROR)") : Player(t, symbol)
    {}

    virtual bool GetMove(Board &board);
};

bool HumanPlayer::GetMove(Board &board)
{
    using namespace std;
    do
    {
        // Get input and convert to coordinates
        cout << "Move Piece at Position: " << endl;
        int iStartMove;
        cin >> iStartMove;
        int iStartRow = (iStartMove / 10) - 1;
        int iStartCol = (iStartMove % 10) - 1;

        cout << "To Position: ";
        int iEndMove;
        cin >> iEndMove;
        int iEndRow = (iEndMove / 10) - 1;
        int iEndCol = (iEndMove % 10) - 1;

        Move m(iStartRow, iStartCol, iEndRow, iEndCol);

        // Check that the indices are in range and that the source and destination are different
        if (Board::IsInBounds(m) && !(iStartRow == iEndRow && iStartCol == iEndCol))
        {
            // Additional checks in here
            Piece *qpCurrPiece = board.mqpaaBoard[iStartRow][iStartCol];
            // Check that the piece is the correct color
            if ((qpCurrPiece != nullptr) && (qpCurrPiece->GetColor() == type))
            {
                // Check that the destination is a valid destination
                if (qpCurrPiece->IsLegalMove(m, board.mqpaaBoard))
                {
                    system("CLS");
                    board.DoTheMove(m, type);
                    return true;
                }
            }
        }
        system("CLS");
        cout << "Invalid Input!" << endl;
        board.Print();
    } while (true);

    return false;
}

#endif //CONSOLE_CHESS_HUMANPLAYER_H
