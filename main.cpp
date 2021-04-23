//
//  Author: Broderick Westrope
//  Date: 20/04/21
//

#include <iostream>
#include "Move.h"
#include "Pieces_I.h"
#include "Board.h"
#include "Players_I.h"
#include "Chess.h"
#include <ctime>

int main()
{
    srand(time(nullptr));

    Player *white = new HumanPlayer('W', "Human");
    Player *black = new RandomPlayer('B', "Random");

    Chess thisGame(white, black);
    thisGame.Play();
    return 0;
}