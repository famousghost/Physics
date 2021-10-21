#pragma once
#include <iostream>
#include "GameWindow.h"
#include "Input.h"
#include <cstdlib>
#include <ctime>
#include "Utilities.h"
#include "Line.h"
#include "Ray.h"
#include "SquareAABB.h"

#define RAY_LENGTH 100000000.0

class SmallFunctionsTest
{
public:
    static void main()
    {
        sf::ContextSettings settings;
        settings.antialiasingLevel = 8;
        const unsigned int l_windowWidth = 1280;
        const unsigned int l_windowHeight = 720;
        std::string l_title = "Small Functions test";
        sf::RenderWindow m_window(sf::VideoMode{ l_windowWidth, l_windowHeight }, l_title, sf::Style::Default, settings);
        float l_prevTime = 0.0f;
        float l_currentTime = 0.0f;
        sf::Clock clock;


        sf::CircleShape circle;
        float radius = 5.0f;
        circle.setPosition(l_windowWidth / 2.0f, l_windowHeight / 2.0f);
        circle.setRadius(radius);

        Line a(Vector2D(200.0f, 300.0f), Vector2D(500.0f, 300.0f));


        sf::Vertex aVert[2] =
        {
            sf::Vertex(sf::Vector2f(a.a.getX(), a.a.getY())),
            sf::Vertex(sf::Vector2f(a.b.getX(), a.b.getY()))
        };

        Ray ray(Vector2D(l_windowWidth / 2, l_windowHeight / 2), Vector2D(-1.0f, -1.0f));

        SquareAABB aabb[4]
        {
            SquareAABB(Vector2D(300.0f, 100.0f), Vector2D(100.0f, 100.0f)),
            SquareAABB(Vector2D(900.0f, 500.0f), Vector2D(100.0f, 100.0f)),
            SquareAABB(Vector2D(300.0f, 300.0f), Vector2D(100.0f, 100.0f)),
            SquareAABB(Vector2D(1000.0f, 600.0f), Vector2D(100.0f, 100.0f))
        };

        sf::Vertex xAxis[2]
        {
            sf::Vertex(sf::Vector2f(0.0f, l_windowHeight / 2.0f)),
            sf::Vertex(sf::Vector2f(l_windowWidth, l_windowHeight / 2.0f)),
        };

        sf::Vertex yAxis[2]
        {
            sf::Vertex(sf::Vector2f(l_windowWidth / 2.0f, 0.0f)),
            sf::Vertex(sf::Vector2f(l_windowWidth / 2.0f, l_windowHeight)),
        };

        Vector2D center(l_windowWidth / 2.0f, l_windowHeight / 2.0f);

        float t = 0.0f;
        while (m_window.isOpen())
        {
            Input::buttonsClick(m_window);
            m_window.clear();
            sf::Time l_elapsed = clock.getElapsedTime();
            l_prevTime = l_currentTime;
            l_currentTime = l_elapsed.asSeconds();
            float l_deltaTime = l_currentTime - l_prevTime;
            //auto mousePos = sf::Mouse::getPosition(m_window);
            /*float x = Utilities::clamp(mousePos.x, radius, l_windowWidth - radius * 2.0f);
            float y = Utilities::clamp(mousePos.y, radius, l_windowHeight - radius * 2.0f);*/
            /*if (t >= 1.0f)
            {
                t = 0.0f;
            }
            float x = Utilities::lerp(t, radius, l_windowWidth - radius * 2.0f);
            float y = Utilities::lerp(t, radius, l_windowHeight - radius * 2.0f);
            circle.setPosition(x, y);*/
            /*float r = Utilities::map(Utilities::clamp((float)mousePos.x, 0.0f, l_windowWidth), 0.0f, l_windowWidth, 5.0f, 20.0f);
            std::cout << r << std::endl;
            circle.setRadius(r);*/
            /*auto mousePos = sf::Mouse::getPosition(m_window);
            Line b(Vector2D(300.0f, 100.0f), Vector2D((float)mousePos.x, (float)mousePos.y));

            sf::Vertex bVert[2] =
            {
                sf::Vertex(sf::Vector2f(b.a.getX(), b.a.getY())),
                sf::Vertex(sf::Vector2f(b.b.getX(), b.b.getY()))
            };
            auto line = a.lineIntersectingPoint(b);
            if(line != nullptr)
            {
                Vector2D point = *line - Vector2D(5.0f, 5.0f);

                sf::CircleShape intersectionPoint;
                intersectionPoint.setRadius(5.0f);
                intersectionPoint.setPosition(sf::Vector2f(point.getX(), point.getY()));

                m_window.draw(intersectionPoint);
            }
            m

            m_window.draw(aVert, 2, sf::Lines);
            m_window.draw(bVert, 2, sf::Lines);*/


            /*auto mousePos = sf::Mouse::getPosition(m_window);
            Vector2D mouse = Vector2D(mousePos.x, mousePos.y);
            ray.direction = mouse - ray.origin;
            Vector2D dirNorm = ray.direction.getNormalized();
            sf::Vertex line[2]
            {
                sf::Vertex(sf::Vector2f(ray.origin.getX(), ray.origin.getY())),
                sf::Vertex(sf::Vector2f(dirNorm.getX() * RAY_LENGTH, dirNorm.getY() * RAY_LENGTH))
            };

            for (int i = 0; i < 4; ++i)
            {
                sf::RectangleShape rectShape;

                rectShape.setPosition(sf::Vector2f(aabb[i].min.getX() - aabb[i].size.getX(), aabb[i].min.getY() - aabb[i].size.getY()));
                rectShape.setSize(sf::Vector2f(aabb[i].size.getX(), aabb[i].size.getY()));
                auto intersectionPoint = aabb[i].rayIntersectionPoint(ray);

                if (intersectionPoint)
                {
                    sf::Vertex lineIntersection[2]
                    {
                        sf::Vertex(sf::Vector2f(ray.origin.getX(), ray.origin.getY())),
                        sf::Vertex(sf::Vector2f(intersectionPoint->getX(), intersectionPoint->getY()))
                    };
                    sf::CircleShape interPoint;
                    float radius = 5.0f;
                    interPoint.setPosition(sf::Vector2f(intersectionPoint->getX() - radius, intersectionPoint->getY() - radius));
                    interPoint.setRadius(5.0f);
                    interPoint.setFillColor(sf::Color::Red);
                    m_window.draw(interPoint);
                    //m_window.draw(lineIntersection, 2, sf::Lines);
                }
                else
                {
                    m_window.draw(line, 2, sf::Lines);
                }


                m_window.draw(rectShape);
            }*/


            auto mousePos = sf::Mouse::getPosition(m_window);

            auto mouseX = Utilities::map(mousePos.x, 0.0f, l_windowWidth, -(l_windowWidth/2.0f), l_windowWidth/2.0f);
            auto mouseY = Utilities::map(mousePos.y, 0.0f, l_windowHeight, -(l_windowHeight / 2.0f), l_windowHeight / 2.0f);
            Vector2D vec(mouseX, mouseY);

            sf::Vertex line[2]
            {
                sf::Vertex(sf::Vector2f(l_windowWidth / 2.0f, l_windowHeight / 2.0f), sf::Color::Blue),
                sf::Vertex(sf::Vector2f(vec.getX() + center.getX(), vec.getY() + center.getY()), sf::Color::Blue),
            };

            Vector2D vec2(0.0f, -100.0f);

            sf::Vertex line2[2]
            {
                sf::Vertex(sf::Vector2f(l_windowWidth / 2.0f, l_windowHeight / 2.0f), sf::Color::Green),
                sf::Vertex(sf::Vector2f(vec2.getX() + center.getX(), vec2.getY() + center.getY()), sf::Color::Green),
            };
            auto reflVec = Utilities::reflect(vec, vec2);

            sf::Vertex reflLine[2]
            {
                sf::Vertex(sf::Vector2f(center.getX(), center.getY()), sf::Color::Red),
                sf::Vertex(sf::Vector2f(reflVec.getX() + center.getX(), reflVec.getY() + center.getY()), sf::Color::Red),
            };

            sf::CircleShape cirlce;
            circle.setRadius(5.0f);
            circle.setPosition(reflVec.getX(), reflVec.getY());

            m_window.draw(xAxis, 2, sf::Lines);
            m_window.draw(yAxis, 2, sf::Lines);
            m_window.draw(line, 2, sf::Lines);
            m_window.draw(reflLine, 2, sf::Lines);
            m_window.draw(line2, 2, sf::Lines);
            m_window.display();
            //t += l_deltaTime;
        }
    }
};

