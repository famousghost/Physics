#pragma once
#include <memory>
#include <vector>
#include "Arm.h"

class ForwardKinematicSystem
{
public:
    ForwardKinematicSystem(Vector2D position);

    void addArm(float length);

    void update();

    void rotateArm(int index, float angle);

    std::vector<std::shared_ptr<Arm>> getArms();
private:

    Vector2D position;
    std::vector<std::shared_ptr<Arm>> arms;  
    std::shared_ptr<Arm> lastArm;
};

