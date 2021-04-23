//
// Created by ascle on 20/04/2021.
//

#ifndef CONSOLE_CHESS_MONTECARLOPLAYER_H
#define CONSOLE_CHESS_MONTECARLOPLAYER_H

#include "vector"
#include "queue"
#include "Player.h"

class MCPlayer : public Player
{
public:
    MCPlayer(char t, string symbol = "Undefined (ERROR)") : Player(t, symbol)
    {}

    virtual bool GetMove(Board &board);

    vector<Move> candidates;
    char opponent;

    Move BestMove(Board *board);

    double Simulation(Board board);

    double Expansion(char playerType, Board board, double depth);

    Move RandomMove(Board board, char player);
};

bool MCPlayer::GetMove(Board &board)
{
    using namespace std;

    for (int pR = 0; pR < 8; pR++) //All rows of Pieces
    {
        for (int pC = 0; pC < 8; pC++) //All columns of Pieces
        {
            if (board.grid[pR][pC] != nullptr && board.grid[pR][pC]->GetColor() == player)
            {
                for (int mR = 0; mR < 8; mR++)
                {
                    for (int mC = 0; mC < 8; mC++)
                    {
                        if ((pR == mR && pC == mC) || (board.grid[mR][mC] != nullptr && board.grid[mR][mC]->GetColor() == player))
                            continue;

                        Move m(pR, pC, mR, mC);
                        if (board.grid[pR][pC]->IsLegalMove(m, board.grid))
                            candidates.push_back(m);
                    }
                }
            }
        }
    }

    if (candidates.empty())
    {
        cout << "ERROR: No candidate moves were found by Monte-Carlo Player!" << endl;
        return false;
    }

    opponent = (player == 'W') ? 'B' : 'W';
    Move best = BestMove(&board);
    board.DoTheMove(best, player);

    cout << "Invalid Input!" << endl;
    board.Print();

    return false;
}

Move MCPlayer::BestMove(Board *board)
{
    priority_queue <MCMove> moves;
    cout << "Values of Moves: " << endl;
    for (Move m : candidates)
    {
        //Print the move
        cout << "PR: " << m.iStartRow << " PC: " << m.iStartCol << " MR: " << m.iEndRow << " MC: " << m.iEndCol;

        Board tempBoard(*board);
        tempBoard.DoTest(m, player);

        cout << "MARK 1" << endl;
        if (board->HasWonGame(player))
        {
            return m;
        }
        else if (board->IsInCheck(player))
        {
            moves.push(MCMove(m, -500));
            continue;
        }
        else if (board->IsInCheck(opponent))
        {
            moves.push(MCMove(m, 500));           //todo          Change the Check value here!
            continue;
        }

        double value = Simulation(tempBoard);

        moves.push(MCMove(m, value));
        cout << " Value: " << value << endl;
    }

    if (!moves.empty())
    {
        cout << "Best value: " << moves.top().v << endl;
        return {moves.top().iStartRow, moves.top().iStartCol, moves.top().iEndRow, moves.top().iEndCol};
    }

    cout << "ERROR: No appropriate move was found by Monte Carlo" << endl;
    return {-1, -1, -1, -1};
}

double MCPlayer::Simulation(Board board)
{
    double winning = 0.0;
    int times = 2000;

    for (int i = 0; i < times; i++)
    {
        Board tempBoard(board);
        winning += Expansion(opponent, tempBoard, 0);
    }
    return (winning / (double) times);
}

double MCPlayer::Expansion(char playerType, Board board, double depth)
{
    Move random = RandomMove(board, playerType);
    if (!board.DoTest(random, playerType))
        printf("ERROR: Invalid input created by Monte-Carlo's Random Move function\n");

    if (board.HasWonGame(player))
    {
        return 1.0 - depth;
    }
    else if (board.HasWonGame(opponent))
    {
        return -1.0 + depth;
    }
    printf("MARK 3\n");

    playerType = (playerType == player) ? opponent : player;
    return Expansion(playerType, board, depth + 0.05);
}

Move MCPlayer::RandomMove(Board board, char player)
{
    vector<Move> moves;

    moves = board.GetPossibleMoves(player);

    if (moves.empty())
        cout << "ERROR: Random Move inside Monte Carlo Player couldn't get any candidate moves." << endl;

    int i = rand() % moves.size();
    return moves[i];
}


#endif //CONSOLE_CHESS_MONTECARLOPLAYER_H
