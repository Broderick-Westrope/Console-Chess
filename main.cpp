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

int main()
{
    Player *white = new HumanPlayer('W', "Human");
    Player *black = new HumanPlayer('B', "Human");

    Chess thisGame(white, black);
    thisGame.Play();
    return 0;
}