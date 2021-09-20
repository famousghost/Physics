#pragma once
class Vector2D
{
public:
    Vector2D();
    Vector2D(float x, float y);

    float getLength();

    float getAngle();

    void setLenght(float length);

    void setAngle(float angle);

    Vector2D operator+(const Vector2D& v);

    Vector2D operator-(const Vector2D & v);

    Vector2D operator*(float value);

    Vector2D operator/(float value);

    void operator+=(const Vector2D & v);

    void operator-=(const Vector2D & v);

    void operator*=(float value);

    void operator/=(float value);

    bool operator==(const Vector2D& v);

    bool operator!=(const Vector2D & v);

    float getX() const;

    float getY() const;

    void setY(float y);

    void setX(float x);

private:
    float x;
    float y;
};

