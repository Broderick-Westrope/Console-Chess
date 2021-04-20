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

            if (IsGameOver(turn))
                won = turn;

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

    bool IsGameOver(char player)
    {
        // Check that the current player can move
        // If not, we have a stalemate or checkmate
        bool bCanMove(false);
        bCanMove = board.CanMove(player);
        if (!bCanMove)
        {
            if (board.IsInCheck(player))
            {
                AlternateTurn();
                std::cout << "Checkmate, " << player << " Wins!" << std::endl;
            }
            else
            {
                std::cout << "Stalemate!" << std::endl;
            }
        }
        return !bCanMove;
    }
};

#endif //CONSOLE_CHESS_CHESS_H
