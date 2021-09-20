#include "ParticleVerlet.h"

ParticleVerlet::ParticleVerlet(float x, float y, float xPrev, float yPrev, float radius, bool unmovable)
{
    position.setX(x);
    position.setY(y);
    prevPosition.setX(xPrev);
    prevPosition.setY(yPrev);
    this->unmovable = unmovable;
    this->radius = radius;
}

Vector2D ParticleVerlet::collision(const ParticleVerlet& point)
{
    if (this->position == point.position)
    {
        return Vector2D();
    }
    auto distance = this->position - point.position;
    if (distance.getLength() <= (this->radius + point.radius))
    {
        return distance;
    }
    return Vector2D();
}
