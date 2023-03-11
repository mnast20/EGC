#pragma once

#include <string>

#include <vector>
#include <iostream>

#include "core/gpu/mesh.h"
#include "utils/glm_utils.h"


namespace createObject
{
    glm::vec3 CalculateCoordinates(int basic_angle, int& current_angle, float radius);
    glm::vec3 CalculateInnerOuterCoordinates(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3, int above, float distance);

    // Create square with given bottom left corner, length and color
    Mesh* CreateTree(const std::string& name, float height_trunk, float width_trunk, float length_trunk,
                    float height_parallelipiped, float width_parallelipiped, float length_parallelipiped,
                    float height_base, float width_base, float length_base, glm::vec3 color[4], bool fill);
    Mesh* CreateParallelipiped(const std::string& name, float height, float width, float length, glm::vec3 color, bool fill);
    Mesh* CreateSquare(const std::string& name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill);
    Mesh* CreateRectangle(const std::string& name, float height, float width, glm::vec3 center, glm::vec3 color, bool fill);
    Mesh* CreateTriangle(const std::string& name, float height, float base_part1, float base_part2, glm::vec3 color, bool fill);
    Mesh* CreateCircle(const std::string& name, float radius, glm::vec3 color, bool fill);
    Mesh* CreateRaceTrack(const std::string& name, glm::vec3 color, bool fill);
    Mesh* CreateCheckers(const std::string& name, float height, float width, int nr_columns, int nr_lines, glm::vec3 color1, glm::vec3 color2, bool fill);

    std::vector<glm::vec3> getPositions(float distance, std::vector<glm::vec3> positions);
    std::vector<glm::vec3> getMiddlePositions();
    std::vector<glm::vec3> getRaceTrackMargins();
    std::vector<glm::vec3> getTreePositions();
}
