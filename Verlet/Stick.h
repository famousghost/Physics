#pragma once
#include "ParticleVerlet.h"
class Stick
{
public:
    Stick(ParticleVerlet* pointA, ParticleVerlet* pointB);

    void update(float deltaTime);

    ParticleVerlet* pointA;
    ParticleVerlet* pointB;
    float length;
};

