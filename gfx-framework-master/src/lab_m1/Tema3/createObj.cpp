#include "createObj.h"

#include <vector>
#include <iostream>

#include "core/engine.h"
#include "utils/gl_utils.h"

glm::vec3 createObj::CalculateCoordinates(int basic_angle, int& current_angle, float radius) {
    float d_pi = 2 * M_PI;
    float x = radius * cos(current_angle * M_PI / 180);
    float y = radius * sin(current_angle * M_PI / 180);

    current_angle += basic_angle;

    return glm::vec3(x, y, 0);
}

Mesh* createObj::CreateTree(
    const std::string& name,
    float height_trunk,
    float width_trunk,
    float length_trunk,
    float height_parallelipiped,
    float width_parallelipiped,
    float length_parallelipiped,
    float height_base,
    float width_base,
    float length_base,
    glm::vec3 color[4],
    bool fill)
{
    std::vector<VertexFormat> vertices =
    {
            // trunk
            VertexFormat(glm::vec3(-length_trunk / 2, 0, 0), color[0]), // 0
            VertexFormat(glm::vec3(length_trunk / 2, 0, 0), color[0]), // 1
            VertexFormat(glm::vec3(length_trunk / 2, 0, -width_trunk), color[0]), // 2
            VertexFormat(glm::vec3(-length_trunk / 2, 0, -width_trunk), color[0]), // 3
            VertexFormat(glm::vec3(-length_trunk / 2, height_trunk, 0), color[0]), // 4
            VertexFormat(glm::vec3(length_trunk / 2, height_trunk, 0), color[0]), // 5
            VertexFormat(glm::vec3(length_trunk / 2, height_trunk, -width_trunk), color[0]), // 6
            VertexFormat(glm::vec3(-length_trunk / 2, height_trunk, -width_trunk), color[0]), // 7

           // parallelipiped
           VertexFormat(glm::vec3(-length_parallelipiped / 2, height_trunk + height_base, width_parallelipiped / 2 - width_trunk / 2), color[1]), // 8
           VertexFormat(glm::vec3(length_parallelipiped / 2, height_trunk + height_base, width_parallelipiped / 2 - width_trunk / 2), color[1]), // 9
           VertexFormat(glm::vec3(length_parallelipiped / 2, height_trunk + height_base, -width_parallelipiped / 2 - width_trunk / 2), color[1]), // 10
           VertexFormat(glm::vec3(-length_parallelipiped / 2, height_trunk + height_base, -width_parallelipiped / 2 - width_trunk / 2), color[1]), // 11
           VertexFormat(glm::vec3(-length_parallelipiped / 2, height_trunk + height_parallelipiped + height_base, width_parallelipiped / 2 - width_trunk / 2), color[1]), // 12
           VertexFormat(glm::vec3(length_parallelipiped / 2, height_trunk + height_parallelipiped + height_base, width_parallelipiped / 2 - width_trunk / 2), color[1]), // 13
           VertexFormat(glm::vec3(length_parallelipiped / 2, height_trunk + height_parallelipiped + height_base, -width_parallelipiped / 2 - width_trunk / 2), color[1]), // 14
           VertexFormat(glm::vec3(-length_parallelipiped / 2, height_trunk + height_parallelipiped + height_base, -width_parallelipiped / 2 - width_trunk / 2), color[1]), // 15
    
           // base
            VertexFormat(glm::vec3(-length_base / 2, height_trunk, width_base / 2 - width_trunk / 2), color[2]), // 16
            VertexFormat(glm::vec3(length_base / 2, height_trunk, width_base / 2 - width_trunk / 2), color[2]), // 17
            VertexFormat(glm::vec3(length_base / 2, height_trunk, -width_base / 2 - width_trunk / 2), color[2]), // 18
            VertexFormat(glm::vec3(-length_base / 2, height_trunk, -width_base / 2 - width_trunk / 2), color[2]), // 19

           VertexFormat(glm::vec3(-length_parallelipiped / 2, height_trunk + height_base, width_parallelipiped / 2 - width_trunk / 2), color[2]), // 20
           VertexFormat(glm::vec3(length_parallelipiped / 2, height_trunk + height_base, width_parallelipiped / 2 - width_trunk / 2), color[2]), // 21
           VertexFormat(glm::vec3(length_parallelipiped / 2, height_trunk + height_base, -width_parallelipiped / 2 - width_trunk / 2), color[2]), // 22
           VertexFormat(glm::vec3(-length_parallelipiped / 2, height_trunk + height_base, -width_parallelipiped / 2 - width_trunk / 2), color[2]), // 23
    
            // ceiling
           VertexFormat(glm::vec3(-length_base / 2, height_trunk + height_parallelipiped + height_base * 2, width_base / 2 - width_trunk / 2), color[3]), // 24
            VertexFormat(glm::vec3(length_base / 2, height_trunk + height_parallelipiped + height_base * 2, width_base / 2 - width_trunk / 2), color[3]), // 25
            VertexFormat(glm::vec3(length_base / 2, height_trunk + height_parallelipiped + height_base * 2, -width_base / 2 - width_trunk / 2), color[3]), // 26
            VertexFormat(glm::vec3(-length_base / 2, height_trunk + height_parallelipiped + height_base * 2, -width_base / 2 - width_trunk / 2), color[3]), // 27

            VertexFormat(glm::vec3(-length_parallelipiped / 2, height_trunk + height_parallelipiped + height_base, width_parallelipiped / 2 - width_trunk / 2), color[3]), // 28
           VertexFormat(glm::vec3(length_parallelipiped / 2, height_trunk + height_parallelipiped + height_base, width_parallelipiped / 2 - width_trunk / 2), color[3]), // 29
           VertexFormat(glm::vec3(length_parallelipiped / 2, height_trunk + height_parallelipiped + height_base, -width_parallelipiped / 2 - width_trunk / 2), color[3]), // 30
           VertexFormat(glm::vec3(-length_parallelipiped / 2, height_trunk + height_parallelipiped + height_base, -width_parallelipiped / 2 - width_trunk / 2), color[3]), // 31

    };

    Mesh* tree = new Mesh(name);
    std::vector<unsigned int> indices = { 
                                         // trunk
                                          3, 1, 0,
                                          3, 2, 1,
                                          5, 2, 1,
                                          5, 6, 2,
                                          4, 3, 7,
                                          4, 0, 3,
                                          7, 5, 4,
                                          7, 6, 5,
                                          4, 5, 1,
                                          4, 1, 0,
                                          7, 2, 6,
                                          7, 3, 2,

                                          // foliage
                                          11, 9, 8,
                                          11, 10, 9,
                                          13, 10, 9,
                                          13, 14, 10,
                                          12, 11, 15,
                                          12, 8, 11,
                                          15, 13, 12,
                                          15, 14, 13,
                                          12, 13, 9,
                                          12, 9, 8,
                                          15, 10, 14,
                                          15, 11, 10,

                                          // base
                                          19, 17, 16,
                                          19, 18, 17,
                                          21, 18, 17,
                                          21, 22, 18,
                                          20, 19, 23,
                                          20, 16, 19,
                                          20, 21, 17,
                                          20, 17, 16,
                                          23, 18, 22, 
                                          23, 19, 18,

                                          // ceiling
                                          27, 25, 24,
                                          27, 26, 25,
                                          25, 30, 29,
                                          25, 26, 30,
                                          24, 31, 27,
                                          24, 28, 31,
                                          24, 25, 29,
                                          24, 29, 28,
                                          27, 30, 26,
                                          27, 31, 30
    };

    if (!fill) {
        tree->SetDrawMode(GL_LINE_LOOP);
    }
    else {
        // Draw 2 triangles. Add the remaining 2 indices
        indices.push_back(0);
        indices.push_back(2);
    }

    tree->InitFromData(vertices, indices);
    return tree;
}

Mesh* createObj::CreateParallelipiped(
    const std::string& name,
    float height,
    float width,
    float length,
    glm::vec3 color,
    bool fill)
{
    Mesh* parallelipiped = new Mesh(name);

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(glm::vec3(-length / 2, 0, width / 2), color), // 0
        VertexFormat(glm::vec3(length / 2, 0, width / 2), color), // 1
        VertexFormat(glm::vec3(length / 2, 0, -width / 2), color), // 2
        VertexFormat(glm::vec3(-length / 2, 0, -width / 2), color), // 3
        VertexFormat(glm::vec3(-length / 2, height, width / 2), color), // 4
        VertexFormat(glm::vec3(length / 2, height, width / 2), color), // 5
        VertexFormat(glm::vec3(length / 2, height, -width / 2), color), // 6
        VertexFormat(glm::vec3(-length / 2, height, -width / 2), color) // 7
    };

    std::vector<unsigned int> indices = { 3, 1, 0,
                                            3, 2, 1,
                                            5, 2, 1,
                                            5, 6, 2,
                                            4, 3, 7,
                                            4, 0, 3,
                                            7, 5, 4,
                                            7, 6, 5,
                                            4, 5, 1,
                                            4, 1, 0,
                                            7, 2, 6,
                                            7, 3, 2
    };

        if (!fill) {
            parallelipiped->SetDrawMode(GL_LINE_LOOP);
        }
        else {
            // Draw 2 triangles. Add the remaining 2 indices
            indices.push_back(0);
            indices.push_back(2);
        }

        parallelipiped->InitFromData(vertices, indices);
    
    return parallelipiped;
}

Mesh* createObj::CreateSquare(
    const std::string& name,
    float length,
    glm::vec3 color,
    bool fill,
    bool texture)
{
    glm::vec3 corner = glm::vec3(0, 0, 0);

    float small_side = length / 2;

    Mesh* square = new Mesh(name);

    if (!texture) {
        std::vector<VertexFormat> vertices = {
            VertexFormat(glm::vec3(-small_side, -small_side, 0), color), // 0
            VertexFormat(glm::vec3(-small_side, small_side, 0), color), // 1
            VertexFormat(glm::vec3(small_side, small_side, 0), color), // 2
            VertexFormat(glm::vec3(small_side, -small_side, 0), color), // 3
        };

        std::vector<unsigned int> indices = { 0, 1, 2,
                                              2, 3, 0 };

        if (!fill) {
            square->SetDrawMode(GL_LINE_LOOP);
        }
        else {
            // Draw 2 triangles. Add the remaining 2 indices
            indices.push_back(0);
            indices.push_back(2);
        }

        square->InitFromData(vertices, indices);
    }
    else {
        std::vector<glm::vec3> vertices = {
            glm::vec3(-small_side, -small_side, 0), // 0
            glm::vec3(-small_side, small_side, 0), // 1
            glm::vec3(small_side, small_side, 0), // 2
            glm::vec3(small_side, -small_side, 0), // 3
        };

        std::vector<unsigned int> indices = { 0, 1, 2,
                                              2, 3, 0 };

        std::vector<glm::vec3> normals
        {
            glm::vec3(0, 0, 1),
            glm::vec3(0, 0, 1),
            glm::vec3(0, 0, 1),
            glm::vec3(0, 0, 1)
        };

        std::vector<glm::vec2> textureCoords
        {
            // TODO(student): Complete texture coordinates for the square
            glm::vec2(0.0f, 0.0f), // 0
            glm::vec2(0.0f, 1.0f), // 1
            glm::vec2(1.0f, 1.0f), // 2
            glm::vec2(1.0f, 0.0f) // 3
        };

        if (!fill) {
            square->SetDrawMode(GL_LINE_LOOP);
        }
        else {
            // Draw 2 triangles. Add the remaining 2 indices
            indices.push_back(0);
            indices.push_back(2);
        }

        square->InitFromData(vertices, normals, textureCoords, indices);
    }

    return square;
}

Mesh* createObj::CreateRectangle(
    const std::string& name,
    float height,
    float width,
    glm::vec3 center,
    glm::vec3 color,
    bool fill)
{

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(center + glm::vec3(-width / 2, -height / 2, 0), color), // 0
        VertexFormat(center + glm::vec3(-width / 2, height / 2, 0), color), // 1
        VertexFormat(center + glm::vec3(width / 2, height / 2, 0), color), // 2
        VertexFormat(center + glm::vec3(width / 2, -height / 2, 0), color) // 3
    };

    Mesh* rectangle = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 2, 3};

    if (!fill) {
        rectangle->SetDrawMode(GL_LINE_LOOP);
    }
    else {
        // Draw 2 triangles. Add the remaining 2 indices
        indices.push_back(0);
        indices.push_back(2);
    }

    rectangle->InitFromData(vertices, indices);
    return rectangle;
}

Mesh* createObj::CreateCheckers(
    const std::string& name,
    float height,
    float width,
    int nr_columns,
    int nr_lines,
    glm::vec3 color1,
    glm::vec3 color2,
    bool fill)
{
    glm::vec3 corner = glm::vec3(0, 0, 0);

    float small_side = height / nr_lines;
    int nr_indices_small_square = 6;
    int current_index = 0;

    std::vector<unsigned int> indices;
    std::vector<VertexFormat> vertices;

    float initial_x = corner.x;

    // glm::vec3 prev_color = color1;
    glm::vec3 current_color = color1;
    glm::vec3 start_color = color1;

    for (int i = 0; i < nr_lines; i++) {
        for (int j = 0; j < nr_columns; j++) {
            vertices.push_back(VertexFormat(corner, current_color));
            vertices.push_back(VertexFormat(corner + glm::vec3(small_side, 0, 0), current_color));
            vertices.push_back(VertexFormat(corner + glm::vec3(small_side, small_side, 0), current_color));
            vertices.push_back(VertexFormat(corner + glm::vec3(0, small_side, 0), current_color));

            indices.push_back(current_index);
            indices.push_back(current_index + 1);
            indices.push_back(current_index + 2);

            indices.push_back(current_index);
            indices.push_back(current_index + 2);
            indices.push_back(current_index + 3);

            corner.x += small_side;
            current_index += 4;

            if (current_color == color1) {
                current_color = color2;
            }
            else {
                current_color = color1;
            }
        }

        corner.x = initial_x;
        corner.y += small_side;

        if (start_color == color1) {
            start_color = color2;
            current_color = color2;
        }
        else {
            start_color = color1;
            current_color = color1;
        }
    }

    Mesh* rectangle = new Mesh(name);

    if (!fill) {
        rectangle->SetDrawMode(GL_LINE_LOOP);
    }
    else {
        // Draw 2 triangles. Add the remaining 2 indices
        indices.push_back(0);
        indices.push_back(2);
    }

    rectangle->InitFromData(vertices, indices);
    return rectangle;
}

Mesh* createObj::CreateTriangle(
    const std::string& name,
    float height,
    float base_part1,
    float base_part2,
    glm::vec3 color,
    bool fill)
{

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(glm::vec3(0, height, 0), color),
        VertexFormat(glm::vec3(base_part1 , 0, 0), color),
        VertexFormat(glm::vec3(base_part2, 0, 0), color)

    };

    std::vector<unsigned int> indices =
    {
        1, 2, 0
    };

    Mesh* triangle = new Mesh(name);

    if (!fill) {
        triangle->SetDrawMode(GL_LINE_LOOP);
    }
    else {
        // Draw 2 triangles. Add the remaining 2 indices
        indices.push_back(0);
        indices.push_back(2);
    }

    triangle->InitFromData(vertices, indices);
    return triangle;
}

Mesh* createObj::CreateCircle(
    const std::string& name,
    float radius,
    glm::vec3 color,
    bool fill)
{

    int angle = 10;
    int current_angle = 0;

    std::vector<VertexFormat> vertices
    {
        VertexFormat(glm::vec3(0, 0, 0), color), // 0
        VertexFormat(CalculateCoordinates(angle, current_angle, radius), color), // 1
        VertexFormat(CalculateCoordinates(angle, current_angle, radius), color), // 2
        VertexFormat(CalculateCoordinates(angle, current_angle, radius), color), // 3
        VertexFormat(CalculateCoordinates(angle, current_angle, radius), color), // 4
        VertexFormat(CalculateCoordinates(angle, current_angle, radius), color), // 5
        VertexFormat(CalculateCoordinates(angle, current_angle, radius), color), // 6
        VertexFormat(CalculateCoordinates(angle, current_angle, radius), color), // 7
        VertexFormat(CalculateCoordinates(angle, current_angle, radius), color), // 8
        VertexFormat(CalculateCoordinates(angle, current_angle, radius), color), // 9
        VertexFormat(CalculateCoordinates(angle, current_angle, radius), color), // 10
        VertexFormat(CalculateCoordinates(angle, current_angle, radius), color), // 11
        VertexFormat(CalculateCoordinates(angle, current_angle, radius), color), // 12
        VertexFormat(CalculateCoordinates(angle, current_angle, radius), color), // 13
        VertexFormat(CalculateCoordinates(angle, current_angle, radius), color), // 14
        VertexFormat(CalculateCoordinates(angle, current_angle, radius), color), // 15
        VertexFormat(CalculateCoordinates(angle, current_angle, radius), color), // 16
        VertexFormat(CalculateCoordinates(angle, current_angle, radius), color), // 17
        VertexFormat(CalculateCoordinates(angle, current_angle, radius), color), // 18
        VertexFormat(CalculateCoordinates(angle, current_angle, radius), color), // 19
        VertexFormat(CalculateCoordinates(angle, current_angle, radius), color), // 20
        VertexFormat(CalculateCoordinates(angle, current_angle, radius), color), // 21
        VertexFormat(CalculateCoordinates(angle, current_angle, radius), color), // 22
        VertexFormat(CalculateCoordinates(angle, current_angle, radius), color), // 23
        VertexFormat(CalculateCoordinates(angle, current_angle, radius), color), // 24
        VertexFormat(CalculateCoordinates(angle, current_angle, radius), color), // 25
        VertexFormat(CalculateCoordinates(angle, current_angle, radius), color), // 26
        VertexFormat(CalculateCoordinates(angle, current_angle, radius), color), // 27
        VertexFormat(CalculateCoordinates(angle, current_angle, radius), color), // 28
        VertexFormat(CalculateCoordinates(angle, current_angle, radius), color), // 29
        VertexFormat(CalculateCoordinates(angle, current_angle, radius), color), // 30
        VertexFormat(CalculateCoordinates(angle, current_angle, radius), color), // 31
        VertexFormat(CalculateCoordinates(angle, current_angle, radius), color), // 32
        VertexFormat(CalculateCoordinates(angle, current_angle, radius), color), // 33
        VertexFormat(CalculateCoordinates(angle, current_angle, radius), color), // 34
        VertexFormat(CalculateCoordinates(angle, current_angle, radius), color), // 35
        VertexFormat(CalculateCoordinates(angle, current_angle, radius), color), // 36
    };

    std::vector<unsigned int> indices =
    {
        1, 2, 0,
        2, 3, 0,
        3, 4, 0,
        4, 5, 0,
        5, 6, 0,
        6, 7, 0,
        7, 8, 0,
        8, 9, 0,
        9, 10, 0,
        10, 11, 0,
        11, 12, 0,
        12, 13, 0,
        13, 14, 0,
        14, 15, 0,
        15, 16, 0,
        16, 17, 0,
        17, 18, 0,
        18, 19, 0,
        19, 20, 0,
        20, 21, 0,
        21, 22, 0,
        22, 23, 0,
        23, 24, 0,
        24, 25, 0,
        25, 26, 0,
        26, 27, 0,
        27, 28, 0,
        28, 29, 0,
        29, 30, 0,
        30, 31, 0,
        31, 32, 0,
        32, 33, 0,
        33, 34, 0,
        34, 35, 0,
        35, 36, 0,
        36, 1, 0
    };

    Mesh* circle = new Mesh(name);

    if (!fill) {
        circle->SetDrawMode(GL_LINE_LOOP);
    }
    else {
        // Draw 2 triangles. Add the remaining 2 indices
        indices.push_back(0);
        indices.push_back(2);
    }

    circle->InitFromData(vertices, indices);
    return circle;
}
