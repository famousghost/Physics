#pragma once
#include "Vector2D.h"

class Particle
{
public:
    Particle(float x, float y, float speed, float angle, float radius);

    void update(float deltaTime);

    Vector2D collision(const Particle & point);

    Vector2D position;
    Vector2D velocity;
    float radius;
};

