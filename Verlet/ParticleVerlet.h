#pragma once
#include "Vector2D.h"
class ParticleVerlet
{
public:
    ParticleVerlet(float x, float y, float xPrev, float yPrev, float radius, bool unmoveable);

    Vector2D collision(const ParticleVerlet & point);

    Vector2D position;
    Vector2D prevPosition;
    float radius;
    bool unmovable;
};

