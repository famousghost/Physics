#include <iostream>
#include "Line.h"
#include <cmath>

Line::Line(Vector2D a, Vector2D b)
    :a(a), b(b)
{
}

std::shared_ptr<Vector2D> Line::lineIntersectingPoint(Line & line)
{
    auto A1 = b.getY() - a.getY();
    auto B1 = a.getX() - b.getX();
    auto C1 = A1 * a.getX() + B1 * a.getY();
    auto A2 = line.b.getY() - line.a.getY();
    auto B2 = line.a.getX() - line.b.getX();
    auto C2 = A2 * line.a.getX() + B2 * line.a.getY();

    auto div = A1 * B2 - A2 * B1;
    if (div == 0)
    {
        return nullptr;
    }
    float x = (B2 * C1 - B1 * C2) / div;
    float y = (A1 * C2 - A2 * C1) / div;
    Vector2D intersectionPoint = Vector2D(x, y);
    float rx0 = (intersectionPoint.getX() - a.getX()) / (b.getX() - a.getX());
    float ry0 = (intersectionPoint.getY() - a.getY()) / (b.getY() - a.getY());

    float rx1 = (intersectionPoint.getX() - line.a.getX()) / (line.b.getX() - line.a.getX());
    float ry1 = (intersectionPoint.getY() - line.a.getY()) / (line.b.getY() - line.a.getY());
    if (((rx0 >= 0.0f && rx0 <= 1.0f) || (ry0 >= 0.0f && ry0 <= 1.0f))
        && ((rx1 >= 0.0f && rx1 <= 1.0f) || (ry1 >= 0.0f && ry1 <= 1.0f)))
    {
        return std::make_shared<Vector2D>(intersectionPoint);
    }

    return nullptr;
}

