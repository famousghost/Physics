#pragma once
#include <SFML\Graphics.hpp>
#include <SFML\Window.hpp>

class Input
{
public:

    static void buttonsClick(sf::RenderWindow& p_window);

    static bool s_moveUp;
    static bool s_moveDown;
    static bool s_increaseLen;
    static bool s_decreaseLen;
    static bool s_rotateRight;
    static bool s_space;
    static bool s_rotateLeft;
    static float s_speed;
    static float s_sensitivity;
    
};

