#include "Particle.h"

Particle::Particle(float x, float y, float speed, float angle, float radius)
{
    position.setX(x);
    position.setY(y);
    velocity.setLenght(speed);
    velocity.setAngle(angle);
    this->radius = radius;
}

void Particle::update(float deltaTime)
{
    this->position += (this->velocity * deltaTime);
}

Vector2D Particle::collision(const Particle& point)
{
    auto distance = this->position - point.position;
    if (distance.getLength() <= (this->radius + point.radius))
    {
        return distance;
    }
    return Vector2D();
}
