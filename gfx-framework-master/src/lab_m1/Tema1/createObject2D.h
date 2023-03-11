#pragma once

#include <string>

#include "core/gpu/mesh.h"
#include "utils/glm_utils.h"


namespace createObject2D
{
    glm::vec3 CalculateCoordinates(int basic_angle, int& current_angle, float radius, float z);

    // Create square with given bottom left corner, length and color
    Mesh* CreateSquare(const std::string &name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill = false);
    Mesh* CreateRectangle(const std::string& name, float height, float width, float z, glm::vec3 color, bool fill);
    Mesh* CreateTriangle(const std::string& name, float height, float base_part1, float base_part2, glm::vec3 color, bool fill = true);
    Mesh* CreateCircle(const std::string& name, float radius, float z, glm::vec3 color, bool fill);
    Mesh* CreateCloud(const std::string& name, float z, bool fill = true);
    Mesh* CreateDuck(const std::string& name, bool fill = true);
    Mesh* CreateFlyingDuck(const std::string& name, bool fill = true);
    Mesh* CreateWing(const std::string& name, bool fill = true);
}
