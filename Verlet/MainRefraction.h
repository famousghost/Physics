#pragma once
#include <iostream>
#include "GameWindow.h"
#include "Input.h"
#include "Utilities.h"
#include <cstdlib>
#include <ctime>

#define PI 3.141592653589793238

class MainRefraction
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

        Vector2D a = Vector2D(0.0f, l_windowHeight/2.0f);
        Vector2D b = Vector2D(l_windowWidth, l_windowHeight / 2.0f);

        Vector2D normal = Vector2D(0.0f, 1.0f);

        Vector2D origin = Vector2D(0.0f, 0.0f);
        Vector2D direction = Vector2D(1.0f, 1.0f).getNormalized();

        while (m_window.isOpen())
        {
            Input::buttonsClick(m_window);
            m_window.clear();
            sf::Time l_elapsed = clock.getElapsedTime();
            l_prevTime = l_currentTime;
            l_currentTime = l_elapsed.asSeconds();
            float l_deltaTime = l_currentTime - l_prevTime;
            auto mPos = sf::Mouse::getPosition(m_window);
            Vector2D mousePos = Vector2D(mPos.x, mPos.y);

            drawLine(m_window, a, b, sf::Color::White);
            direction = mousePos - origin;
            Vector2D closestPoint = calculateIntersectionPoint(origin, a, direction, b);
            drawLine(m_window, origin, direction.getNormalized() * std::min(direction.getLength(), closestPoint.getLength()), sf::Color::Red);
 
            Vector2D refractedVec = refract(direction.getNormalized(), normal.getNormalized(), 1.0f, 1.33f); // air -> water

            drawLine(m_window, closestPoint, closestPoint + refractedVec * 1000.0f, sf::Color::Blue);

            sf::CircleShape c;
            c.setPosition(sf::Vector2f(closestPoint.getX() - 3.0f, closestPoint.getY() - 3.0f));
            c.setRadius(3.0f);
            m_window.draw(c);
            m_window.display();

        }
    }

    static Vector2D getVectorFromPoints(Vector2D a, Vector2D  b) // dir to point B
    {
        return b - a;
    }

    static Vector2D rotate(Vector2D a, float angle)
    {
        return Vector2D(a.getX() * cos(angle) - a.getY() * sin(angle), a.getX() * sin(angle) + a.getY() * cos(angle));
    }

    static Vector2D refract(Vector2D a, Vector2D normal, float n1, float n2)
    {
        float angle = acos(dot(a, normal));

        float n = n1 / n2;

        float refractAngle = asin(n * sin(angle));

        Vector2D refractedVector = rotate(normal, -refractAngle);

        return refractedVector;
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

    static float cross(Vector2D a, Vector2D n)
    {
        return a.getX() * n.getY() - a.getY() * n.getX();
    }

    static void drawLine(sf::RenderWindow& window, const Vector2D& a, const Vector2D& b, const sf::Color color)
    {
        sf::Vertex line[2] =
        {
            sf::Vertex(sf::Vector2f(a.getX(), a.getY()), color),
            sf::Vertex(sf::Vector2f(b.getX(), b.getY()), color),
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

