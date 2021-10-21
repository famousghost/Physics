#pragma once
#include "Circle.h"

class Utilities
{
public:
    static float normalization(float value, float min, float max);
    static float lerp(float value, float min, float max);
    static float clamp(float value, float min, float max);
    static float map(float value, float srcMin, float srcMax, float dstMin, float dstMax);
    static Vector2D castVectorToVector(const Vector2D & vec1, const Vector2D& vec2);
    static Vector2D reflect(const Vector2D & vec, const Vector2D & normal);
    static void drag(Circle& circle, Vector2D mousePoint);
};

