#pragma once
#include <iostream>
#include "GameWindow.h"
#include "Input.h"
#include "InverseKinematicSystem.h"
#include <cstdlib>
#include <ctime>
#define PI 3.141592653589793238
#define LENGTH 100

class InverseKinematic
{
public:
    static void main()
    {
        sf::ContextSettings settings;
        settings.antialiasingLevel = 8;
        const unsigned int l_windowWidth = 1280;
        const unsigned int l_windowHeight = 720;
        std::string l_title = "Inverse kinematic";
        sf::RenderWindow m_window(sf::VideoMode{ l_windowWidth, l_windowHeight }, l_title, sf::Style::Default, settings);
        float l_prevTime = 0.0f;
        float l_currentTime = 0.0f;
        sf::Clock clock;

        float friction = 0.9f;

        float angle = 90.0f;

        InverseKinematicSystem ivksystem(Vector2D(l_windowWidth / 2.0f, l_windowHeight / 2.0f));

        for(int i = 0; i < LENGTH; ++i)
        {
            ivksystem.addArm(1000.0f / LENGTH);
        }

        while (m_window.isOpen())
        {
            Input::buttonsClick(m_window);
            m_window.clear();
            sf::Time l_elapsed = clock.getElapsedTime();
            l_prevTime = l_currentTime;
            l_currentTime = l_elapsed.asSeconds();
            float l_deltaTime = l_currentTime - l_prevTime;
            auto mousePos = sf::Mouse::getPosition(m_window);
            ivksystem.drag(Vector2D(mousePos.x, mousePos.y));
            for(const auto& arm : ivksystem.getArms())
            {
                drawLine(m_window, *arm);
            }

            angle += 80.0f * l_deltaTime;

            m_window.display();
        }
    }

    static void drawLine(sf::RenderWindow& window, const Arm& arm)
    {
        sf::Vertex line[2] =
        {
            sf::Vertex(sf::Vector2f(arm.getPos().getX(), arm.getPos().getY())),
            sf::Vertex(sf::Vector2f(arm.getEndIK().getX(), arm.getEndIK().getY())),
        };
        window.draw(line, 2, sf::Lines);
    }

    static float toDegrees(float radians)
    {
        return radians * 180.0f / PI;
    }

    static float toRadians(float angle)
    {
        return angle * PI / 180.0f;
    }
};

