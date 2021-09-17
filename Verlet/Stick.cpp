#include "Stick.h"

Stick::Stick(ParticleVerlet* pointA, ParticleVerlet* pointB)
{
    this->pointA = pointA;
    this->pointB = pointB;
    auto dir = pointA->position - pointB->position;
    length = dir.getLength();
}

void Stick::update(float deltaTime)
{
    auto dir = (pointB->position - pointA->position);
    auto distance = dir.getLength();
    auto diff = length - distance;
    auto percent = (diff / distance) * 0.5f;

    if(!pointA->unmovable)
    {
        pointA->position -= dir * percent * deltaTime;
    }
    if(!pointB->unmovable)
    {
        pointB->position += dir * percent * deltaTime;
    }

}
