//
// Created by ascle on 20/04/2021.
//

#ifndef CONSOLE_CHESS_MOVE_H
#define CONSOLE_CHESS_MOVE_H

struct MCMove;

struct Move
{
public:
    int iStartRow;
    int iStartCol;
    int iEndRow;
    int iEndCol;

    Move(int _startR, int _startC, int _endR, int _endC) : iStartRow(_startR), iStartCol(_startC), iEndRow(_endR), iEndCol(_endC)
    {}
};

struct MCMove
{
    int iStartRow;
    int iStartCol;
    int iEndRow;
    int iEndCol;
    double v;

    MCMove(Move _m, double _v) : iStartRow(_m.iStartRow), iStartCol(_m.iStartCol), iEndRow(_m.iEndRow), iEndCol(_m.iEndCol), v(_v)
    {}

    bool operator<(const MCMove &m) const
    {
        return v < m.v;
    };
};

#endif //CONSOLE_CHESS_MOVE_H
