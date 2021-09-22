#include "Vector2D.h"
#include <cmath>

Vector2D::Vector2D()
    :x(0), y(0)
{
}

Vector2D::Vector2D(float x, float y)
    :x(x), y(y)
{
}

float Vector2D::getLength()
{
    return sqrt(this->x * this->x + this->y * this->y);
}

float Vector2D::getAngle() 
{
    return atan2(this->y, this->x);
}

void Vector2D::setLenght(float length)
{
    float angle = getAngle();
    this->x = cos(angle) * length;
    this->y = sin(angle) * length;
}

void Vector2D::setAngle(float angle)
{
    float length = getLength();
    this->x = cos(angle) * length;
    this->y = sin(angle) * length;
}

void Vector2D::normalize()
{
    auto len = getLength();
    x /= len;
    y /= len;
}

float Vector2D::dotProduct(Vector2D v)
{
    return this->x * v.x + this->y * v.y;
}

Vector2D Vector2D::operator+(const Vector2D & v)
{
    return Vector2D(this->x + v.x, this->y + v.y);
}

Vector2D Vector2D::operator-(const Vector2D& v)
{
    return Vector2D(this->x - v.x, this->y - v.y);
}

Vector2D Vector2D::operator*(float value)
{
    return Vector2D(this->x * value, this->y * value);
}

Vector2D Vector2D::operator/(float value)
{
    if(value == 0.0f)
    { 
        return Vector2D();
    }
    return Vector2D(this->x / value, this->y / value);
}

void Vector2D::operator+=(const Vector2D& v)
{
    this->x += v.x;
    this->y += v.y;
}

void Vector2D::operator-=(const Vector2D& v)
{
    this->x -= v.x;
    this->y -= v.y;
}

void Vector2D::operator*=(float value)
{
    this->x *= value;
    this->y *= value;
}

void Vector2D::operator/=(float value)
{
    if(value != 0.0f)
    {
        this->x /= value;
        this->y /= value;
    }
}

bool Vector2D::operator==(const Vector2D & v)
{
    return this->x == v.x && this->y == v.y;
}

bool Vector2D::operator!=(const Vector2D & v)
{
    return !this->operator==(v);
}


float Vector2D::getX() const
{
    return this->x;
}

float Vector2D::getY() const
{
    return this->y;
}

void Vector2D::setY(float y)
{
    this->y = y;
}

void Vector2D::setX(float x)
{
    this->x = x;
}

