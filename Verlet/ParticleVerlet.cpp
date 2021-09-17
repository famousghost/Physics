#include "ParticleVerlet.h"

ParticleVerlet::ParticleVerlet(float x, float y, float xPrev, float yPrev, bool unmovable)
{
    position.setX(x);
    position.setY(y);
    prevPosition.setX(xPrev);
    prevPosition.setY(yPrev);
    this->unmovable = unmovable;
}
