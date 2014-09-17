#pragma once

#include <string>

class Player
{
    size_t cash, bet;
    std::string name;
    bool inGame;
    bool fold;

public:
    Player(std::string name, size_t cash)
        : cash(cash)
        , bet(0)
        , name(name)
        , inGame(true)
        , fold(false) {   }

    Player()
        : cash(30000)
        , bet(0)
        , name("Clara")
        , inGame(true)
        , fold(false) {   }

    size_t getCash() { return (cash); }
    size_t getBet() { return (bet); }
    std::string getName() { return (name); }

    bool isInGame() { return (inGame); }
    bool isFold() { return (fold); }

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

    void setFold() { fold = true; }

    void reset() { bet = 0; fold = false; }
    void win(size_t gain) { cash += gain; inGame = true;}
};
