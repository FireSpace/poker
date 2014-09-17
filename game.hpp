#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <stack>
#include <functional>

#include "player.hpp"

class Game
{
    size_t number;
    std::vector<Player> players;

    size_t curDealer;
    size_t smallBlind;
    size_t curPlayer;
    size_t curBet;
    size_t curStep;

    std::stack<size_t> bank;

    size_t progress;

    void bet(size_t playerNum, size_t sum)
    {
        if (sum == 0 && curBet - players[playerNum].getBet())
        {
            players[playerNum].setFold();
            return;
        }

        size_t rSum = players[playerNum].move(sum);
        bank.top() += rSum;
        if (rSum > curBet) curBet = rSum; //raise

        if (rSum < sum) bank.push(0); // split bank if player move all in
    }

    size_t nextPlayer(size_t i)
    {
        i++;
        while (!players[i].isInGame() || players[i].isFold()) i++;
        return (i);
    }

    void nextMove()
    {
        progress++;
        if (progress%20 == 0) //increase blinds
            smallBlind *= 2;

        curStep = 0;

        curDealer = nextPlayer(curDealer);

        bank.push(0);

        curPlayer = nextPlayer(curDealer);
        bet(curPlayer, smallBlind);
        curPlayer = nextPlayer(curPlayer);
        bet(curPlayer, smallBlind*2);
        curPlayer = nextPlayer(curPlayer);
    }

    bool whileCond(Player p) //becouse fuck you, c++11 !
    {
        return (p.isInGame() && !p.isFold() && p.getBet() == curBet);
    }

public:
    Game(size_t number)
        : number(number)
        , players(number)
        , smallBlind(50)
        , curPlayer(0)
        , curBet(0)
        , curStep(0)
    {
        size_t cash;
        std::cout << "Please, write players cash:" << std::endl;
        std::cin >> cash;

        std::string tname;
        for (size_t i = 0; i < number; ++i)
        {
            std::cout << "Please, write " << i << "-s player name:" << std::endl;
            std::cin >> tname;
            players[i] = Player(tname, cash);
        }

        curDealer = 0;
    }

    void run()
    {
        while (std::count_if(players.begin(), players.end(), [](Player p){ return (p.isInGame()); }) > 1)
        {
            nextMove();

            while (curStep < 3)
            {
                while (curPlayer != curDealer &&
                    !std::all_of(players.begin(), players.end(), std::bind(&Game::whileCond, this, std::placeholders::_1)))
                {
                    std::cout << players[curPlayer].getName() << std::endl
                              << "player's bet: " << players[curPlayer].getBet() << std::endl
                              << "current bet: " << curBet << std::endl
                              << "check cost: " << curBet - players[curPlayer].getBet() << std::endl
                              << "please, enter your rise: (0 - check or fold)" << std::endl;

                    size_t tbet; std::cin >> tbet;
                    bet(curPlayer, tbet);

                    curPlayer = nextPlayer(curPlayer);
                }

                curStep++;
            }

            for (size_t i = 0; i < number; ++i) std::cout << i << ": " << players[i].getName() << std::endl;

            while (!bank.empty())
            {
                std::cout << "current bank: " << bank.top() << std::endl
                          << "enter winner's number" << std::endl;

                size_t tnumb; std::cin >> tnumb;
                players[tnumb].win(bank.top());
                bank.pop();
            }
        }

        std::cout << "Game over. Winner - " << (std::find_if(players.begin(), players.end(), [](Player p){ return (p.isInGame()); }))->getName() << "!" << std::endl;
    }
};
