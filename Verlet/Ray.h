#pragma once
#include "Vector2D.h"

struct Ray
{
    Ray(Vector2D origin, Vector2D direction)
        :origin(origin), direction(direction)
    {

    }

    Vector2D origin;
    Vector2D direction;
};

