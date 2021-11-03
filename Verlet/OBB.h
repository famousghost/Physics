#pragma once
#include <memory>
#include "Vector2D.h"
#include "Utilities.h"

class OBB
{
public:
    OBB(Vector2D pos, Vector2D size)
        :pos(pos), size(size)
    {
        normals[0] = Vector2D(1.0f, 0.0f);
        normals[1] = Vector2D(0.0f, 1.0f);
        norms[0] = Vector2D(1.0f, 0.0f);
        norms[1] = Vector2D(0.0f, 1.0f);

        vertices[0] = Vector2D(-1.0f, -1.0f);
        vertices[1] = Vector2D(1.0f, -1.0f);
        vertices[2] = Vector2D(-1.0f, 1.0f);
        vertices[3] = Vector2D(1.0f, 1.0f);

        verts[0] = vertices[0] * size + pos;
        verts[1] = vertices[1] * size + pos;
        verts[2] = vertices[2] * size + pos;
        verts[3] = vertices[1] * size + pos;
        verts[4] = vertices[2] * size + pos;
        verts[5] = vertices[3] * size + pos;
    }

    bool collsion(const OBB& obj1, const OBB& obj2)
    {
        for (int i = 0; i < 2; ++i)
        {
            if (!checkCollisionOnNormal(obj1, obj2, obj1.norms[i]))
            {
                return false;
            }
        }

        for (int i = 0; i < 2; ++i)
        {
            if (!checkCollisionOnNormal(obj1, obj2, obj2.norms[i]))
            {
                return false;
            }
        }

        return true;
    }

    bool checkCollisionOnNormal(const OBB& obj1, const OBB& obj2, const Vector2D& normal)
    {
        float minObj1 = 1000000.0f;
        float maxObj1 = -1000000.0f;

        float minObj2 = 1000000.0f;
        float maxObj2 = -1000000.0f;

        for (int j = 0; j < 6; ++j)
        {
            auto obj2Value = Utilities::castVectorToVectorLength(obj2.verts[j], normal);
            auto obj1Value = Utilities::castVectorToVectorLength(obj1.verts[j], normal);

            minObj1 = std::min(minObj1, obj1Value);
            minObj2 = std::min(minObj2, obj2Value);

            maxObj1 = std::max(maxObj1, obj1Value);
            maxObj2 = std::max(maxObj2, obj2Value);
        }
        if (minObj1 > maxObj2 || maxObj1 < minObj2)
        {
            return false;
        }
        return true;
    }

    void update(Vector2D pos, float angle)
    {
        this->pos = pos;
        rotate(angle);
    }

    void rotate(float angle)
    {
        float rads = Utilities::toRadians(angle);

        setVert(rads, 0, 0);
        setVert(rads, 1, 1);
        setVert(rads, 2, 2);
        setVert(rads, 3, 1);
        setVert(rads, 4, 2);
        setVert(rads, 5, 3);

        norms[0].setX(std::cos(rads) * normals[0].getX() - std::sin(rads) * normals[0].getY());
        norms[0].setY(std::sin(rads) * normals[0].getX() + std::cos(rads) * normals[0].getY());

        norms[1].setX(std::cos(rads) * normals[1].getX() - std::sin(rads) * normals[1].getY());
        norms[1].setY(std::sin(rads) * normals[1].getX() + std::cos(rads) * normals[1].getY());
    }

    void translate(Vector2D pos)
    {
        this->pos += pos;
    }

    void MoveTo(Vector2D pos)
    {
        this->pos = pos;
    }

    void setVert(float rads, int i, int j)
    {
        verts[i].setX((std::cos(rads) * vertices[j].getX() - std::sin(rads) * vertices[j].getY()));
        verts[i].setY((std::sin(rads) * vertices[j].getX() + std::cos(rads) * vertices[j].getY()));
        verts[i] = verts[i] * size + pos;
    }

    Vector2D verts[6];
    Vector2D norms[2];


    Vector2D pos;
    Vector2D size;

private:

    Vector2D vertices[4];
    Vector2D normals[2];


};

