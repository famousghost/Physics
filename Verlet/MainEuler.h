#pragma once
#include <iostream>
#include "GameWindow.h"
#include "Input.h"
#include "Particle.h"
#include <cstdlib>
#include <ctime>
#include <vector>
#define PI 3.141592653589793238
#define PARTICLES_SIZE 500

class MainEuler
{
public:
    static void main()
    {
        int points = 0;
        int currentAmount = 0;



        const unsigned int l_windowWidth = 1280;
        const unsigned int l_windowHeight = 720;
        std::string l_title = "Physics Tutorial";
        sf::RenderWindow m_window(sf::VideoMode{ l_windowWidth, l_windowHeight }, l_title, sf::Style::Default);
        float l_prevTime = 0.0f;
        float l_currentTime = 0.0f;
        std::vector<Particle> particles;
        srand((unsigned int)time(NULL));
        float a = 5.0;
        sf::CircleShape circles[PARTICLES_SIZE];
        for (int i = 0; i < PARTICLES_SIZE; ++i)
        {
            float rnd = (float(rand()) / float((RAND_MAX)) * a);
            particles.emplace_back(rnd * l_windowWidth / 2.0f, 0.0f, rnd * 100.0f + 10.0f, PI * rnd, 5.0f);
        }

        Vector2D acceleration(0.0f, 1000.0f);
        sf::Clock clock;

        float friction = 0.9997f;
        float speed = 100.0f;

        Vector2D dir[]
        {
            Vector2D(0.0f, -1.0f),
            Vector2D(0.0f, 1.0f),
            Vector2D(-1.0f, 0.0f),
            Vector2D(1.0f, 0.0f)
        };

        while (m_window.isOpen())
        {
            Input::buttonsClick(m_window);
            sf::Time l_elapsed = clock.getElapsedTime();
            l_prevTime = l_currentTime;
            l_currentTime = l_elapsed.asSeconds();
            float l_deltaTime = l_currentTime - l_prevTime;
            m_window.clear();

            for (int i = 0; i < PARTICLES_SIZE; ++i)
            {
                auto& p = particles[i];
                auto& circle = circles[i];
                if ((p.position.getY() + circle.getRadius()) > l_windowHeight)
                {
                    p.velocity.setY(p.velocity.getY() * -1.0f);
                    p.position.setY(l_windowHeight - circle.getRadius());
                }
                if ((p.position.getY() - circle.getRadius()) < 0.0f)
                {
                    p.velocity.setY(p.velocity.getY() * -1.0f);
                    p.position.setY(circle.getRadius());
                }
                if ((p.position.getX() + circle.getRadius()) > l_windowWidth)
                {
                    p.velocity.setX(p.velocity.getX() * -1.0f);
                    p.position.setX(l_windowWidth - circle.getRadius());
                }
                if ((p.position.getX() - circle.getRadius()) < 0.0f)
                {
                    p.velocity.setX(p.velocity.getX() * -1.0f);
                    p.position.setX(circle.getRadius());
                }

                for (int j = 0; j < PARTICLES_SIZE; ++j)
                {
                    auto dir = p.collision(particles[j]);
                    if (dir == Vector2D())
                    {
                        continue;
                    }

                    p.velocity += dir;
                    p.velocity *= friction;
                }

                p.velocity += (acceleration * l_deltaTime);
                p.velocity *= friction;
                p.update(l_deltaTime);

                circle.setPosition(p.position.getX(), p.position.getY());
                circle.setFillColor(sf::Color::White);
                circle.setRadius(p.radius);
            }

            for (const auto& circle : circles)
            {
                m_window.draw(circle);
            }
            m_window.display();

        }
    }
};

