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

float Input::KeyFWAxis(MezKeyCode forward_key, MezKeyCode backward_key)
{
    bool fw = KeyPressed(forward_key);
    bool bw = KeyPressed(backward_key);
    if (fw == bw) return 0.0f;
    return fw ? 1.0f : -1.0f;
}
