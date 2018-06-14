#include "../include/input_handlers.hpp"

Action::Action(int cmd) : cmdMask_(cmd)
{
   //
}

Action::Action(int cmd, sf::Vector2i delta) : cmdMask_(cmd), dir_(delta)
{
    //
}

Action handleKeys(int key)
{
    switch(key)
    {
        case sf::Keyboard::Down:
        case sf::Keyboard::Numpad2:
        {
            return Action(Cmd::MOVE, sf::Vector2i(0,1)); 
        }
        case sf::Keyboard::Left:
        case sf::Keyboard::Numpad4:
        {
            return Action(Cmd::MOVE, sf::Vector2i(-1,0));
        }
        case sf::Keyboard::Up:
        case sf::Keyboard::Numpad8:
        {
            return Action(Cmd::MOVE, sf::Vector2i(0,-1));
        }
        case sf::Keyboard::Right:
        case sf::Keyboard::Numpad6:
        {
            return Action(Cmd::MOVE, sf::Vector2i(1,0));
        }
        case sf::Keyboard::Q:
        case sf::Keyboard::Escape:
        {
            return Action(Cmd::QUIT);
        }
        default: { break; }
    }

    return Action(Cmd::NONE);
}