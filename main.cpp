#include <iostream>

#include "game.hpp"

int main()
{
    std::cout << "Hello! Please, enter the number of gamers: " << std::endl;
    size_t numb; std::cin >> numb;

    Game game(numb);
    game.run();
}
