#pragma once
#include "Vector2D.h"
#include "Ray.h"
#include <math.h>
#include <memory>
#include <iostream>

struct SquareAABB
{
    SquareAABB(Vector2D min, Vector2D size)
        :min(min), size(size)
    {

    }

    std::shared_ptr<Vector2D> rayIntersectionPoint(const Ray& ray)
    {
        Vector2D ro = ray.origin;
        Vector2D dir = ray.direction.getNormalized();
        Vector2D max = min - size;

        float tminX = (min.getX() - ro.getX()) / dir.getX();
        float tminY = (min.getY() - ro.getY()) / dir.getY();
        float tmaxX = (max.getX() - ro.getX()) / dir.getX();
        float tmaxY = (max.getY() - ro.getY()) / dir.getY();

        float maxX = fmax(tmaxX, tminX);
        float maxY = fmax(tmaxY, tminY);
        float minX = fmin(tmaxX, tminX);
        float minY = fmin(tmaxY, tminY);

        float maxFromMin = fmax(minX, minY);
        float minFromMax = fmin(maxX, maxY);

        if (minFromMax < 0.0f)
        {
            return nullptr;
        }

        if (maxFromMin > minFromMax)
        {
            return nullptr;
        }

        float t = maxFromMin;

        Vector2D point = ro + dir * t;

        return std::make_shared<Vector2D>(point);
    }

    Vector2D min;
    Vector2D size;
};

