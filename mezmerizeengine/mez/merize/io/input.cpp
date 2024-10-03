#include "input.h"
#include <SFML/Window/Keyboard.hpp>

bool Input::KeyPressed(MezKeyCode key)
{
    return sf::Keyboard::isKeyPressed((sf::Keyboard::Key)key);
}

bool Input::KeyHeld(MezKeyCode key)
{
    //not yet
    return sf::Keyboard::isKeyPressed((sf::Keyboard::Key)key);
}
