#pragma once
#include <memory>
#include <vector>
#include "Arm.h"

class InverseKinematicSystem
{
public:
    InverseKinematicSystem(Vector2D position);
    void addArm(float length);

    void update();

    void rotateArm(int index, float angle);

    std::vector<std::shared_ptr<Arm>> getArms();
    void drag(Vector2D position);
private:

    Vector2D position;
    std::vector<std::shared_ptr<Arm>> arms;  
    std::shared_ptr<Arm> lastArm;
    bool lastArmNotMoving;
};

