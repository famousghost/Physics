#pragma once
#include <iostream>
#include "GameWindow.h"
#include "Input.h"
#include "ParticleVerlet.h"
#include "Stick.h"
#include <cstdlib>
#include <ctime>
#define POINTS_IN_LINE 5
#define STICK_SIZE 4
#define PI 3.141592653589793238

class MainVerlet
{
public:
    static void main()
    {
        const unsigned int l_windowWidth = 1280;
        const unsigned int l_windowHeight = 720;
        std::string l_title = "Physics Tutorial";
        sf::RenderWindow m_window(sf::VideoMode{ l_windowWidth, l_windowHeight }, l_title, sf::Style::Default);
        float l_prevTime = 0.0f;
        float l_currentTime = 0.0f;
        float bouncy = 0.9f;
        sf::Clock clock;
        auto w = l_windowWidth / 2.0f;
        std::vector<ParticleVerlet> points;
        float beginPosX = 200.0f;
        float beginPosY = 200.0f;
        for (int i = 0; i < POINTS_IN_LINE; ++i)
        {
            for (int j = 0; j < POINTS_IN_LINE; ++j)
            {
                bool unmoveable = false;
                if((i == 0 && j == 0) || (i == 0 && j == POINTS_IN_LINE -1))
                {
                    unmoveable = true;
                }
                points.emplace_back(beginPosX + 75.0f * j, 
                                    beginPosY + 75.0f * i,
                                    beginPosX + 75.0f * j,
                                    beginPosY + 75.0f * i,
                                    unmoveable);
            }
        }

        auto& p = points[0];
        p.position += Vector2D(-25.0f, 0.0f);
        p.prevPosition += Vector2D(-25.0f, 0.0f);
        auto& p1 = points[POINTS_IN_LINE - 1];
        p1.position += Vector2D(25.0f, 0.0f);
        p1.prevPosition += Vector2D(25.0f, 0.0f);

        auto& p2 = points[POINTS_IN_LINE * (POINTS_IN_LINE-1)];
        p2.position += Vector2D(-25.0f, 0.0f);
        p2.prevPosition += Vector2D(-25.0f, 0.0f);
        auto& p3 = points[POINTS_IN_LINE * (POINTS_IN_LINE - 1) + (POINTS_IN_LINE-1)];
        p3.position += Vector2D(25.0f, 0.0f);
        p3.prevPosition += Vector2D(25.0f, 0.0f);

        std::vector<sf::CircleShape> circles;

        for (int i = 0; i < POINTS_IN_LINE; ++i)
        {
            for (int j = 0; j < POINTS_IN_LINE; ++j)
            {
                circles.emplace_back(points[i].position.getX(), points[i].position.getY());
            }
        }

        std::vector<Stick> sticks;

        for (int i = 0; i < POINTS_IN_LINE; ++i)
        {
            for (int j = 0; j < STICK_SIZE; ++j)
            {
                sticks.emplace_back(&points[j + i * POINTS_IN_LINE], &points[(j + 1) + i * POINTS_IN_LINE]);
            }
            for (int j = 0; j < POINTS_IN_LINE; ++j)
            {
                if (i < POINTS_IN_LINE - 1)
                {
                    sticks.emplace_back(&points[j + i * POINTS_IN_LINE], &points[j + (i + 1) * POINTS_IN_LINE]);
                }
            }
            if(i < POINTS_IN_LINE - 1)
            {
                sticks.emplace_back(&points[STICK_SIZE + i * POINTS_IN_LINE], &points[STICK_SIZE + (i + 1) * POINTS_IN_LINE]);
            }
        }

        float friction = 0.9f;

        while (m_window.isOpen())
        {
            Input::buttonsClick(m_window);
            sf::Time l_elapsed = clock.getElapsedTime();
            l_prevTime = l_currentTime;
            l_currentTime = l_elapsed.asSeconds();
            float l_deltaTime = l_currentTime - l_prevTime;

            for(int i = 0; i < points.size(); ++i)
            {
                auto& p = points[i];
                if (!p.unmovable)
                {
                    auto velocity = p.position - p.prevPosition;
                    Vector2D accel(0.0f, 1.02f);
                    accel.setX(0.0f);
                    p.prevPosition = p.position;
                    p.position += velocity;
                    p.position += accel * l_deltaTime;
                }
            }


            for(int j = 0; j < 1; ++j)
            {
                for (int i = 0; i < 2 * (STICK_SIZE * POINTS_IN_LINE) + STICK_SIZE; ++i)
                {
                    sticks[i].update(l_deltaTime);
                }

                for (int i = 0; i < points.size(); ++i)
                {
                    auto& p = points[i];
                    auto& circle = circles[i];
                    if(!p.unmovable)
                    {
                        auto velocity = p.position - p.prevPosition;

                        if ((p.position.getY() - circle.getRadius()) > l_windowHeight)
                        {
                            p.position.setY(l_windowHeight - circle.getRadius());
                            p.prevPosition.setY(p.position.getY() + velocity.getY() * bouncy);
                        }
                        if ((p.position.getY() + circle.getRadius()) < 0.0f)
                        {
                            p.position.setY(circle.getRadius());
                            p.prevPosition.setY(p.position.getY() + velocity.getY() * bouncy);
                        }
                        if ((p.position.getX() - circle.getRadius()) > l_windowWidth)
                        {
                            p.position.setX(l_windowWidth - circle.getRadius());
                            p.prevPosition.setX(p.position.getX() + velocity.getX() * bouncy);
                        }
                        if ((p.position.getX() + circle.getRadius()) < 0.0f)
                        {
                            p.position.setX(circle.getRadius());
                            p.prevPosition.setX(p.position.getX() + velocity.getX() * bouncy);
                        }
                    }
                }
            }

            m_window.clear();
            for(int i = 0; i < points.size(); ++i)
            {

                auto& p = points[i];
                auto& cirlce = circles[i];
                cirlce.setPosition(p.position.getX(), p.position.getY());
                cirlce.setRadius(5.0f);
                m_window.draw(cirlce);
                for (int i = 0; i < 2 * (STICK_SIZE * POINTS_IN_LINE) + STICK_SIZE; ++i)//4 * (POINTS_IN_LINE * STICK_SIZE) - STICK_SIZE * 2; ++i)
                {
                    auto& pA = sticks[i].pointA->position;
                    auto& pB = sticks[i].pointB->position;
                    sf::Vertex line[] =
                    {
                        sf::Vertex(sf::Vector2f(pA.getX() + cirlce.getRadius(), 
                                                pA.getY() + cirlce.getRadius())),
                        sf::Vertex(sf::Vector2f(pB.getX() + cirlce.getRadius(), 
                                                pB.getY() + cirlce.getRadius()))
                    };

                    m_window.draw(line, 2, sf::Lines);
                }
            }
            m_window.display();

        }
    }
};

