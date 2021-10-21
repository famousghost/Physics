#pragma once
#include "Vector2D.h"

struct Bezier
{
    Vector2D linearBezier(Vector2D a, Vector2D b, float t)
    {
        return lerp(a, b, t);
    }

    Vector2D quadricBezier(Vector2D a, Vector2D b, Vector2D c, float t)
    {
        Vector2D p0 = lerp(a, b, t);
        Vector2D p1 = lerp(b, c, t);
        return lerp(p0, p1, t);
    }


    Vector2D cubicBezier(Vector2D a, Vector2D b, Vector2D c, Vector2D d, float t)
    {
        Vector2D p0 = quadricBezier(a, b, c, t);
        Vector2D p1 = quadricBezier(b, c, d, t);
        return lerp(p0, p1, t);
    }

    std::vector<Vector2D> calculatePoints(Vector2D a, Vector2D b, Vector2D c, Vector2D d, int size)
    {
        std::vector<Vector2D> points;
        for (int i = 0; i < size; ++i)
        {
            float step = (float) i / size;
            points.push_back(cubicBezier(a, b, c, d, step));
        }

        return points;
    }

private:


    Vector2D lerp(Vector2D a, Vector2D b, float t)
    {
        return (b - a) * t + a;
    }
};

