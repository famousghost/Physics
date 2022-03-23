#pragma once
#include <iostream>
#include "GameWindow.h"
#include "Input.h"
#include "Utilities.h"
#include <cstdlib>
#include <ctime>

#define PI 3.141592653589793238

class DistancePointAndLine
{
public:
    static void main()
    {
        sf::ContextSettings settings;
        settings.antialiasingLevel = 8;
        const unsigned int l_windowWidth = 1280;
        const unsigned int l_windowHeight = 720;
        std::string l_title = "Distance Line and Point";
        sf::RenderWindow m_window(sf::VideoMode{ l_windowWidth, l_windowHeight }, l_title, sf::Style::Default, settings);
        float l_prevTime = 0.0f;
        float l_currentTime = 0.0f;
        sf::Clock clock;

        float angle = 90.0f;

        Vector2D a(0.0f, l_windowHeight / 2.0f);

        Vector2D b(l_windowWidth, 0.0f);

        Vector2D c;



        while (m_window.isOpen())
        {
            Input::buttonsClick(m_window);
            m_window.clear();
            sf::Time l_elapsed = clock.getElapsedTime();
            l_prevTime = l_currentTime;
            l_currentTime = l_elapsed.asSeconds();
            float l_deltaTime = l_currentTime - l_prevTime;

            auto mPos = sf::Mouse::getPosition(m_window);
            Vector2D mousePos(mPos.x, mPos.y);

            c.setX(mousePos.getX());
            c.setY(mousePos.getY());




            drawLine(m_window, a, b);

            Vector2D closestPoint = calculateClosestPointFromPointToLine(c, a, b);

            sf::CircleShape point1;
            point1.setPosition(sf::Vector2f(closestPoint.getX(), closestPoint.getY()));
            point1.setRadius(5.0f);

            m_window.draw(point1);

            sf::CircleShape point2;
            point2.setPosition(sf::Vector2f(c.getX(), c.getY()));
            point2.setRadius(5.0f);

            m_window.draw(point2);

            drawLine(m_window, c, closestPoint);

            m_window.display();

        }
    }

    static Vector2D calculateClosestPointFromPointToLine(Vector2D point, Vector2D a, Vector2D b)
    {
        Vector2D ab = b - a;
        Vector2D pointA = point - a;

        float t = pointA.dotProduct(ab) / ab.dotProduct(ab);

        Vector2D castVec = ab * t;

        castVec += Vector2D(0.0f, a.getY() - 5.0f);

        return castVec;
    }

    static void drawLine(sf::RenderWindow& window, const Vector2D& a, const Vector2D& b)
    {
        sf::Vertex line[2] =
        {
            sf::Vertex(sf::Vector2f(a.getX(), a.getY())),
            sf::Vertex(sf::Vector2f(b.getX(), b.getY())),
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

