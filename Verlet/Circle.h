#pragma once
#include "Vector2D.h"

struct Circle
{
    Vector2D position;
    float radius;

    Circle(Vector2D pos, float radius)
        :position(pos), radius(radius)
    {

    }

    bool pointCircleIntersection(Vector2D point)
    {
        float dist = (point - position).getLength();
        if (dist <= radius)
        {
            return true;
        }
        return false;
    }
};

