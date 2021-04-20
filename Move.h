//
// Created by ascle on 20/04/2021.
//

#ifndef CONSOLE_CHESS_MOVE_H
#define CONSOLE_CHESS_MOVE_H

class Move
{
public:
    int iStartRow;
    int iStartCol;
    int iEndRow;
    int iEndCol;

    Move(int _startR, int _startC, int _endR, int _endC) : iStartRow(_startR), iStartCol(_startC), iEndRow(_endR), iEndCol(_endC)
    {}
};

#endif //CONSOLE_CHESS_MOVE_H
