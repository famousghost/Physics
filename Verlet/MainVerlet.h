#pragma once
#include <iostream>
#include "GameWindow.h"
#include "Input.h"
#include "ParticleVerlet.h"
#include "Stick.h"
#include <cstdlib>
#include <ctime>

#define MOUSE_RADIUS 7.0
#define POINTS_IN_LINE 20
#define STICK_SIZE 19
#define ITERATIONS (2 * (STICK_SIZE * POINTS_IN_LINE) + STICK_SIZE)
#define PI 3.141592653589793238

constexpr float GRAVITY = 9.81f;

class MainVerlet
{
public:
    static void main()
    {
        sf::ContextSettings settings;
        settings.antialiasingLevel = 8;
        const unsigned int l_windowWidth = 1280;
        const unsigned int l_windowHeight = 720;
        std::string l_title = "Physics Tutorial";
        sf::RenderWindow m_window(sf::VideoMode{ l_windowWidth, l_windowHeight }, l_title, sf::Style::Default, settings);
        float l_prevTime = 0.0f;
        float l_currentTime = 0.0f;
        float bouncy = 0.9f;
        sf::Clock clock;
        auto w = l_windowWidth / 2.0f;
        std::vector<ParticleVerlet> points;
        float beginPosX = 300.0f;
        float beginPosY = 10.0f;

        std::vector<sf::Vertex> vertices;

        for (int i = 0; i < POINTS_IN_LINE; ++i)
        {
            for (int j = 0; j < POINTS_IN_LINE; ++j)
            {
                bool unmoveable = false;
                if(i == 0 && j % 2 == 0)
                {
                    unmoveable = true;
                }
                points.emplace_back(beginPosX + 20.0f * j, 
                                    beginPosY + 20.0f * i,
                                    beginPosX + 20.0f * j,
                                    beginPosY + 20.0f * i,
                                    5.0f,
                                    unmoveable);
            }
        }

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

        for (int i = 0; i < ITERATIONS; ++i)
        {
            const auto& pA = sticks[i].pointA;
            const auto& pB = sticks[i].pointB;
            vertices.push_back(sf::Vector2f(pA->position.getX() + pA->radius, pA->position.getY() + pA->radius));
            vertices.push_back(sf::Vector2f(pB->position.getX() + pB->radius, pB->position.getY() + pB->radius));
        }

        float friction = 0.9f;

        while (m_window.isOpen())
        {
            Input::buttonsClick(m_window);
            m_window.clear();
            sf::Time l_elapsed = clock.getElapsedTime();
            l_prevTime = l_currentTime;
            l_currentTime = l_elapsed.asSeconds();
            float l_deltaTime = l_currentTime - l_prevTime;

            for(int i = 0; i < points.size(); ++i)
            {
                auto& p = points[i];
                if (!p.unmovable)
                {
                    auto mousePos = sf::Mouse::getPosition(m_window);
                    ParticleVerlet mouseP(mousePos.x,
                                          mousePos.y,
                                          mousePos.x,
                                          mousePos.y,
                                          MOUSE_RADIUS,
                                          true);
                    auto velocity = p.position - p.prevPosition;
                    Vector2D accel(0.0f, GRAVITY);
                    p.prevPosition = p.position;
                    auto dir = p.collision(mouseP);
                    if (dir != Vector2D())
                    {
                        velocity += dir;
                    }
                    p.position += velocity;
                    p.position += accel * l_deltaTime;
                }
            }

            for(int j = 0; j < 4; ++j)
            {
                int k = 0;
                for (int i = 0; i < ITERATIONS; ++i)
                {
                    sticks[i].update(l_deltaTime);
                    const auto& pA = sticks[i].pointA->position;
                    const auto& pB = sticks[i].pointB->position;
                    vertices[k].position = sf::Vector2f(pA.getX(), pA.getY());
                    vertices[k+1].position = sf::Vector2f(pB.getX(), pB.getY());
                    k+=2;
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

            for(int i = 0; i < points.size(); ++i)
            {
                auto& p = points[i];
                auto& cirlce = circles[i];
                cirlce.setPosition(p.position.getX(), p.position.getY());
                cirlce.setRadius(p.radius);
            }
            m_window.draw(&vertices[0], vertices.size(), sf::Lines);
            m_window.display();

        }
    }
};

