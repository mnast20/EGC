#pragma once

#include "utils/glm_utils.h"
#include "utils/math_utils.h"


namespace implemented
{
    class Car
    {
    public:
        Car()
        {
            position = glm::vec3(0, 2, 5);
            rotationAngle = 0;
        }

        Car(const glm::vec3& position, float rotationAngle)
        {
            this->position = position;
            this->rotationAngle = rotationAngle;
        }

        ~Car()
        { }

    public:
        float rotationAngle;
        glm::vec3 position;
    };
}   // namespace implemented
