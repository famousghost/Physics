#pragma once
#include <iostream>
#include "GameWindow.h"
#include "Input.h"
#include "ParticleVerlet.h"
#include "Stick.h"
#include <cstdlib>
#include <ctime>

struct vec2
{
    vec2(float x, float y)
        :x(x), y(y)
    {}

    vec2(const vec2& vec)
    {
        x = vec.x;
        y = vec.y;
    }

    vec2& operator=(const vec2& vec)
    {
        x = vec.x;
        y = vec.y;
        return *this;
    }

    vec2 operator+(const vec2& vec)
    {
        return vec2(x + vec.x, y + vec.y);
    }

    vec2& operator+=(const vec2& vec)
    {
        x += vec.x;
        y += vec.y;
        return *this;
    }

    vec2 operator-(const vec2& vec)
    {
        return vec2(x - vec.x, y - vec.y);
    }

    vec2& operator-=(const vec2& vec)
    {
        x -= vec.x;
        y -= vec.y;
        return *this;
    }

    vec2 operator/(float value)
    {
        return vec2(x / value, y / value);
    }

    vec2& operator/=(float value)
    {
        x /= value;
        y /= value;
        return *this;
    }

    vec2 operator*(float value)
    {
        return vec2(x * value, y * value);
    }

    vec2& operator*=(float value)
    {
        x *= value;
        y *= value;
        return *this;
    }

    friend std::ostream& operator <<(std::ostream& out, const vec2& vec)
    {
        out << "(" << vec.x << ", " << vec.y << ")";
        return out;
    }

    float x;
    float y;
};

struct operations
{
    static float dot(const vec2& a, const vec2& b)
    {
        return a.x * b.x + a.y * b.y;
    }

    static float len(const vec2& a)
    {
        return std::sqrt(a.x * a.x + a.y * a.y);
    }

    static vec2 normalize(vec2 a)
    {
        return a / len(a);
    }

    static float distance(const vec2& a, const vec2& b)
    {
        return std::sqrt((b.x - a.x) * (b.x - a.x) + (b.y - a.y) * (b.y - a.y));
    }
};

class MainTest
{
public:
    static void main()
    {
        int points = 0;
        int currentAmount = 0;

        const unsigned int l_windowWidth = 1280;
        const unsigned int l_windowHeight = 720;
        std::string l_title = "Program 1";
        sf::RenderWindow m_window(sf::VideoMode{ l_windowWidth, l_windowHeight }, l_title, sf::Style::Default);
        float l_prevTime = 0.0f;
        float l_currentTime = 0.0f;
        sf::Clock clock;

        vec2 vert = vec2(l_windowWidth / 2.0f, l_windowHeight - 300.0f);


        vec2 norm(0.0f, 1.0f);

        sf::Vector2f v(vert.x, vert.y);

        sf::CircleShape c;

        c.setRadius(5.0f);
        while (m_window.isOpen())
        {
            Input::buttonsClick(m_window);
            sf::Time l_elapsed = clock.getElapsedTime();
            l_prevTime = l_currentTime;
            l_currentTime = l_elapsed.asSeconds();
            float l_deltaTime = l_currentTime - l_prevTime;
            m_window.clear();

            auto mousePos = sf::Mouse::getPosition(m_window);

            vec2 lightPos = vec2(mousePos.x, mousePos.y);

            vec2 fromPointToLight = operations::normalize(vert - lightPos);

            sf::Vector2f l(lightPos.x, lightPos.y);
            sf::Vector2f fptl(fromPointToLight.x, fromPointToLight.y);

            if (operations::dot(fromPointToLight, norm) > 0.0f)
            {
                c.setFillColor(sf::Color::Red);
            }
            else if (operations::dot(fromPointToLight, norm) < 0.0f)
            {
                c.setFillColor(sf::Color::Blue);
            }
            else
            {
                c.setFillColor(sf::Color::White);
            }


            c.setPosition(v);
            m_window.draw(c);

            c.setPosition(l);
            m_window.draw(c);

            sf::Vertex vertex[2]
            {
                v,
                l
            };

            sf::Vertex normal[2]
            {
                v,
                sf::Vector2f(v.x, 0.0f)
            };

            vec2 vl = vert - lightPos;
            vec2 norm = vec2(vert.x, 0.0f) - vert;

            vec2 reflVl = vl - (norm * operations::dot(vl, norm) / operations::dot(norm, norm))* 2.0f + vert;


            sf::Vector2f rvl = sf::Vector2f(reflVl.x, reflVl.y);
            sf::Vertex reflVec[2]
            {
                v,
                rvl 
            };

            m_window.draw(vertex, 2, sf::Lines);
            m_window.draw(normal, 2, sf::Lines);
            m_window.draw(reflVec, 2, sf::Lines);

            m_window.display();

        }
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
};

