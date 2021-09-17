#include "Input.h"

bool Input::s_moveUp = false;
bool Input::s_moveDown = false;
bool Input::s_increaseLen = false;
bool Input::s_decreaseLen = false;
bool Input::s_rotateRight = false;
bool Input::s_rotateLeft = false;
bool Input::s_space = false;
float Input::s_speed = 500.0f;
float Input::s_sensitivity = 100.0f;
constexpr float JUMP_FORCE = 100.0f;

void Input::buttonsClick(sf::RenderWindow& p_window)
{
    sf::Event event;
    while (p_window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            p_window.close();
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
            p_window.close();
        if (event.type == sf::Event::KeyPressed)
        {
            if (event.key.code == sf::Keyboard::W || event.key.code == sf::Keyboard::Up)
            {
                s_moveUp = true;
            }
            if (event.key.code == sf::Keyboard::S || event.key.code == sf::Keyboard::Down)
            {
                s_moveDown = true;
            }
            if (event.key.code == sf::Keyboard::D || event.key.code == sf::Keyboard::Right)
            {
                s_increaseLen = true;
            }
            if (event.key.code == sf::Keyboard::A || event.key.code == sf::Keyboard::Left)
            {
                s_decreaseLen = true;
            }
            if (event.key.code == sf::Keyboard::Q)
            {
                s_rotateLeft = true;
            }
            if (event.key.code == sf::Keyboard::E)
            {
                s_rotateRight = true;
            }
            if (event.key.code == sf::Keyboard::Space)
            {
                s_space = true;
            }
        }
        else if(event.type == sf::Event::KeyReleased)
        {
            if (event.key.code == sf::Keyboard::W || event.key.code == sf::Keyboard::Up)
            {
                s_moveUp = false;
            }
            if (event.key.code == sf::Keyboard::S || event.key.code == sf::Keyboard::Down)
            {
                s_moveDown = false;
            }
            if (event.key.code == sf::Keyboard::D || event.key.code == sf::Keyboard::Right)
            {
                s_increaseLen = false;
            }
            if (event.key.code == sf::Keyboard::A || event.key.code == sf::Keyboard::Left)
            {
                s_decreaseLen = false;
            }
            if (event.key.code == sf::Keyboard::Q)
            {
                s_rotateLeft = false;
            }
            if (event.key.code == sf::Keyboard::E)
            {
                s_rotateRight = false;
            }
            if (event.key.code == sf::Keyboard::Space)
            {
                s_space = false;
            }
        }
    }
}
