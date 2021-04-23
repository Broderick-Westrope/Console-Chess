//
// Created by ascle on 20/04/2021.
//

#ifndef CONSOLE_CHESS_PLAYER_H
#define CONSOLE_CHESS_PLAYER_H
using namespace std;

class Player
{
protected:
    char player;
    string name;
    string symbol;
public:
    Player(char t, string n) : player(t), name(n)
    {
        switch (player)
        {
            case 'W':
                name = "White";
                break;
            case 'B':
                name = "Black";
                break;
        }
    }

    string GetName()
    {
        return name;
    }

    string GetSymbol()
    {
        return symbol;
    }

    int GetType()
    {
        return player;
    }

    virtual bool GetMove(Board &bBoard) = 0;

    virtual ~Player()
    {
    }
};

#endif //CONSOLE_CHESS_PLAYER_H
