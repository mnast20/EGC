#pragma once

#include "utils/glm_utils.h"

#include <vector>


namespace transforms3D
{
    // Translate matrix
    inline glm::mat4 Translate(float translateX, float translateY, float translateZ)
    {
        return glm::mat4(1, 0, 0, 0,
            0, 1, 0, 0,
            0, 0, 1, 0,
            translateX, translateY, translateZ, 1);
    }

    // Scale matrix
    inline glm::mat4 Scale(float scaleX, float scaleY, float scaleZ)
    {
        return glm::mat4(scaleX, 0, 0, 0,
            0, scaleY, 0, 0,
            0, 0, scaleZ, 0,
            0, 0, 0, 1);

    }

    // Rotate matrix relative to the OZ axis
    inline glm::mat4 RotateOZ(float radians)
    {
        return glm::mat4(cos(radians), sin(radians), 0, 0,
            (-1) * sin(radians), cos(radians), 0, 0,
            0, 0, 1, 0,
            0, 0, 0, 1);

    }

    // Rotate matrix relative to the OY axis
    inline glm::mat4 RotateOY(float radians)
    {
        return glm::mat4(cos(radians), 0, (-1) * sin(radians), 0,
            0, 1, 0, 0,
            sin(radians), 0, cos(radians), 0,
            0, 0, 0, 1);

    }

    // Rotate matrix relative to the OX axis
    inline glm::mat4 RotateOX(float radians)
    {
        return glm::mat4(1, 0, 0, 0,
            0, cos(radians), sin(radians), 0,
            0, (-1) * sin(radians), cos(radians), 0,
            0, 0, 0, 1);

    }

    // Scale matrix
    inline glm::vec3 ScaleVector(float scaleX, float scaleY, float scaleZ, glm::vec3 vect)
    {
        return glm::vec3(vect.x * scaleX, vect.y * scaleY, vect.z * scaleZ);

    }

    inline std::vector<glm::vec3> ScaleVectorArray(float scaleX, float scaleY, float scaleZ, std::vector<glm::vec3> vector_array)
    {
        for (int i = 0; i < vector_array.size(); i++) {
            vector_array[i] = ScaleVector(scaleX, scaleY, scaleZ, vector_array[i]);
        }

        return vector_array;

    }
}   // namespace transform3D
