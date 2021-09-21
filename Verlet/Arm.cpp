#include "Arm.h"
#include <cmath>

Arm::Arm(Vector2D position, float length, float angle, Arm* parent)
    :position(position), length(length), angle(angle), parent(parent)
{
}

Vector2D Arm::getEnd() const
{
    auto angle = this->angle;
    auto* parent = this->parent;
    while (parent)
    {
        angle += parent->angle;
        parent = parent->parent;
    }
    return Vector2D(position.getX() + std::sin(angle) * length, 
                    position.getY() + std::cos(angle) * length);
}

void Arm::setAngle(float angle)
{
    this->angle = angle;
}

void Arm::setLength(float length)
{
    this->length = length;
}

void Arm::setPosition(Vector2D newPos)
{
    this->position = newPos;
}

Vector2D Arm::getPos() const
{
    return position;
}
