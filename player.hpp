#pragma once

#include <string>

class Player
{
    size_t cash, bet;
    std::string name;
    bool inGame;

public:
    Player(std::string name, size_t cash)
        : cash(cash)
        , bet(0)
        , name(name)
        , inGame(true) {   }

    size_t getCash() { return (cash); }
    size_t getBet() { return (bet); }
    std::string getName() { return (name); }

    bool isInGame() { return (inGame); }

    size_t move(size_t newbet)
    {
        if (newbet > cash) //all in
        {
            bet += cash;
            cash = 0;
            inGame = false;
            return (cash);
        } else
        {
            bet += newbet;
            cash -= newbet;
            return newbet;
        }
    }

    void betReset() { bet = 0; }
    void win(size_t gain) { cash += gain; inGame = true;}
};
