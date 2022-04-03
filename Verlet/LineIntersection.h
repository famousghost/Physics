#pragma once
#include <iostream>
#include "GameWindow.h"
#include "Input.h"
#include "Utilities.h"
#include <cstdlib>
#include <ctime>

#define PI 3.141592653589793238

class LineIntersection
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

        Vector2D a = Vector2D(20, 100);
        Vector2D b = Vector2D(20, 300);

        Vector2D c = Vector2D(400, 400);

        Vector2D d = Vector2D(400, 100);

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
            c = mousePos;

            drawLine(m_window, a, c);
            drawLine(m_window, b, d);

            Vector2D point = calculateIntersectionPoint(a, b, c, d);

            sf::CircleShape c;
            c.setPosition(point.getX() - 5.0f, point.getY() - 5.0f);

            c.setRadius(5.0f);

            m_window.draw(c);



            m_window.display();

        }
    }

    static Vector2D getVectorFromPoints(Vector2D a, Vector2D  b) // dir to point B
    {
        return b - a;
    }

    static Vector2D calculateIntersectionPoint(Vector2D a, Vector2D b, Vector2D c, Vector2D d)
    {
        Vector2D v = getVectorFromPoints(a, c);
        Vector2D u = getVectorFromPoints(b, d);
        Vector2D vPerp = perpendicularVector(v);
        Vector2D uPerp = perpendicularVector(u);

        float div = dot(uPerp, v);

        if (div == 0)
        {
            return Vector2D(1000000, 1000000);
        }

        float t = dot(uPerp, (b - a)) / dot(uPerp, v);
        float s = dot(vPerp, (b - a)) / dot(uPerp, v);

        if ((s > 1.0f || s < 0.0f) || (t > 1.0f || t < 0.0f))
        {
            return Vector2D(1000000, 1000000);
        }

        return a + v * t;
    }

    static float dot(Vector2D a, Vector2D b)
    {
        return a.getX() * b.getX() + a.getY() * b.getY();
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

    static Vector2D perpendicularVector(Vector2D v)
    {
        return Vector2D(-v.getY(), v.getX());
    }
};

