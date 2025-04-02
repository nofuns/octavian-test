#include <SFML/Graphics.hpp>
#include <iostream>

#include "IEntity.hpp"
#include "SlotMachineState.hpp"

#include "Game.hpp"

int main()
{
    std::unique_ptr<Game> game = std::make_unique<Game>();
   
    game->loop();

    return 0;
}