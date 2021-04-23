//
//  Author: Broderick Westrope
//  Date: 20/04/21
//

#ifndef CONSOLE_CHESS_CHESS_H
#define CONSOLE_CHESS_CHESS_H

class Chess
{
private:
    Board board;
    char turn;
    Player *whiteP, *blackP;
public:
    Chess(Player *_w, Player *_b) : turn('W'), whiteP(_w), blackP(_b)
    {}

    ~Chess() = default;

    char Play()
    {
        using namespace std;

        char won = ' ';
        board.Print();

        do
        {
            cout << turn << "'s Move: " << endl;

            if (turn == 'W')
            {
                if (!whiteP->GetMove(board))
                    cout << "Invalid Move by White!" << endl;
            }
            else if (turn == 'B')
            {
                if (!blackP->GetMove(board))
                    cout << "Invalid Move by Black!" << endl;
            }
            else
                cout << "ERROR: Incorrect value in turn variable." << endl;

            board.Print();

            if (board.HasWonGame(turn))
            {
                printf("Winner\n");
                AlternateTurn();
                won = turn;
            }

            AlternateTurn();
        } while (won == ' ');

        if (won == 'W')
            cout << "White won the game!" << endl;
        else
            cout << "Black won the game!" << endl;

        return turn;
    }

    void AlternateTurn()
    {
        turn = (turn == 'W') ? 'B' : 'W';
    }
};

#endif //CONSOLE_CHESS_CHESS_H
