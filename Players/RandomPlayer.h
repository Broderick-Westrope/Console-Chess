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
        for (int pC = 0; pC < 8; pC++) //All columns of Pieces
        {
            if (board.grid[pR][pC] != nullptr && board.grid[pR][pC]->GetColor() == type)
            {
                for (int mR = 0; mR < 8; mR++)
                {
                    for (int mC = 0; mC < 8; mC++)
                    {
                        if ((pR == mR && pC == mC) || (board.grid[mR][mC] != nullptr && board.grid[mR][mC]->GetColor() == type))
                            continue;

                        Move m(pR, pC, mR, mC);
                        if (board.grid[pR][pC]->IsLegalMove(m, board.grid))
                            moves.push_back(m);
                    }
                }
            }
        }
    }

    if (moves.empty())
    {
        cout << "ERROR: No candidate moves were found by Random Player!" << endl;
        return false;
    }
    
    int randomIndex = rand() % (moves.size() - 1);
    Move randMove = moves[randomIndex];
    if (board.DoTheMove(randMove, type))
        return true;

    cout << "Invalid Input!" << endl;
    board.Print();

    return false;
}

#endif //CONSOLE_CHESS_RANDOMPLAYER_H
