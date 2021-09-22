#include "ForwardKinematicSystem.h"
#include <iostream>

ForwardKinematicSystem::ForwardKinematicSystem(Vector2D position)
    :position(position)
{
    lastArm = nullptr;
}

void ForwardKinematicSystem::addArm(float length)
{
    std::shared_ptr<Arm> arm = std::make_shared<Arm>(position, length, 0.0f);
    if (lastArm)
    {
        arm->setParent(lastArm.get());
    }
    lastArm = arm;
    arms.push_back(arm);
    update();
}

std::vector<std::shared_ptr<Arm>> ForwardKinematicSystem::getArms()
{
    return arms;
}

void ForwardKinematicSystem::update()
{
    for (auto& arm : arms)
    {
        if (auto* parent = arm->getParent())
        {
            arm->setPosition(parent->getEnd());
        }
        else
        {
            arm->setPosition(position);
        }
    }
}

void ForwardKinematicSystem::rotateArm(int index, float angle)
{
    try
    {
        arms.at(index)->setAngle(angle);
    }
    catch (...)
    {
        std::cerr << "Cannot find the arm" << std::endl;
    }
}
