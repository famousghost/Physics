#pragma once
#include "Vector2D.h"
#include <memory>

class Line
{
public:
    Line(Vector2D a, Vector2D b);


    std::shared_ptr<Vector2D> lineIntersectingPoint(Line& line);

    Vector2D a;
    Vector2D b;



};

