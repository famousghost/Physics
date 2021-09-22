#include "Arm.h"
#include <cmath>
#define PI 3.141592653589793238

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
    return Vector2D(position.getX() + std::cos(angle) * length, 
                    position.getY() + std::sin(angle) * length);
}

void Arm::pointAt(Vector2D position)
{
    auto diff = position - this->position;
    this->angle = std::atan2(diff.getY(), diff.getX());
}

void Arm::drag(Vector2D position)
{
    pointAt(position);
    this->position = position - Vector2D(this->length * std::cos(this->angle),
                                         this->length * std::sin(this->angle));

    if (this->parent)
    {
        this->parent->drag(this->position);
    }

}

Vector2D Arm::getEndIK() const
{
    return Vector2D(position.getX() + std::cos(angle) * length,
                    position.getY() + std::sin(angle) * length);
}

void Arm::setAngle(float angle)
{
    this->angle = angle;
}

void Arm::setParent(Arm* arm)
{
    parent = arm;
}

Arm* Arm::getParent()
{
    return parent;
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
