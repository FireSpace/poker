#pragma once

#include <string>

class Player
{
    size_t cash, bet;
    std::string name;

public:
    Player(std::string name, size_t cash)
        : cash(cash)
        , bet(0)
        , name(name) {   }

    size_t getCash() { return (cash); }
    size_t getBet() { return (bet); }

    size_t move(size_t newbet)
    {
        if (newbet > cash) //all in
        {
            bet += cash;
            cash = 0;
            return (cash);
        } else
        {
            bet += newbet;
            cash -= newbet;
            return newbet;
        }
    }

    void betReset() { bet = 0; }
    void win(size_t gain) { cash += gain; }
};
