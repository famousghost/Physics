#pragma once
#include <iostream>
#include "GameWindow.h"
#include "Input.h"
#include <cstdlib>
#include <ctime>
#include "Utilities.h"
#include "Line.h"
#include "Circle.h"
#include "Bezier.h"

#define RAY_LENGTH 100000000.0

class MainBezier
{
public:
    static void main()
    {
        sf::ContextSettings settings;
        settings.antialiasingLevel = 8;
        const unsigned int l_windowWidth = 1280;
        const unsigned int l_windowHeight = 720;
        std::string l_title = "Main Bezier";
        sf::RenderWindow m_window(sf::VideoMode{ l_windowWidth, l_windowHeight }, l_title, sf::Style::Default, settings);
        float l_prevTime = 0.0f;
        float l_currentTime = 0.0f;
        sf::Clock clock;

        Circle points[]
        {
            Circle(Vector2D(100.0f, 100.0f), 5.0f),
            Circle(Vector2D(200.0f, 200.0f), 5.0f),
            Circle(Vector2D(300.0f, 300.0f), 5.0f),
            Circle(Vector2D(400.0f, 400.0f), 5.0f)
        };


        Bezier bezier;

        while (m_window.isOpen())
        {
            Input::buttonsClick(m_window);
            m_window.clear();
            sf::Time l_elapsed = clock.getElapsedTime();
            l_prevTime = l_currentTime;
            l_currentTime = l_elapsed.asSeconds();
            float l_deltaTime = l_currentTime - l_prevTime;

            for (int i = 0; i < 4; ++i)
            {
                auto mPos = sf::Mouse::getPosition(m_window);
                Vector2D mousePos(mPos.x, mPos.y);
                Utilities::drag(points[i], mousePos);
                sf::CircleShape circle;
                Vector2D pos = points[i].position;
                circle.setPosition(sf::Vector2f(pos.getX(), pos.getY()));
                circle.setRadius(points[i].radius);

                m_window.draw(circle);
            }

            auto pointsArray = bezier.calculatePoints(points[0].position, 
                                                      points[1].position, 
                                                      points[2].position,
                                                      points[3].position, 
                                                      50);
            
            for(int i = 0; i < pointsArray.size()-1; ++i)
            {
                sf::Vertex vert[2]
                {
                    sf::Vertex(sf::Vector2f(pointsArray[i].getX(), pointsArray[i].getY())),
                    sf::Vertex(sf::Vector2f(pointsArray[i+1].getX(), pointsArray[i+1].getY())),
                };

                m_window.draw(vert, 2, sf::Lines);
            }

            m_window.display();
        }
    }
};