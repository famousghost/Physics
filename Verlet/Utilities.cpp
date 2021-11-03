#include "Utilities.h"
#include <cmath>
#include "Input.h"
#include <iostream>

float Utilities::normalization(float value, float min, float max)
{
    return (value - min) / (max - min);
}

float Utilities::lerp(float value, float min, float max)
{
    return (max - min) * value + min;
}

float Utilities::clamp(float value, float min, float max)
{
    return std::fmin(std::fmax(value, min), max);
}

float Utilities::map(float value, float srcMin, float srcMax, float dstMin, float dstMax)
{
    float val = (value - srcMin) / (srcMax - srcMin);
    return (dstMax - dstMin) * val + dstMin;
}

Vector2D Utilities::castVectorToVector(const Vector2D & vec1, const Vector2D& vec2)
{
    Vector2D vec2Normalized = vec2.getNormalized();
    return vec2Normalized * vec1.dotProduct(vec2Normalized);
}

float Utilities::castVectorToVectorLength(const Vector2D & vec1, const Vector2D& vec2)
{
    Vector2D vec2Normalized = vec2.getNormalized();
    return vec1.dotProduct(vec2Normalized);
}

Vector2D Utilities::reflect(const Vector2D& vec, const Vector2D& normal)
{
    Vector2D vecBuf = vec;
    Vector2D normBuf = normal;
    return castVectorToVector(vec, normal) * 2.0f - vecBuf;
}

void Utilities::drag(Circle & circle, Vector2D mousePoint)
{
    if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        if (circle.pointCircleIntersection(mousePoint))
        {
            circle.position = mousePoint;
        }
    }
}

float Utilities::toRadians(float angle)
{
    return angle * PI / 180.0f;
}

float Utilities::toDegrees(float radians)
{
    return radians * 180.0f / PI;
}

Vector2D Utilities::rotate(const Vector2D & vec, float angle)
{
    float radians = toRadians(angle);
    return Vector2D(std::cos(radians) * vec.getX() - std::sin(radians) * vec.getY(),
                    std::sin(radians) * vec.getX() + std::cos(radians) * vec.getY());
}

