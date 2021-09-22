#pragma once
#include <SFML\Graphics.hpp>
#include "Vector2D.h"
#include <utility>

class Arm
{
public:
    Arm(Vector2D position, float length, float angle, Arm* parent = nullptr);

    Vector2D getEnd() const;

    void pointAt(Vector2D position);

    void drag(Vector2D position);

    Vector2D getEndIK() const;

    void setAngle(float angle);

    void setParent(Arm * arm);

    Arm * getParent();

    void setLength(float length);

    void setPosition(Vector2D newPos);

    Vector2D getPos() const;

private:
    Vector2D position;
    float length;
    float angle;
    Arm* parent;
};

