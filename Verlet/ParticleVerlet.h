#pragma once
#include "Vector2D.h"
class ParticleVerlet
{
public:
    ParticleVerlet(float x, float y, float xPrev, float yPrev, bool unmoveable);

    Vector2D position;
    Vector2D prevPosition;
    bool unmovable;
};

