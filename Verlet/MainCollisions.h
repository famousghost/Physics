#pragma once
#include <iostream>
#include "GameWindow.h"
#include "Input.h"
#include <cstdlib>
#include <ctime>
#include <vector>
#include "OBB.h"

class MainCollisions
{
public:
    static void main()
    {
        int points = 0;
        int currentAmount = 0;

        const unsigned int l_windowWidth = 1280;
        const unsigned int l_windowHeight = 720;
        std::string l_title = "Collision Detection";
        sf::RenderWindow m_window(sf::VideoMode{ l_windowWidth, l_windowHeight }, l_title, sf::Style::Default);
        float l_prevTime = 0.0f;
        float l_currentTime = 0.0f;
        sf::Clock clock;

        OBB square1(Vector2D(l_windowWidth/2.0f, l_windowHeight/2.0f), Vector2D(100.0f, 50.0f));

        OBB square2(Vector2D(l_windowWidth / 2.0f + 150.0f, l_windowHeight / 2.0f + 150.0f) , Vector2D(120.0f, 50.0f));

        sf::RectangleShape rect;

        rect.setPosition(l_windowWidth/3.0f, l_windowHeight/3.0f);
        rect.setSize(sf::Vector2f(100.0f, 100.0f));

        float t2 = 1.0f;
        float t = 1.0f;

        sf::Vector2f center(l_windowWidth/2.0f, l_windowHeight/2.0f);

        while (m_window.isOpen())
        {
            Input::buttonsClick(m_window);
            sf::Time l_elapsed = clock.getElapsedTime();
            l_prevTime = l_currentTime;
            l_currentTime = l_elapsed.asSeconds();
            float l_deltaTime = l_currentTime - l_prevTime;
            m_window.clear();

            sf::Color color = sf::Color::White;
            if (square1.collsion(square1, square2))
            {
                color = sf::Color::Red;
            }

            t += 1.0f * l_deltaTime;

            Input::buttonsClick(m_window);

            if (Input::s_rotateLeft)
            {
                t2 -= 100.0f * l_deltaTime;
            }
            if (Input::s_rotateRight)
            {
                t2 += 100.0f * l_deltaTime;
            }

            square1.rotate(t2);

            auto vertices = prepareVertices(square1, color);

            m_window.draw(&vertices[0], 6, sf::Triangles);

            auto mousePos = sf::Mouse::getPosition(m_window);
            square2.update(Vector2D(mousePos.x, mousePos.y), 0.0f);

            square2.rotate(-t2);

            vertices = prepareVertices(square2, color);

            m_window.draw(&vertices[0], 6, sf::Triangles);

            m_window.display();

        }
    }

    static std::vector<std::vector<sf::Vertex>> prepareNormal(const OBB& obj)
    {
        std::vector<sf::Vertex> normX
        {
            sf::Vertex(sf::Vector2f(obj.pos.getX(), obj.pos.getY())),
            sf::Vertex(sf::Vector2f(obj.pos.getX() - obj.norms[0].getX() * 500.0f, obj.pos.getY() - obj.norms[0].getY()*500.0f))
        };

        std::vector<sf::Vertex> normY
        {
            sf::Vertex(sf::Vector2f(obj.pos.getX(), obj.pos.getY())),
            sf::Vertex(sf::Vector2f(obj.pos.getX() - obj.norms[1].getX() * 500.0f, obj.pos.getY() - obj.norms[1].getY()*500.0f))
        };

        std::vector<std::vector<sf::Vertex>> result;
        result.push_back(normX);
        result.push_back(normY);
        return result;
    }

    static std::vector<sf::Vertex> prepareVertices(const OBB& obj, const sf::Color& color = sf::Color::White)
    {
        std::vector<sf::Vertex> vertices
        {
            sf::Vertex(sf::Vector2f(obj.verts[0].getX(),
                                    obj.verts[0].getY()),
                                    color),
            sf::Vertex(sf::Vector2f(obj.verts[1].getX(),
                                    obj.verts[1].getY()),
                                    color),
            sf::Vertex(sf::Vector2f(obj.verts[2].getX(),
                                    obj.verts[2].getY()),
                                    color),
            sf::Vertex(sf::Vector2f(obj.verts[3].getX(),
                                    obj.verts[3].getY()),
                                    color),
            sf::Vertex(sf::Vector2f(obj.verts[4].getX(),
                                    obj.verts[4].getY()),
                                    color),
            sf::Vertex(sf::Vector2f(obj.verts[5].getX(),
                                    obj.verts[5].getY()),
                                    color)
        };

        return vertices;
    }
};

