#pragma once
#include <iostream>
#include "GameWindow.h"
#include "Input.h"
#include "Arm.h"
#include "ForwardKinematicSystem.h"
#include <cstdlib>
#include <ctime>

#define PI 3.141592653589793238

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

        ForwardKinematicSystem fksystem(Vector2D(l_windowWidth / 2, l_windowHeight / 2));

        fksystem.addArm(100.0f);
        fksystem.addArm(100.0f);
        fksystem.addArm(100.0f);

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

            fksystem.rotateArm(0, std::sin(toRadians(angle)) * 1.3f);
            fksystem.rotateArm(1, std::sin(toRadians(angle * 1.2f)) * -0.9f);
            fksystem.rotateArm(2, std::sin(toRadians(angle * 0.73f)) * 1.12f);
            fksystem.update();

            auto& arms = fksystem.getArms();

            for(const auto& arm : arms)
            {
                drawLine(m_window, *arm);
            }

            m_window.display();

        }
    }

    static void drawLine(sf::RenderWindow& window, const Arm& arm)
    {
        sf::Vertex line[2] =
        {
            sf::Vertex(sf::Vector2f(arm.getPos().getX(), arm.getPos().getY())),
            sf::Vertex(sf::Vector2f(arm.getEnd().getX(), arm.getEnd().getY())),
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

