//
// Created by ascle on 20/04/2021.
//

#ifndef CONSOLE_CHESS_RANDOMPLAYER_H
#define CONSOLE_CHESS_RANDOMPLAYER_H

#include "vector"
#include "Player.h"

class RandomPlayer : public Player
{
public:
    RandomPlayer(char t, string symbol = "Undefined (ERROR)") : Player(t, symbol)
    {}

    virtual bool GetMove(Board &board);
};

bool RandomPlayer::GetMove(Board &board)
{
    using namespace std;

    vector<Move> moves;
    for (int pR = 0; pR < 8; pR++) //All rows of Pieces
    {
        printf("L1\n");
        for (int pC = 0; pC < 8; pC++) //All cols of Pieces
        {
            printf("L2\n");
            if (board.grid[pR][pC] != nullptr)
            {
                printf("L3\n");
                for (int mR = 0; mR < 8; mR++)
                {
                    printf("L4\n");
                    for (int mC = 0; mC < 8; mC++)
                    {
                        if ((pR == mR && pC == mC) || (board.grid[mR][mC]->GetColor() == type))// || (board.grid[pR][pC]->GetPiece() != 'P'))
                            continue;

                        printf("L5\n");
                        Move m(pR, pC, mR, mC);
                        if (board.grid[pR][pC]->IsLegalMove(m, board.grid))
                            moves.push_back(m);
                    }
                }
            }
        }
    }

    if (moves.empty())
        cout << "ERROR: No candidate moves were found by Random Player!" << endl;

    do
    {
        int randomIndex = rand() % (moves.size() - 1);
        cout << "Picked random index " << randomIndex << endl;
        Move randMove = moves[randomIndex];
        if (board.DoTheMove(randMove, type))
            return true;

        system("CLS");
        cout << "Invalid Input!" << endl;
        board.Print();
    } while (true);

    return false;
}

#endif //CONSOLE_CHESS_RANDOMPLAYER_H
