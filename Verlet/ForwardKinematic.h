#pragma once
#include <iostream>
#include "GameWindow.h"
#include "Input.h"
#include "Arm.h"
#include <cstdlib>
#include <ctime>

class ForwardKinematic
{
public:
    static void main()
    {
        sf::ContextSettings settings;
        settings.antialiasingLevel = 8;
        const unsigned int l_windowWidth = 1280;
        const unsigned int l_windowHeight = 720;
        std::string l_title = "Forward kinematic";
        sf::RenderWindow m_window(sf::VideoMode{ l_windowWidth, l_windowHeight }, l_title, sf::Style::Default, settings);
        float l_prevTime = 0.0f;
        float l_currentTime = 0.0f;
        sf::Clock clock;

        float friction = 0.9f;

        Arm arm(Vector2D(l_windowWidth / 2, l_windowHeight / 2), 100.0f, 0.0f);
        Arm arm2(arm.getEnd(), 100.0f, toRadians(45.0f), &arm);
        Arm arm3(arm2.getEnd(), 100.0f, toRadians(45.0f), &arm2);

        float angle = 90.0f;

        while (m_window.isOpen())
        {
            Input::buttonsClick(m_window);
            m_window.clear();
            sf::Time l_elapsed = clock.getElapsedTime();
            l_prevTime = l_currentTime;
            l_currentTime = l_elapsed.asSeconds();
            float l_deltaTime = l_currentTime - l_prevTime;

            angle += 80.0f * l_deltaTime;
            arm.setAngle(1.2f * std::sin(toRadians(angle)));
            arm2.setPosition(arm.getEnd());
            arm2.setAngle(0.92f * std::cos(toRadians(angle * 0.873f)));
            arm3.setPosition(arm2.getEnd());
            arm3.setAngle(1.34f * std::cos(toRadians(angle * 1.57f)));
            sf::Vertex line[2] =
            {
                sf::Vertex(sf::Vector2f(arm.getPos().getX(), arm.getPos().getY())),
                sf::Vertex(sf::Vector2f(arm.getEnd().getX(), arm.getEnd().getY())),
            };

            sf::Vertex line2[2] =
            {
                sf::Vertex(sf::Vector2f(arm2.getPos().getX(), arm2.getPos().getY())),
                sf::Vertex(sf::Vector2f(arm2.getEnd().getX(), arm2.getEnd().getY())),
            };

            sf::Vertex line3[2] =
            {
                sf::Vertex(sf::Vector2f(arm3.getPos().getX(), arm3.getPos().getY())),
                sf::Vertex(sf::Vector2f(arm3.getEnd().getX(), arm3.getEnd().getY())),
            };

            m_window.draw(line, 2, sf::Lines);
            m_window.draw(line2, 2, sf::Lines);
            m_window.draw(line3, 2, sf::Lines);
            m_window.display();

        }
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

