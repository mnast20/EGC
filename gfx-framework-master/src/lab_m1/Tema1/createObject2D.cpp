#include "createObject2D.h"

#include <vector>

#include "core/engine.h"
#include "utils/gl_utils.h"

glm::vec3 createObject2D::CalculateCoordinates(int basic_angle, int& current_angle, float radius, float z) {
    float d_pi = 2 * M_PI;
    float x = radius * cos(current_angle * M_PI / 180);
    float y = radius * sin(current_angle * M_PI / 180);

    // float x = r * 0.86f;
    // float y = r * 0.5f;

    current_angle += basic_angle;

    return glm::vec3(x, y, z);
}

Mesh* createObject2D::CreateSquare(
    const std::string &name,
    glm::vec3 leftBottomCorner,
    float length,
    glm::vec3 color,
    bool fill)
{
    glm::vec3 corner = leftBottomCorner;

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(corner, color),
        VertexFormat(corner + glm::vec3(length, 0, 0), color),
        VertexFormat(corner + glm::vec3(length, length, 0), color),
        VertexFormat(corner + glm::vec3(0, length, 0), color)
    };

    Mesh* square = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 2, 3 };

    if (!fill) {
        square->SetDrawMode(GL_LINE_LOOP);
    } else {
        // Draw 2 triangles. Add the remaining 2 indices
        indices.push_back(0);
        indices.push_back(2);
    }

    square->InitFromData(vertices, indices);
    return square;
}

Mesh* createObject2D::CreateRectangle(
    const std::string& name,
    float height,
    float width,
    float z,
    glm::vec3 color,
    bool fill)
{

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(glm::vec3(0, 0, z), color),
        VertexFormat(glm::vec3(0, height, z), color),
        VertexFormat(glm::vec3(width, height, 0), color),
        VertexFormat(glm::vec3(width, 0, z), color)
    };

    Mesh* rectangle = new Mesh(name);
    std::vector<unsigned int> indices = {0, 1, 2, 3};

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

Mesh* createObject2D::CreateTriangle(
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

Mesh* createObject2D::CreateCircle(
    const std::string& name,
    float radius,
    float z,
    glm::vec3 color,
    bool fill)
{

    int angle = 10;
    int current_angle = 0;

    std::vector<VertexFormat> vertices
    {
        VertexFormat(glm::vec3(0, 0, z), color), // 0
        VertexFormat(CalculateCoordinates(angle, current_angle, radius, z), color), // 1
        VertexFormat(CalculateCoordinates(angle, current_angle, radius, z), color), // 2
        VertexFormat(CalculateCoordinates(angle, current_angle, radius, z), color), // 3
        VertexFormat(CalculateCoordinates(angle, current_angle, radius, z), color), // 4
        VertexFormat(CalculateCoordinates(angle, current_angle, radius, z), color), // 5
        VertexFormat(CalculateCoordinates(angle, current_angle, radius, z), color), // 6
        VertexFormat(CalculateCoordinates(angle, current_angle, radius, z), color), // 7
        VertexFormat(CalculateCoordinates(angle, current_angle, radius, z), color), // 8
        VertexFormat(CalculateCoordinates(angle, current_angle, radius, z), color), // 9
        VertexFormat(CalculateCoordinates(angle, current_angle, radius, z), color), // 10
        VertexFormat(CalculateCoordinates(angle, current_angle, radius, z), color), // 11
        VertexFormat(CalculateCoordinates(angle, current_angle, radius, z), color), // 12
        VertexFormat(CalculateCoordinates(angle, current_angle, radius, z), color), // 13
        VertexFormat(CalculateCoordinates(angle, current_angle, radius, z), color), // 14
        VertexFormat(CalculateCoordinates(angle, current_angle, radius, z), color), // 15
        VertexFormat(CalculateCoordinates(angle, current_angle, radius, z), color), // 16
        VertexFormat(CalculateCoordinates(angle, current_angle, radius, z), color), // 17
        VertexFormat(CalculateCoordinates(angle, current_angle, radius, z), color), // 18
        VertexFormat(CalculateCoordinates(angle, current_angle, radius, z), color), // 19
        VertexFormat(CalculateCoordinates(angle, current_angle, radius, z), color), // 20
        VertexFormat(CalculateCoordinates(angle, current_angle, radius, z), color), // 21
        VertexFormat(CalculateCoordinates(angle, current_angle, radius, z), color), // 22
        VertexFormat(CalculateCoordinates(angle, current_angle, radius, z), color), // 23
        VertexFormat(CalculateCoordinates(angle, current_angle, radius, z), color), // 24
        VertexFormat(CalculateCoordinates(angle, current_angle, radius, z), color), // 25
        VertexFormat(CalculateCoordinates(angle, current_angle, radius, z), color), // 26
        VertexFormat(CalculateCoordinates(angle, current_angle, radius, z), color), // 27
        VertexFormat(CalculateCoordinates(angle, current_angle, radius, z), color), // 28
        VertexFormat(CalculateCoordinates(angle, current_angle, radius, z), color), // 29
        VertexFormat(CalculateCoordinates(angle, current_angle, radius, z), color), // 30
        VertexFormat(CalculateCoordinates(angle, current_angle, radius, z), color), // 31
        VertexFormat(CalculateCoordinates(angle, current_angle, radius, z), color), // 32
        VertexFormat(CalculateCoordinates(angle, current_angle, radius, z), color), // 33
        VertexFormat(CalculateCoordinates(angle, current_angle, radius, z), color), // 34
        VertexFormat(CalculateCoordinates(angle, current_angle, radius, z), color), // 35
        VertexFormat(CalculateCoordinates(angle, current_angle, radius, z), color), // 36
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

Mesh* createObject2D::CreateCloud(const std::string& name, float z, bool fill) {
    std::vector<VertexFormat> vertices
    {
        VertexFormat(glm::vec3(1, 2.8f, z), glm::vec3(1, 1, 1)), // 0
        VertexFormat(glm::vec3(-0.5f, 2.18f, z), glm::vec3(1, 1, 1)), // 1
        VertexFormat(glm::vec3(2.3f, 2.42f, z), glm::vec3(1, 1, 1)), // 2
        VertexFormat(glm::vec3(3.18f, 1.73f, z), glm::vec3(1, 1, 1)), // 3
        VertexFormat(glm::vec3(3.49f, 0.48f, z), glm::vec3(1, 1, 1)), // 4
        VertexFormat(glm::vec3(4.23f, -0.21f, z), glm::vec3(1, 1, 1)), // 5
        VertexFormat(glm::vec3(4.67f, -1.12f, z), glm::vec3(1, 1, 1)), // 6
        VertexFormat(glm::vec3(4.2f, -2.21f, z), glm::vec3(1, 1, 1)), // 7
        VertexFormat(glm::vec3(3.68f, -2.65f, z), glm::vec3(1, 1, 1)), // 8
        VertexFormat(glm::vec3(2.73f, -2.73f, z), glm::vec3(1, 1, 1)), // 9
        VertexFormat(glm::vec3(0.59f, -2.78f, z), glm::vec3(1, 1, 1)), // 10
        VertexFormat(glm::vec3(-1.43f, -2.78f, z), glm::vec3(1, 1, 1)), // 11
        VertexFormat(glm::vec3(-3.359f, -2.73f, z), glm::vec3(1, 1, 1)), // 12
        VertexFormat(glm::vec3(-4.45f, -2, z), glm::vec3(1, 1, 1)), // 13
        VertexFormat(glm::vec3(-4.61f, -1, z), glm::vec3(1, 1, 1)), // 14
        VertexFormat(glm::vec3(-4.39f, -0.165f, z), glm::vec3(1, 1, 1)), // 15
        VertexFormat(glm::vec3(-3.6f, 0.41f, z), glm::vec3(1, 1, 1)), // 16
        VertexFormat(glm::vec3(-2.75f, 0.53f, z), glm::vec3(1, 1, 1)), // 17
        VertexFormat(glm::vec3(-2.14f, 1.4f, z), glm::vec3(1, 1, 1)), // 18
        VertexFormat(glm::vec3(-0.71f, 1.68f, z), glm::vec3(1, 1, 1)), // 19
        VertexFormat(glm::vec3(-1.25f, 0.165f, z), glm::vec3(1, 1, 1)), // 20
        VertexFormat(glm::vec3(0.59f, 0.29f, z), glm::vec3(1, 1, 1)), // 21
        VertexFormat(glm::vec3(1.78f, -1.35f, z), glm::vec3(1, 1, 1)), // 22
        VertexFormat(glm::vec3(-0.47f, -1.36f, z), glm::vec3(1, 1, 1)), // 23
        VertexFormat(glm::vec3(-2.26f, -1.35f, z), glm::vec3(1, 1, 1)) // 24
    };  

    std::vector<unsigned int> indices = {
        0, 1, 2,
        2, 3, 4,
        5, 6, 7,
        7, 8, 9,
        12, 13, 14,
        14, 15, 16,
        17, 18, 19,
        1, 20, 21,
        1, 21, 2,
        2, 21, 4,
        21, 22, 4, 
        4, 22, 5,
        5, 22, 7,
        22, 9, 7,
        22, 10, 9,
        23, 22, 10,
        21, 22, 23,
        20, 21, 23,
        20, 24, 23,
        17, 19, 20,
        17, 20, 24,
        16, 17, 24,
        16, 14, 24,
        14, 12, 24,
        24, 11, 23,
        23, 11, 10,
        24, 11, 12,
        1, 20, 19
    };

    Mesh* cloud = new Mesh(name);

    if (!fill) {
        cloud->SetDrawMode(GL_LINE_LOOP);
    }
    else {
        // Draw 2 triangles. Add the remaining 2 indices
        indices.push_back(0);
        indices.push_back(2);
    }

    cloud->InitFromData(vertices, indices);
    return cloud;
}

Mesh* createObject2D::CreateWing(const std::string& name, bool fill) {
    std::vector<VertexFormat> vertices
    {
        VertexFormat(glm::vec3(-0.44f, 0.25f, 0), glm::vec3(238.0f, 218.0f, 219.0f) / 255.0f), // 0
        VertexFormat(glm::vec3(-0.44f, 0.25f, 0), glm::vec3(244.0f, 224.0f, 225.0f) / 255.0f), // 1

        VertexFormat(glm::vec3(-1.2f, -0.69f, 0), glm::vec3(238.0f, 218.0f, 219.0f) / 255.0f), // 2
        VertexFormat(glm::vec3(-1.2f, -0.69f, 0), glm::vec3(154.0f, 132.0f, 134.0f) / 255.0f), // 3

        VertexFormat(glm::vec3(0.6f, -1.23f, 0), glm::vec3(154.0f, 132.0f, 134.0f) / 255.0f), // 4
        VertexFormat(glm::vec3(0.6f, -1.23f, 0), glm::vec3(231.0f, 211.0f, 212.0f) / 255.0f), // 5
        VertexFormat(glm::vec3(0.6f, -1.23f, 0), glm::vec3(231.0f, 211.0f, 212.0f) / 255.0f), // 6

        VertexFormat(glm::vec3(1.1f, -1.4f, 0), glm::vec3(238.0f, 218.0f, 219.0f) / 255.0f), // 7
        VertexFormat(glm::vec3(1.1f, -1.4f, 0), glm::vec3(244.0f, 224.0f, 225.0f) / 255.0f), // 8
        VertexFormat(glm::vec3(1.1f, -1.4f, 0), glm::vec3(244.0f, 224.0f, 225.0f) / 255.0f), // 9
        VertexFormat(glm::vec3(1.1f, -1.4f, 0), glm::vec3(171.0f, 148.0f, 142.0f) / 255.0f), // 10
        VertexFormat(glm::vec3(1.1f, -1.4f, 0), glm::vec3(39.0f, 20.0f, 14.0f) / 255.0f), // 11
        VertexFormat(glm::vec3(1.1f, -1.4f, 0), glm::vec3(31.0f, 27.0f, 77.0f) / 255.0f), // 12
        VertexFormat(glm::vec3(1.1f, -1.4f, 0), glm::vec3(231.0f, 211.0f, 212.0f) / 255.0f), // 13
        VertexFormat(glm::vec3(1.1f, -1.4f, 0), glm::vec3(231.0f, 211.0f, 212.0f) / 255.0f), // 14

        VertexFormat(glm::vec3(-0.19f, -1.4f, 0), glm::vec3(154.0f, 132.0f, 134.0f) / 255.0f), // 15
        VertexFormat(glm::vec3(-0.19f, -1.4f, 0), glm::vec3(231.0f, 211.0f, 212.0f) / 255.0f), // 16

        VertexFormat(glm::vec3(3.0f, -0.875f, 0), glm::vec3(244.0f, 224.0f, 225.0f) / 255.0f), // 17
        VertexFormat(glm::vec3(3.0f, -0.875f, 0), glm::vec3(200.0f, 181.0f, 177.0f) / 255.0f), // 18
        VertexFormat(glm::vec3(3.0f, -0.875f, 0), glm::vec3(193.0f, 172.0f, 169.0f) / 255.0f), // 19
        VertexFormat(glm::vec3(3.0f, -0.875f, 0), glm::vec3(171.0f, 148.0f, 142.0f) / 255.0f), // 20

        VertexFormat(glm::vec3(0.8f, 0.38f, 0), glm::vec3(244.0f, 224.0f, 225.0f) / 255.0f), // 21
        VertexFormat(glm::vec3(0.8f, 0.38f, 0), glm::vec3(244.0f, 224.0f, 225.0f) / 255.0f), // 22
        VertexFormat(glm::vec3(0.8f, 0.38f, 0), glm::vec3(200.0f, 181.0f, 177.0f) / 255.0f), // 23

        VertexFormat(glm::vec3(4.0f, -0.85f, 0), glm::vec3(200.0f, 181.0f, 177.0f) / 255.0f), // 24
        VertexFormat(glm::vec3(4.0f, -0.85f, 0), glm::vec3(193.0f, 172.0f, 169.0f) / 255.0f), // 25

        VertexFormat(glm::vec3(3.44f, -1.36f, 0), glm::vec3(193.0f, 172.0f, 169.0f) / 255.0f), // 26
        VertexFormat(glm::vec3(3.44f, -1.36f, 0), glm::vec3(171.0f, 148.0f, 142.0f) / 255.0f), // 27
        VertexFormat(glm::vec3(3.44f, -1.36f, 0), glm::vec3(39.0f, 20.0f, 14.0f) / 255.0f), // 28

        VertexFormat(glm::vec3(2.915f, -1.8f, 0), glm::vec3(39.0f, 20.0f, 14.0f) / 255.0f), // 29
        VertexFormat(glm::vec3(2.915f, -1.8f, 0), glm::vec3(31.0f, 27.0f, 77.0f) / 255.0f), // 30
        VertexFormat(glm::vec3(2.915f, -1.8f, 0), glm::vec3(41.0f, 37.0f, 98.0f) / 255.0f), // 31

        VertexFormat(glm::vec3(2.52f, -2.2f, 0), glm::vec3(41.0f, 37.0f, 98.0f) / 255.0f), // 32

        VertexFormat(glm::vec3(0.6f, -1.9f, 0), glm::vec3(31.0f, 27.0f, 77.0f) / 255.0f), // 33
        VertexFormat(glm::vec3(0.6f, -1.9f, 0), glm::vec3(41.0f, 37.0f, 98.0f) / 255.0f), // 34
        VertexFormat(glm::vec3(0.6f, -1.9f, 0), glm::vec3(231.0f, 211.0f, 212.0f) / 255.0f), // 35
    };

    std::vector<unsigned int> indices = {
    2, 0, 7, // glm::vec3(238.0f, 218.0f, 219.0f)
    1, 21, 8, // glm::vec3(244.0f, 224.0f, 225.0f)
    22, 9, 17, // glm::vec3(244.0f, 224.0f, 225.0f)
    23, 18, 24, // glm::vec3(200.0f, 181.0f, 177.0f)
    25, 19, 26, // glm::vec3(193.0f, 172.0f, 169.0f)
    20, 27, 10, // glm::vec3(171.0f, 148.0f, 142.0f)
    28, 29, 11, // glm::vec3(39.0f, 20.0f, 14.0f)
    30, 33, 12, // glm::vec3(31.0f, 27.0f, 77.0f)
    31, 34, 32, // glm::vec3(41.0f, 37.0f, 98.0f)
    3, 15, 4, // glm::vec3(154.0f, 132.0f, 134.0f)
    16, 5, 13, // glm::vec3(231.0f, 211.0f, 212.0f)
    14, 16, 35 // glm::vec3(231.0f, 211.0f, 212.0f)
    };

    Mesh* wing = new Mesh(name);

    if (!fill) {
        wing->SetDrawMode(GL_LINE_LOOP);
    }
    else {
        // Draw 2 triangles. Add the remaining 2 indices
        indices.push_back(0);
        indices.push_back(2);
    }

    wing->InitFromData(vertices, indices);
    return wing;
}

Mesh* createObject2D::CreateDuck(const std::string& name, bool fill) {
    std::vector<VertexFormat> vertices
    {
        VertexFormat(glm::vec3(-2.04f, 1.95f,  -5), glm::vec3(228.0f, 183.0f, 74.0f) / 255.0f), // 0
        VertexFormat(glm::vec3(-2.04f, 1.95f,  -5), glm::vec3(19.0f, 89.0f, 53.0f) / 255.0f), // 1
        VertexFormat(glm::vec3(-2.04f, 1.95f,  -5), glm::vec3(22.0f, 98.0f, 51.0f) / 255.0f), // 2
        VertexFormat(glm::vec3(-3.23f, 1.46f,  -5), glm::vec3(228.0f, 183.0f, 74.0f) / 255.0f), // 3
        VertexFormat(glm::vec3(-3.23f, 1.46f,  -5), glm::vec3(225.0f, 163.0f, 61.0f) / 255.0f), // 4
        VertexFormat(glm::vec3(-3.23f, 1.265f,  -5), glm::vec3(225.0f, 163.0f, 61.0f) / 255.0f), // 5
        VertexFormat(glm::vec3(-1.53f, 1.27f,  -5), glm::vec3(228.0f, 183.0f, 74.0f) / 255.0f), // 6
        VertexFormat(glm::vec3(-1.53f, 1.27f,  -5), glm::vec3(225.0f, 163.0f, 61.0f) / 255.0f), // 7
        VertexFormat(glm::vec3(-1.53f, 1.27f,  -5), glm::vec3(19.0f, 89.0f, 53.0f) / 255.0f), // 8
        VertexFormat(glm::vec3(-1.53f, 1.27f,  -5), glm::vec3(38.0f, 112.0f, 56.0f) / 255.0f), // 9
        VertexFormat(glm::vec3(-1.53f, 1.27f,  -5), glm::vec3(21.0f, 81.0f, 70.0f) / 255.0f), // 10
        VertexFormat(glm::vec3(-2.02f, 2.43f,  -5), glm::vec3(22.0f, 98.0f, 51.0f) / 255.0f), // 11
        VertexFormat(glm::vec3(-2.02f, 2.43f,  -5), glm::vec3(29.0f, 126.0f, 63.0f) / 255.0f), // 12
        VertexFormat(glm::vec3(-1.34f, 3.0f,  -5), glm::vec3(29.0f, 126.0f, 63.0f) / 255.0f), // 13
        VertexFormat(glm::vec3(-1.34f, 3.0f,  -5), glm::vec3(42.0f, 151.0f, 70.0f) / 255.0f), // 14
        VertexFormat(glm::vec3(-0.3f, 2.64f,  -5), glm::vec3(42.0f, 151.0f, 70.0f) / 255.0f), // 15
        VertexFormat(glm::vec3(-0.3f, 2.64f,  -5), glm::vec3(51.0f, 153.0f, 77.0f) / 255.0f), // 16
        VertexFormat(glm::vec3(-0.3f, 2.64f,  -5), glm::vec3(37.0f, 145.0f, 70.0f) / 255.0f), // 17
        VertexFormat(glm::vec3(-0.035f, 1.43f,  -5), glm::vec3(37.0f, 145.0f, 70.0f) / 255.0f), // 18
        VertexFormat(glm::vec3(-0.035f, 1.43f,  -5), glm::vec3(24.0f, 97.0f, 52.0f) / 255.0f), // 19
        VertexFormat(glm::vec3(-0.035f, 1.43f,  -5), glm::vec3(22.0f, 109.0f, 56.0f) / 255.0f), // 20
        
        VertexFormat(glm::vec3(-1.3f, 2.32f,  -5), glm::vec3(19.0f, 89.0f, 53.0f) / 255.0f), // 21
        VertexFormat(glm::vec3(-1.3f, 2.32f,  -5), glm::vec3(22.0f, 98.0f, 51.0f) / 255.0f), // 22
        VertexFormat(glm::vec3(-1.3f, 2.32f,  -5), glm::vec3(29.0f, 126.0f, 63.0f) / 255.0f), // 23
        VertexFormat(glm::vec3(-1.3f, 2.32f,  -5), glm::vec3(42.0f, 151.0f, 70.0f) / 255.0f), // 24
        VertexFormat(glm::vec3(-1.3f, 2.32f,  -5), glm::vec3(51.0f, 153.0f, 77.0f) / 255.0f), // 25
        VertexFormat(glm::vec3(-1.3f, 2.32f,  -5), glm::vec3(38.0f, 112.0f, 56.0f) / 255.0f), // 26

        VertexFormat(glm::vec3(-0.95f, 1.38f,  -5), glm::vec3(51.0f, 153.0f, 77.0f) / 255.0f), // 27
        VertexFormat(glm::vec3(-0.95f, 1.38f,  -5), glm::vec3(38.0f, 112.0f, 56.0f) / 255.0f), // 28
        VertexFormat(glm::vec3(-0.95f, 1.38f,  -5), glm::vec3(37.0f, 145.0f, 70.0f) / 255.0f), // 29
        VertexFormat(glm::vec3(-0.95f, 1.38f,  -5), glm::vec3(21.0f, 81.0f, 70.0f) / 255.0f), // 30
        VertexFormat(glm::vec3(-0.95f, 1.38f,  -5), glm::vec3(24.0f, 97.0f, 52.0f) / 255.0f), // 31
        VertexFormat(glm::vec3(-0.95f, 1.38f,  -5), glm::vec3(21.0f, 81.0f, 70.0f) / 255.0f), // 32
        VertexFormat(glm::vec3(-0.95f, 1.38f,  -5), glm::vec3(16.0f, 70.0f, 67.0f) / 255.0f), // 33

        VertexFormat(glm::vec3(-1.24f, 0.5f,  -5), glm::vec3(16.0f, 70.0f, 67.0f) / 255.0f), // 34
        VertexFormat(glm::vec3(-1.24f, 0.5f,  -5), glm::vec3(24.0f, 97.0f, 52.0f) / 255.0f), // 35
        VertexFormat(glm::vec3(-1.24f, 0.5f,  -5), glm::vec3(22.0f, 109.0f, 56.0f) / 255.0f), // 36
        VertexFormat(glm::vec3(-1.24f, 0.5f,  -5), glm::vec3(123.0f, 67.0f, 78.0f) / 255.0f), // 37
        VertexFormat(glm::vec3(-1.24f, 0.5f,  -5), glm::vec3(138.0f, 79.0f, 81.0f) / 255.0f), // 38

        VertexFormat(glm::vec3(-0.44f, 0.25f,  -5), glm::vec3(22.0f, 109.0f, 56.0f) / 255.0f), // 39
        VertexFormat(glm::vec3(-1.24f, 0.5f,  -5), glm::vec3(138.0f, 79.0f, 81.0f) / 255.0f), // 40
        VertexFormat(glm::vec3(-1.24f, 0.5f,  -5), glm::vec3(199.0f, 179.0f, 174.0f) / 255.0f), // 41
        VertexFormat(glm::vec3(-1.24f, 0.5f,  -5), glm::vec3(188.0f, 171.0f, 164.0f) / 255.0f), // 42

        VertexFormat(glm::vec3(-2.28f, 0.17f,  -5), glm::vec3(16.0f, 70.0f, 67.0f) / 255.0f), // 43
        VertexFormat(glm::vec3(-2.28f, 0.17f,  -5), glm::vec3(123.0f, 67.0f, 78.0f) / 255.0f), // 44
        VertexFormat(glm::vec3(-2.28f, 0.17f,  -5), glm::vec3(85.0f, 43.0f, 29.0f) / 255.0f), // 45

        VertexFormat(glm::vec3(-1.725f, -0.775f,  -5), glm::vec3(123.0f, 67.0f, 78.0f) / 255.0f), // 46
        VertexFormat(glm::vec3(-1.725f, -0.775f,  -5), glm::vec3(138.0f, 79.0f, 81.0f) / 255.0f), // 47
        VertexFormat(glm::vec3(-1.725f, -0.775f,  -5), glm::vec3(85.0f, 43.0f, 29.0f) / 255.0f), // 48
        VertexFormat(glm::vec3(-1.725f, -0.775f,  -5), glm::vec3(67.0f, 33.0f, 24.0f) / 255.0f), // 49
        VertexFormat(glm::vec3(-1.725f, -0.775f,  -5), glm::vec3(199.0f, 179.0f, 174.0f) / 255.0f), // 50
        VertexFormat(glm::vec3(-1.725f, -0.775f,  -5), glm::vec3(188.0f, 171.0f, 164.0f) / 255.0f), // 51

        VertexFormat(glm::vec3(-1.2f, -0.69f,  -5), glm::vec3(199.0f, 179.0f, 174.0f) / 255.0f), // 52
        VertexFormat(glm::vec3(-1.2f, -0.69f,  -5), glm::vec3(188.0f, 171.0f, 164.0f) / 255.0f), // 53
        VertexFormat(glm::vec3(-1.2f, -0.69f,  -5), glm::vec3(188.0f, 171.0f, 164.0f) / 255.0f), // 54
        VertexFormat(glm::vec3(-1.2f, -0.69f,  -5), glm::vec3(188.0f, 171.0f, 164.0f) / 255.0f), // 55

        VertexFormat(glm::vec3(-2.7f, -1.5f,  -5), glm::vec3(85.0f, 43.0f, 29.0f) / 255.0f), // 56
        VertexFormat(glm::vec3(-2.7f, -1.5f,  -5), glm::vec3(67.0f, 33.0f, 24.0f) / 255.0f), // 57

        VertexFormat(glm::vec3(-1.74f, -2.53f,  -5), glm::vec3(67.0f, 33.0f, 24.0f) / 255.0f), // 58
        VertexFormat(glm::vec3(-1.74f, -2.53f,  -5), glm::vec3(188.0f, 171.0f, 164.0f) / 255.0f), // 59
        VertexFormat(glm::vec3(-1.74f, -2.53f,  -5), glm::vec3(171.0f, 155.0f, 155.0f) / 255.0f), // 60

        VertexFormat(glm::vec3(-1.24f, 0.5f,  -5), glm::vec3(243.0f, 223.0f, 224.0f) / 255.0f), // 61

        VertexFormat(glm::vec3(-0.47f, -1.21f,  -5), glm::vec3(188.0f, 171.0f, 164.0f) / 255.0f), // 62
        VertexFormat(glm::vec3(-0.47f, -1.21f,  -5), glm::vec3(188.0f, 171.0f, 164.0f) / 255.0f), // 63
        VertexFormat(glm::vec3(-0.47f, -1.21f,  -5), glm::vec3(188.0f, 171.0f, 164.0f) / 255.0f), // 64
        VertexFormat(glm::vec3(-0.47f, -1.21f,  -5), glm::vec3(171.0f, 155.0f, 155.0f) / 255.0f), // 65
        VertexFormat(glm::vec3(-0.47f, -1.21f,  -5), glm::vec3(171.0f, 155.0f, 155.0f) / 255.0f), // 66
        VertexFormat(glm::vec3(-0.47f, -1.21f,  -5), glm::vec3(243.0f, 223.0f, 224.0f) / 255.0f), // 67
        VertexFormat(glm::vec3(-0.47f, -1.21f,  -5), glm::vec3(177.0f, 156.0f, 151.0f) / 255.0f), // 68
        VertexFormat(glm::vec3(-0.47f, -1.21f,  -5), glm::vec3(207.0f, 191.0f, 191.0f) / 255.0f), // 69

        VertexFormat(glm::vec3(-1.23f, -3.08f,  -5), glm::vec3(171.0f, 155.0f, 155.0f) / 255.0f), // 70
        VertexFormat(glm::vec3(-1.23f, -3.08f,  -5), glm::vec3(171.0f, 155.0f, 155.0f) / 255.0f), // 71

        VertexFormat(glm::vec3(0.8f, -3.29f,  -5), glm::vec3(171.0f, 155.0f, 155.0f) / 255.0f), // 72
        VertexFormat(glm::vec3(0.8f, -3.29f,  -5), glm::vec3(207.0f, 191.0f, 191.0f) / 255.0f), // 73
        VertexFormat(glm::vec3(0.8f, -3.29f,  -5), glm::vec3(121.0f, 110.0f, 104.0f) / 255.0f), // 74

        VertexFormat(glm::vec3(1.57f, -2.05f,  -5), glm::vec3(177.0f, 156.0f, 151.0f) / 255.0f), // 75
        VertexFormat(glm::vec3(1.57f, -2.05f,  -5), glm::vec3(207.0f, 191.0f, 191.0f) / 255.0f), // 76
        VertexFormat(glm::vec3(1.57f, -2.05f,  -5), glm::vec3(121.0f, 110.0f, 104.0f) / 255.0f), // 77
        VertexFormat(glm::vec3(1.57f, -2.05f,  -5), glm::vec3(121.0f, 110.0f, 104.0f) / 255.0f), // 78
        VertexFormat(glm::vec3(1.57f, -2.05f,  -5), glm::vec3(105.0f, 96.0f, 91.0f) / 255.0f), // 79
        VertexFormat(glm::vec3(1.57f, -2.05f,  -5), glm::vec3(105.0f, 96.0f, 91.0f) / 255.0f), // 80
        VertexFormat(glm::vec3(1.57f, -2.05f,  -5), glm::vec3(200.0f, 180.0f, 181.0f) / 255.0f), // 81

        VertexFormat(glm::vec3(1.72f, -1.17f,  -5), glm::vec3(177.0f, 156.0f, 151.0f) / 255.0f), // 82
        VertexFormat(glm::vec3(1.72f, -1.17f,  -5), glm::vec3(105.0f, 96.0f, 91.0f) / 255.0f), // 83

        VertexFormat(glm::vec3(1.02f, 0.25f,  -5), glm::vec3(243.0f, 223.0f, 224.0f) / 255.0f), // 84
        VertexFormat(glm::vec3(1.02f, 0.25f,  -5), glm::vec3(243.0f, 223.0f, 224.0f) / 255.0f), // 85

        VertexFormat(glm::vec3(3.8f, -1.13f,  -5), glm::vec3(243.0f, 223.0f, 224.0f) / 255.0f), // 86
        VertexFormat(glm::vec3(3.8f, -1.13f,  -5), glm::vec3(105.0f, 96.0f, 91.0f) / 255.0f), // 87
        VertexFormat(glm::vec3(3.8f, -1.13f,  -5), glm::vec3(200.0f, 180.0f, 181.0f) / 255.0f), // 88
        VertexFormat(glm::vec3(3.8f, -1.13f,  -5), glm::vec3(200.0f, 180.0f, 181.0f) / 255.0f), // 89
        VertexFormat(glm::vec3(3.8f, -1.13f,  -5), glm::vec3(199.0f, 179.0f, 180.0f) / 255.0f), // 90
        VertexFormat(glm::vec3(3.8f, -1.13f,  -5), glm::vec3(199.0f, 179.0f, 180.0f) / 255.0f), // 91

        VertexFormat(glm::vec3(2.263f, -2.15f,  -5), glm::vec3(105.0f, 96.0f, 91.0f) / 255.0f), // 92
        VertexFormat(glm::vec3(2.263f, -2.15f,  -5), glm::vec3(6.0f, 8.0f, 7.0f) / 255.0f), // 93

        VertexFormat(glm::vec3(3.6f, -2.15f,  -5), glm::vec3(6.0f, 8.0f, 7.0f) / 255.0f), // 94
        VertexFormat(glm::vec3(3.6f, -2.15f,  -5), glm::vec3(200.0f, 180.0f, 181.0f) / 255.0f), // 95
        VertexFormat(glm::vec3(3.6f, -2.15f,  -5), glm::vec3(200.0f, 180.0f, 181.0f) / 255.0f), // 96
        VertexFormat(glm::vec3(3.6f, -2.15f,  -5), glm::vec3(105.0f, 96.0f, 91.0f) / 255.0f), // 97

        VertexFormat(glm::vec3(2.63f, -2.8f,  -5), glm::vec3(121.0f, 110.0f, 104.0f) / 255.0f), // 98
        VertexFormat(glm::vec3(2.63f, -2.8f,  -5), glm::vec3(105.0f, 96.0f, 91.0f) / 255.0f), // 99
        VertexFormat(glm::vec3(2.63f, -2.8f,  -5), glm::vec3(6.0f, 8.0f, 7.0f) / 255.0f), // 100

        VertexFormat(glm::vec3(1.72f, -3.4f,  -5), glm::vec3(121.0f, 110.0f, 104.0f) / 255.0f), // 101
        VertexFormat(glm::vec3(1.72f, -3.4f,  -5), glm::vec3(121.0f, 110.0f, 104.0f) / 255.0f), // 102

        VertexFormat(glm::vec3(4.69f, -1.42f,  -5), glm::vec3(200.0f, 180.0f, 181.0f) / 255.0f), // 103
        VertexFormat(glm::vec3(4.69f, -1.42f,  -5), glm::vec3(199.0f, 179.0f, 180.0f) / 255.0f), // 104
        VertexFormat(glm::vec3(4.69f, -1.42f,  -5), glm::vec3(216.0f, 197.0f, 193.0f) / 255.0f), // 105

        VertexFormat(glm::vec3(4.7f, -0.9f,  -5), glm::vec3(216.0f, 197.0f, 193.0f) / 255.0f), // 106

        VertexFormat(glm::vec3(4.0f, -1.07f,  -5), glm::vec3(199.0f, 179.0f, 180.0f) / 255.0f), // 107
        VertexFormat(glm::vec3(4.0f, -1.07f,  -5), glm::vec3(216.0f, 197.0f, 193.0f) / 255.0f), // 108

        VertexFormat(glm::vec3(-0.03f, -3.2f,  5), glm::vec3(203.0f, 94.0f, 58.0f) / 255.0f), // 109

        VertexFormat(glm::vec3(0.3f, -3.25f,  5), glm::vec3(203.0f, 94.0f, 58.0f) / 255.0f), // 110
        VertexFormat(glm::vec3(0.3f, -3.25f,  5), glm::vec3(186.0f, 68.0f, 41.0f) / 255.0f), // 111

        VertexFormat(glm::vec3(-0.03f, -3.98f,  5), glm::vec3(203.0f, 94.0f, 58.0f) / 255.0f), // 112
        VertexFormat(glm::vec3(-0.03f, -3.98f,  5), glm::vec3(186.0f, 68.0f, 41.0f) / 255.0f), // 113
        VertexFormat(glm::vec3(-0.03f, -3.98f,  5), glm::vec3(155.0f, 53.0f, 34.0f) / 255.0f), // 114
        VertexFormat(glm::vec3(-0.03f, -3.98f,  5), glm::vec3(198.0f, 86.0f, 39.0f) / 255.0f), // 115

        VertexFormat(glm::vec3(-1.725f, -0.775f,  -5), glm::vec3(188.0f, 171.0f, 164.0f) / 255.0f), // 116

        VertexFormat(glm::vec3(0.22f, -4.0f,  5), glm::vec3(186.0f, 68.0f, 41.0f) / 255.0f), // 117
        VertexFormat(glm::vec3(0.22f, -4.0f,  5), glm::vec3(155.0f, 53.0f, 34.0f) / 255.0f), // 118
        VertexFormat(glm::vec3(0.22f, -4.0f,  5), glm::vec3(130.0f, 30.0f, 27.0f) / 255.0f), // 119

        VertexFormat(glm::vec3(-1.19f, -4.14f,  5), glm::vec3(198.0f, 86.0f, 39.0f) / 255.0f), // 120

        VertexFormat(glm::vec3(0.06f, -4.22f,  5), glm::vec3(198.0f, 86.0f, 39.0f) / 255.0f), // 121

        VertexFormat(glm::vec3(-0.7f, -4.23f,  5), glm::vec3(236.0f, 125.0f, 54.0f) / 255.0f), // 122

        VertexFormat(glm::vec3(-0.6f, -4.4f,  5), glm::vec3(236.0f, 125.0f, 54.0f) / 255.0f), // 123
        VertexFormat(glm::vec3(-0.6f, -4.4f,  5), glm::vec3(236.0f, 125.0f, 54.0f) / 255.0f), // 124
        VertexFormat(glm::vec3(-0.6f, -4.4f,  5), glm::vec3(236.0f, 125.0f, 54.0f) / 255.0f), // 125

        VertexFormat(glm::vec3(-0.93f, -4.5f,  5), glm::vec3(236.0f, 125.0f, 54.0f) / 255.0f), // 126

        VertexFormat(glm::vec3(-0.25f, -4.59f,  5), glm::vec3(236.0f, 125.0f, 54.0f) / 255.0f), // 127
        VertexFormat(glm::vec3(-0.25f, -4.59f,  5), glm::vec3(236.0f, 125.0f, 54.0f) / 255.0f), // 128
        VertexFormat(glm::vec3(-0.25f, -4.59f,  5), glm::vec3(236.0f, 125.0f, 54.0f) / 255.0f), // 129

        VertexFormat(glm::vec3(-0.27f, -4.85f,  5), glm::vec3(236.0f, 125.0f, 54.0f) / 255.0f), // 130

        VertexFormat(glm::vec3(0.43f, -4.535f,  5), glm::vec3(236.0f, 125.0f, 54.0f) / 255.0f), // 131
        VertexFormat(glm::vec3(0.43f, -4.535f,  5), glm::vec3(192.0f, 62.0f, 42.0f) / 255.0f), // 132
        VertexFormat(glm::vec3(0.43f, -4.535f,  5), glm::vec3(217.0f, 88.0f, 45.0f) / 255.0f), // 133

        VertexFormat(glm::vec3(0.8f, -4.64f,  5), glm::vec3(192.0f, 62.0f, 42.0f) / 255.0f), // 134

        VertexFormat(glm::vec3(0.6f, -4.25f,  5), glm::vec3(192.0f, 62.0f, 42.0f) / 255.0f), // 135
        VertexFormat(glm::vec3(0.6f, -4.25f,  5), glm::vec3(217.0f, 88.0f, 45.0f) / 255.0f), // 136
        VertexFormat(glm::vec3(0.6f, -4.25f,  5), glm::vec3(238.0f, 99.0f, 45.0f) / 255.0f), // 137
        VertexFormat(glm::vec3(0.6f, -4.25f,  5), glm::vec3(170.0f, 66.0f, 39.0f) / 255.0f), // 138

        VertexFormat(glm::vec3(0.35f, -4.2f,  5), glm::vec3(130.0f, 30.0f, 27.0f) / 255.0f), // 139
        VertexFormat(glm::vec3(0.35f, -4.2f,  5), glm::vec3(236.0f, 125.0f, 54.0f) / 255.0f), // 140
        VertexFormat(glm::vec3(0.35f, -4.2f,  5), glm::vec3(236.0f, 125.0f, 54.0f) / 255.0f), // 141
        VertexFormat(glm::vec3(0.35f, -4.2f,  5), glm::vec3(217.0f, 88.0f, 45.0f) / 255.0f), // 142
        VertexFormat(glm::vec3(0.35f, -4.2f,  5), glm::vec3(238.0f, 99.0f, 45.0f) / 255.0f), // 143

        VertexFormat(glm::vec3(0.06f, -4.22f,  5), glm::vec3(155.0f, 53.0f, 34.0f) / 255.0f), // 144
        VertexFormat(glm::vec3(0.06f, -4.22f,  5), glm::vec3(130.0f, 30.0f, 27.0f) / 255.0f), // 145

        VertexFormat(glm::vec3(0.6f, -3.28f,  5), glm::vec3(238.0f, 99.0f, 45.0f) / 255.0f), // 146
        VertexFormat(glm::vec3(0.6f, -3.28f,  5), glm::vec3(170.0f, 66.0f, 39.0f) / 255.0f), // 147

        VertexFormat(glm::vec3(1.03f, -3.32f,  5), glm::vec3(170.0f, 66.0f, 39.0f) / 255.0f), // 148

        VertexFormat(glm::vec3(2.263f, -2.15f, -5), glm::vec3(105.0f, 96.0f, 91.0f) / 255.0f) // 149

    };

    std::vector<unsigned int> indices = {
    0, 3, 6, 	    //  glm::vec3(228.0f, 183.0f, 74.0f)
    4, 5, 7, 	    //  glm::vec3(225.0f, 163.0f, 61.0f)
    1, 21, 8,	    //  glm::vec3(19.0f, 89.0f, 53.0f)
    11, 22, 2,	    //  glm::vec3(22.0f, 98.0f, 51.0f)
    12, 13, 23,	    //  glm::vec3(29.0f, 126.0f, 63.0f)
    14, 24, 15,	    //  glm::vec3(42.0f, 151.0f, 70.0f)
    16, 25, 27,	    //  glm::vec3(51.0f, 153.0f, 77.0f)
    9, 26, 28,	    //  glm::vec3(38.0f, 112.0f, 56.0f)
    29, 17, 18,	    //  glm::vec3(37.0f, 145.0f, 70.0f)
    10, 32, 30,	    //  glm::vec3(21.0f, 81.0f, 70.0f)
    33, 34, 43,	    //  glm::vec3(16.0f, 70.0f, 67.0f)
    19, 31, 35,	    //  glm::vec3(24.0f, 97.0f, 52.0f)
    20, 39, 36,	    //  glm::vec3(22.0f, 109.0f, 56.0f)
    44, 46, 37,	    //  glm::vec3(123.0f, 67.0f, 78.0f)
    40, 38, 47,	    //  glm::vec3(138.0f, 79.0f, 81.0f)
    45, 48, 56,	    //  glm::vec3(85.0f, 43.0f, 29.0f)
    57, 49, 58,	    //  glm::vec3(67.0f, 33.0f, 24.0f)
    41, 52, 50,	    // glm::vec3(199.0f, 179.0f, 174.0f)
    53, 42, 62,	    // glm::vec3(188.0f, 171.0f, 164.0f)
    51, 54, 63,	    // glm::vec3(188.0f, 171.0f, 164.0f)
    116, 64, 59,	// glm::vec3(188.0f, 171.0f, 164.0f)
    65, 60, 70,	    // glm::vec3(171.0f, 155.0f, 155.0f)
    66, 71, 72,	    // glm::vec3(171.0f, 155.0f, 155.0f)
    61, 84, 67,	    // glm::vec3(243.0f, 223.0f, 224.0f)
    85, 67, 86,	    // glm::vec3(243.0f, 223.0f, 224.0f)
    68, 82, 75,	    // glm::vec3(177.0f, 156.0f, 151.0f)
    69, 73, 76,	    // glm::vec3(207.0f, 191.0f, 191.0f)
    77, 74, 101,    // glm::vec3(121.0f, 110.0f, 104.0f)
    102, 78, 98,	// glm::vec3(121.0f, 110.0f, 104.0f)
    99, 79, 92,	    // glm::vec3(105.0f, 96.0f, 91.0f)
    93, 94, 100,	// glm::vec3(6.0f, 8.0f, 7.0f)
    83, 80, 87,	    // glm::vec3(105.0f, 96.0f, 91.0f)
    81, 88, 95,	    // glm::vec3(200.0f, 180.0f, 181.0f)
    89, 96, 103,	// glm::vec3(200.0f, 180.0f, 181.0f)
    107, 90, 104,	// glm::vec3(199.0f, 179.0f, 180.0f)
    106, 108, 105,	// glm::vec3(216.0f, 197.0f, 193.0f)
    109, 110, 112,	// glm::vec3(203.0f, 94.0f, 58.0f)
    111, 113, 117,	// glm::vec3(186.0f, 68.0f, 41.0f)
    114, 144, 118,	// glm::vec3(155.0f, 53.0f, 34.0f)
    119, 145, 139,	// glm::vec3(130.0f, 30.0f, 27.0f)
    120, 121, 115,	// glm::vec3(198.0f, 86.0f, 39.0f)
    122, 123, 140,	// glm::vec3(236.0f, 125.0f, 54.0f)
    124, 126, 127,	// glm::vec3(236.0f, 125.0f, 54.0f)
    128, 130, 131,	// glm::vec3(236.0f, 125.0f, 54.0f)
    125, 129, 141,	// glm::vec3(236.0f, 125.0f, 54.0f)
    129, 141, 131,	// glm::vec3(236.0f, 125.0f, 54.0f)
    132, 135, 134,	// glm::vec3(192.0f, 62.0f, 42.0f)
    142, 136, 133,	// glm::vec3(217.0f, 88.0f, 45.0f)
    143, 146, 137,	// glm::vec3(238.0f, 99.0f, 45.0f)
    148, 138, 147,	// glm::vec3(170.0f, 66.0f, 39.0f)
    97, 149, 80 // glm::vec3(105.0f, 96.0f, 91.0f)
    };

    Mesh* duck = new Mesh(name);

    if (!fill) {
        duck->SetDrawMode(GL_LINE_LOOP);
    }
    else {
        // Draw 2 triangles. Add the remaining 2 indices
        indices.push_back(0);
        indices.push_back(2);
    }

    duck->InitFromData(vertices, indices);
    return duck;
}

Mesh* createObject2D::CreateFlyingDuck(const std::string& name, bool fill) {
    std::vector<VertexFormat> vertices
    {
        VertexFormat(glm::vec3(-2.04f, 1.95f,  -5), glm::vec3(228.0f, 183.0f, 74.0f) / 255.0f), // 0
        VertexFormat(glm::vec3(-2.04f, 1.95f,  -5), glm::vec3(19.0f, 89.0f, 53.0f) / 255.0f), // 1
        VertexFormat(glm::vec3(-2.04f, 1.95f,  -5), glm::vec3(22.0f, 98.0f, 51.0f) / 255.0f), // 2
        VertexFormat(glm::vec3(-3.23f, 1.46f,  -5), glm::vec3(228.0f, 183.0f, 74.0f) / 255.0f), // 3
        VertexFormat(glm::vec3(-3.23f, 1.46f,  -5), glm::vec3(225.0f, 163.0f, 61.0f) / 255.0f), // 4
        VertexFormat(glm::vec3(-3.23f, 1.265f,  -5), glm::vec3(225.0f, 163.0f, 61.0f) / 255.0f), // 5
        VertexFormat(glm::vec3(-1.53f, 1.27f,  -5), glm::vec3(228.0f, 183.0f, 74.0f) / 255.0f), // 6
        VertexFormat(glm::vec3(-1.53f, 1.27f,  -5), glm::vec3(225.0f, 163.0f, 61.0f) / 255.0f), // 7
        VertexFormat(glm::vec3(-1.53f, 1.27f,  -5), glm::vec3(19.0f, 89.0f, 53.0f) / 255.0f), // 8
        VertexFormat(glm::vec3(-1.53f, 1.27f,  -5), glm::vec3(38.0f, 112.0f, 56.0f) / 255.0f), // 9
        VertexFormat(glm::vec3(-1.53f, 1.27f,  -5), glm::vec3(21.0f, 81.0f, 70.0f) / 255.0f), // 10
        VertexFormat(glm::vec3(-2.02f, 2.43f,  -5), glm::vec3(22.0f, 98.0f, 51.0f) / 255.0f), // 11
        VertexFormat(glm::vec3(-2.02f, 2.43f,  -5), glm::vec3(29.0f, 126.0f, 63.0f) / 255.0f), // 12
        VertexFormat(glm::vec3(-1.34f, 3.0f,  -5), glm::vec3(29.0f, 126.0f, 63.0f) / 255.0f), // 13
        VertexFormat(glm::vec3(-1.34f, 3.0f,  -5), glm::vec3(42.0f, 151.0f, 70.0f) / 255.0f), // 14
        VertexFormat(glm::vec3(-0.3f, 2.64f,  -5), glm::vec3(42.0f, 151.0f, 70.0f) / 255.0f), // 15
        VertexFormat(glm::vec3(-0.3f, 2.64f,  -5), glm::vec3(51.0f, 153.0f, 77.0f) / 255.0f), // 16
        VertexFormat(glm::vec3(-0.3f, 2.64f,  -5), glm::vec3(37.0f, 145.0f, 70.0f) / 255.0f), // 17
        VertexFormat(glm::vec3(-0.035f, 1.43f,  -5), glm::vec3(37.0f, 145.0f, 70.0f) / 255.0f), // 18
        VertexFormat(glm::vec3(-0.035f, 1.43f,  -5), glm::vec3(24.0f, 97.0f, 52.0f) / 255.0f), // 19
        VertexFormat(glm::vec3(-0.035f, 1.43f,  -5), glm::vec3(22.0f, 109.0f, 56.0f) / 255.0f), // 20

        VertexFormat(glm::vec3(-1.3f, 2.32f,  -5), glm::vec3(19.0f, 89.0f, 53.0f) / 255.0f), // 21
        VertexFormat(glm::vec3(-1.3f, 2.32f,  -5), glm::vec3(22.0f, 98.0f, 51.0f) / 255.0f), // 22
        VertexFormat(glm::vec3(-1.3f, 2.32f,  -5), glm::vec3(29.0f, 126.0f, 63.0f) / 255.0f), // 23
        VertexFormat(glm::vec3(-1.3f, 2.32f,  -5), glm::vec3(42.0f, 151.0f, 70.0f) / 255.0f), // 24
        VertexFormat(glm::vec3(-1.3f, 2.32f,  -5), glm::vec3(51.0f, 153.0f, 77.0f) / 255.0f), // 25
        VertexFormat(glm::vec3(-1.3f, 2.32f,  -5), glm::vec3(38.0f, 112.0f, 56.0f) / 255.0f), // 26

        VertexFormat(glm::vec3(-0.95f, 1.38f,  -5), glm::vec3(51.0f, 153.0f, 77.0f) / 255.0f), // 27
        VertexFormat(glm::vec3(-0.95f, 1.38f,  -5), glm::vec3(38.0f, 112.0f, 56.0f) / 255.0f), // 28
        VertexFormat(glm::vec3(-0.95f, 1.38f,  -5), glm::vec3(37.0f, 145.0f, 70.0f) / 255.0f), // 29
        VertexFormat(glm::vec3(-0.95f, 1.38f,  -5), glm::vec3(21.0f, 81.0f, 70.0f) / 255.0f), // 30
        VertexFormat(glm::vec3(-0.95f, 1.38f,  -5), glm::vec3(24.0f, 97.0f, 52.0f) / 255.0f), // 31
        VertexFormat(glm::vec3(-0.95f, 1.38f,  -5), glm::vec3(21.0f, 81.0f, 70.0f) / 255.0f), // 32
        VertexFormat(glm::vec3(-0.95f, 1.38f,  -5), glm::vec3(16.0f, 70.0f, 67.0f) / 255.0f), // 33

        VertexFormat(glm::vec3(-1.24f, 0.5f,  -5), glm::vec3(16.0f, 70.0f, 67.0f) / 255.0f), // 34
        VertexFormat(glm::vec3(-1.24f, 0.5f,  -5), glm::vec3(24.0f, 97.0f, 52.0f) / 255.0f), // 35
        VertexFormat(glm::vec3(-1.24f, 0.5f,  -5), glm::vec3(22.0f, 109.0f, 56.0f) / 255.0f), // 36
        VertexFormat(glm::vec3(-1.24f, 0.5f,  -5), glm::vec3(123.0f, 67.0f, 78.0f) / 255.0f), // 37
        VertexFormat(glm::vec3(-1.24f, 0.5f,  -5), glm::vec3(138.0f, 79.0f, 81.0f) / 255.0f), // 38

        VertexFormat(glm::vec3(-0.44f, 0.25f,  -5), glm::vec3(22.0f, 109.0f, 56.0f) / 255.0f), // 39
        VertexFormat(glm::vec3(-1.24f, 0.5f,  -5), glm::vec3(138.0f, 79.0f, 81.0f) / 255.0f), // 40
        VertexFormat(glm::vec3(-1.24f, 0.5f,  -5), glm::vec3(199.0f, 179.0f, 174.0f) / 255.0f), // 41
        VertexFormat(glm::vec3(-1.24f, 0.5f,  -5), glm::vec3(188.0f, 171.0f, 164.0f) / 255.0f), // 42

        VertexFormat(glm::vec3(-2.28f, 0.17f,  -5), glm::vec3(16.0f, 70.0f, 67.0f) / 255.0f), // 43
        VertexFormat(glm::vec3(-2.28f, 0.17f,  -5), glm::vec3(123.0f, 67.0f, 78.0f) / 255.0f), // 44
        VertexFormat(glm::vec3(-2.28f, 0.17f,  -5), glm::vec3(85.0f, 43.0f, 29.0f) / 255.0f), // 45

        VertexFormat(glm::vec3(-1.725f, -0.775f,  -5), glm::vec3(123.0f, 67.0f, 78.0f) / 255.0f), // 46
        VertexFormat(glm::vec3(-1.725f, -0.775f,  -5), glm::vec3(138.0f, 79.0f, 81.0f) / 255.0f), // 47
        VertexFormat(glm::vec3(-1.725f, -0.775f,  -5), glm::vec3(85.0f, 43.0f, 29.0f) / 255.0f), // 48
        VertexFormat(glm::vec3(-1.725f, -0.775f,  -5), glm::vec3(67.0f, 33.0f, 24.0f) / 255.0f), // 49
        VertexFormat(glm::vec3(-1.725f, -0.775f,  -5), glm::vec3(199.0f, 179.0f, 174.0f) / 255.0f), // 50
        VertexFormat(glm::vec3(-1.725f, -0.775f,  -5), glm::vec3(188.0f, 171.0f, 164.0f) / 255.0f), // 51

        VertexFormat(glm::vec3(-1.2f, -0.69f,  -5), glm::vec3(199.0f, 179.0f, 174.0f) / 255.0f), // 52
        VertexFormat(glm::vec3(-1.2f, -0.69f,  -5), glm::vec3(188.0f, 171.0f, 164.0f) / 255.0f), // 53
        VertexFormat(glm::vec3(-1.2f, -0.69f,  -5), glm::vec3(188.0f, 171.0f, 164.0f) / 255.0f), // 54
        VertexFormat(glm::vec3(-1.2f, -0.69f,  -5), glm::vec3(188.0f, 171.0f, 164.0f) / 255.0f), // 55

        VertexFormat(glm::vec3(-2.7f, -1.5f,  -5), glm::vec3(85.0f, 43.0f, 29.0f) / 255.0f), // 56
        VertexFormat(glm::vec3(-2.7f, -1.5f,  -5), glm::vec3(67.0f, 33.0f, 24.0f) / 255.0f), // 57

        VertexFormat(glm::vec3(-1.74f, -2.53f,  -5), glm::vec3(67.0f, 33.0f, 24.0f) / 255.0f), // 58
        VertexFormat(glm::vec3(-1.74f, -2.53f,  -5), glm::vec3(188.0f, 171.0f, 164.0f) / 255.0f), // 59
        VertexFormat(glm::vec3(-1.74f, -2.53f,  -5), glm::vec3(171.0f, 155.0f, 155.0f) / 255.0f), // 60

        VertexFormat(glm::vec3(-1.24f, 0.5f,  -5), glm::vec3(243.0f, 223.0f, 224.0f) / 255.0f), // 61

        VertexFormat(glm::vec3(-0.47f, -1.21f,  -5), glm::vec3(188.0f, 171.0f, 164.0f) / 255.0f), // 62
        VertexFormat(glm::vec3(-0.47f, -1.21f,  -5), glm::vec3(188.0f, 171.0f, 164.0f) / 255.0f), // 63
        VertexFormat(glm::vec3(-0.47f, -1.21f,  -5), glm::vec3(188.0f, 171.0f, 164.0f) / 255.0f), // 64
        VertexFormat(glm::vec3(-0.47f, -1.21f,  -5), glm::vec3(171.0f, 155.0f, 155.0f) / 255.0f), // 65
        VertexFormat(glm::vec3(-0.47f, -1.21f,  -5), glm::vec3(171.0f, 155.0f, 155.0f) / 255.0f), // 66
        VertexFormat(glm::vec3(-0.47f, -1.21f,  -5), glm::vec3(243.0f, 223.0f, 224.0f) / 255.0f), // 67
        VertexFormat(glm::vec3(-0.47f, -1.21f,  -5), glm::vec3(177.0f, 156.0f, 151.0f) / 255.0f), // 68
        VertexFormat(glm::vec3(-0.47f, -1.21f,  -5), glm::vec3(207.0f, 191.0f, 191.0f) / 255.0f), // 69

        VertexFormat(glm::vec3(-1.23f, -3.08f,  -5), glm::vec3(171.0f, 155.0f, 155.0f) / 255.0f), // 70
        VertexFormat(glm::vec3(-1.23f, -3.08f,  -5), glm::vec3(171.0f, 155.0f, 155.0f) / 255.0f), // 71

        VertexFormat(glm::vec3(0.8f, -3.29f,  -5), glm::vec3(171.0f, 155.0f, 155.0f) / 255.0f), // 72
        VertexFormat(glm::vec3(0.8f, -3.29f,  -5), glm::vec3(207.0f, 191.0f, 191.0f) / 255.0f), // 73
        VertexFormat(glm::vec3(0.8f, -3.29f,  -5), glm::vec3(121.0f, 110.0f, 104.0f) / 255.0f), // 74

        VertexFormat(glm::vec3(1.57f, -2.05f,  -5), glm::vec3(177.0f, 156.0f, 151.0f) / 255.0f), // 75
        VertexFormat(glm::vec3(1.57f, -2.05f,  -5), glm::vec3(207.0f, 191.0f, 191.0f) / 255.0f), // 76
        VertexFormat(glm::vec3(1.57f, -2.05f,  -5), glm::vec3(121.0f, 110.0f, 104.0f) / 255.0f), // 77
        VertexFormat(glm::vec3(1.57f, -2.05f,  -5), glm::vec3(121.0f, 110.0f, 104.0f) / 255.0f), // 78
        VertexFormat(glm::vec3(1.57f, -2.05f,  -5), glm::vec3(105.0f, 96.0f, 91.0f) / 255.0f), // 79
        VertexFormat(glm::vec3(1.57f, -2.05f,  -5), glm::vec3(105.0f, 96.0f, 91.0f) / 255.0f), // 80
        VertexFormat(glm::vec3(1.57f, -2.05f,  -5), glm::vec3(200.0f, 180.0f, 181.0f) / 255.0f), // 81

        VertexFormat(glm::vec3(1.72f, -1.17f,  -5), glm::vec3(177.0f, 156.0f, 151.0f) / 255.0f), // 82
        VertexFormat(glm::vec3(1.72f, -1.17f,  -5), glm::vec3(105.0f, 96.0f, 91.0f) / 255.0f), // 83

        VertexFormat(glm::vec3(1.02f, 0.25f,  -5), glm::vec3(243.0f, 223.0f, 224.0f) / 255.0f), // 84
        VertexFormat(glm::vec3(1.02f, 0.25f,  -5), glm::vec3(243.0f, 223.0f, 224.0f) / 255.0f), // 85

        VertexFormat(glm::vec3(3.8f, -1.13f,  -5), glm::vec3(243.0f, 223.0f, 224.0f) / 255.0f), // 86
        VertexFormat(glm::vec3(3.8f, -1.13f,  -5), glm::vec3(105.0f, 96.0f, 91.0f) / 255.0f), // 87
        VertexFormat(glm::vec3(3.8f, -1.13f,  -5), glm::vec3(200.0f, 180.0f, 181.0f) / 255.0f), // 88
        VertexFormat(glm::vec3(3.8f, -1.13f,  -5), glm::vec3(200.0f, 180.0f, 181.0f) / 255.0f), // 89
        VertexFormat(glm::vec3(3.8f, -1.13f,  -5), glm::vec3(199.0f, 179.0f, 180.0f) / 255.0f), // 90
        VertexFormat(glm::vec3(3.8f, -1.13f,  -5), glm::vec3(199.0f, 179.0f, 180.0f) / 255.0f), // 91

        VertexFormat(glm::vec3(2.263f, -2.15f,  -5), glm::vec3(105.0f, 96.0f, 91.0f) / 255.0f), // 92
        VertexFormat(glm::vec3(2.263f, -2.15f,  -5), glm::vec3(6.0f, 8.0f, 7.0f) / 255.0f), // 93

        VertexFormat(glm::vec3(3.6f, -2.15f,  -5), glm::vec3(6.0f, 8.0f, 7.0f) / 255.0f), // 94
        VertexFormat(glm::vec3(3.6f, -2.15f,  -5), glm::vec3(200.0f, 180.0f, 181.0f) / 255.0f), // 95
        VertexFormat(glm::vec3(3.6f, -2.15f,  -5), glm::vec3(200.0f, 180.0f, 181.0f) / 255.0f), // 96
        VertexFormat(glm::vec3(3.6f, -2.15f,  -5), glm::vec3(105.0f, 96.0f, 91.0f) / 255.0f), // 97

        VertexFormat(glm::vec3(2.63f, -2.8f,  -5), glm::vec3(121.0f, 110.0f, 104.0f) / 255.0f), // 98
        VertexFormat(glm::vec3(2.63f, -2.8f,  -5), glm::vec3(105.0f, 96.0f, 91.0f) / 255.0f), // 99
        VertexFormat(glm::vec3(2.63f, -2.8f,  -5), glm::vec3(6.0f, 8.0f, 7.0f) / 255.0f), // 100

        VertexFormat(glm::vec3(1.72f, -3.4f,  -5), glm::vec3(121.0f, 110.0f, 104.0f) / 255.0f), // 101
        VertexFormat(glm::vec3(1.72f, -3.4f,  -5), glm::vec3(121.0f, 110.0f, 104.0f) / 255.0f), // 102

        VertexFormat(glm::vec3(4.69f, -1.42f,  -5), glm::vec3(200.0f, 180.0f, 181.0f) / 255.0f), // 103
        VertexFormat(glm::vec3(4.69f, -1.42f,  -5), glm::vec3(199.0f, 179.0f, 180.0f) / 255.0f), // 104
        VertexFormat(glm::vec3(4.69f, -1.42f,  -5), glm::vec3(216.0f, 197.0f, 193.0f) / 255.0f), // 105

        VertexFormat(glm::vec3(4.7f, -0.9f,  -5), glm::vec3(216.0f, 197.0f, 193.0f) / 255.0f), // 106

        VertexFormat(glm::vec3(4.0f, -1.07f,  -5), glm::vec3(199.0f, 179.0f, 180.0f) / 255.0f), // 107
        VertexFormat(glm::vec3(4.0f, -1.07f,  -5), glm::vec3(216.0f, 197.0f, 193.0f) / 255.0f), // 108

        VertexFormat(glm::vec3(-0.03f, -3.2f,  5), glm::vec3(203.0f, 94.0f, 58.0f) / 255.0f), // 109

        VertexFormat(glm::vec3(0.3f, -3.25f,  5), glm::vec3(203.0f, 94.0f, 58.0f) / 255.0f), // 110
        VertexFormat(glm::vec3(0.3f, -3.25f,  5), glm::vec3(186.0f, 68.0f, 41.0f) / 255.0f), // 111

        VertexFormat(glm::vec3(-0.03f, -3.98f,  5), glm::vec3(203.0f, 94.0f, 58.0f) / 255.0f), // 112
        VertexFormat(glm::vec3(-0.03f, -3.98f,  5), glm::vec3(186.0f, 68.0f, 41.0f) / 255.0f), // 113
        VertexFormat(glm::vec3(-0.03f, -3.98f,  5), glm::vec3(155.0f, 53.0f, 34.0f) / 255.0f), // 114
        VertexFormat(glm::vec3(-0.03f, -3.98f,  5), glm::vec3(198.0f, 86.0f, 39.0f) / 255.0f), // 115

        VertexFormat(glm::vec3(-1.725f, -0.775f,  -5), glm::vec3(188.0f, 171.0f, 164.0f) / 255.0f), // 116

        VertexFormat(glm::vec3(0.22f, -4.0f,  5), glm::vec3(186.0f, 68.0f, 41.0f) / 255.0f), // 117
        VertexFormat(glm::vec3(0.22f, -4.0f,  5), glm::vec3(155.0f, 53.0f, 34.0f) / 255.0f), // 118
        VertexFormat(glm::vec3(0.22f, -4.0f,  5), glm::vec3(130.0f, 30.0f, 27.0f) / 255.0f), // 119

        VertexFormat(glm::vec3(-1.19f, -4.14f,  5), glm::vec3(198.0f, 86.0f, 39.0f) / 255.0f), // 120

        VertexFormat(glm::vec3(0.06f, -4.22f,  5), glm::vec3(198.0f, 86.0f, 39.0f) / 255.0f), // 121

        VertexFormat(glm::vec3(-0.7f, -4.23f,  5), glm::vec3(236.0f, 125.0f, 54.0f) / 255.0f), // 122

        VertexFormat(glm::vec3(-0.6f, -4.4f,  5), glm::vec3(236.0f, 125.0f, 54.0f) / 255.0f), // 123
        VertexFormat(glm::vec3(-0.6f, -4.4f,  5), glm::vec3(236.0f, 125.0f, 54.0f) / 255.0f), // 124
        VertexFormat(glm::vec3(-0.6f, -4.4f,  5), glm::vec3(236.0f, 125.0f, 54.0f) / 255.0f), // 125

        VertexFormat(glm::vec3(-0.93f, -4.5f,  5), glm::vec3(236.0f, 125.0f, 54.0f) / 255.0f), // 126

        VertexFormat(glm::vec3(-0.25f, -4.59f,  5), glm::vec3(236.0f, 125.0f, 54.0f) / 255.0f), // 127
        VertexFormat(glm::vec3(-0.25f, -4.59f,  5), glm::vec3(236.0f, 125.0f, 54.0f) / 255.0f), // 128
        VertexFormat(glm::vec3(-0.25f, -4.59f,  5), glm::vec3(236.0f, 125.0f, 54.0f) / 255.0f), // 129

        VertexFormat(glm::vec3(-0.27f, -4.85f,  5), glm::vec3(236.0f, 125.0f, 54.0f) / 255.0f), // 130

        VertexFormat(glm::vec3(0.43f, -4.535f,  5), glm::vec3(236.0f, 125.0f, 54.0f) / 255.0f), // 131
        VertexFormat(glm::vec3(0.43f, -4.535f,  5), glm::vec3(192.0f, 62.0f, 42.0f) / 255.0f), // 132
        VertexFormat(glm::vec3(0.43f, -4.535f,  5), glm::vec3(217.0f, 88.0f, 45.0f) / 255.0f), // 133

        VertexFormat(glm::vec3(0.8f, -4.64f,  5), glm::vec3(192.0f, 62.0f, 42.0f) / 255.0f), // 134

        VertexFormat(glm::vec3(0.6f, -4.25f,  5), glm::vec3(192.0f, 62.0f, 42.0f) / 255.0f), // 135
        VertexFormat(glm::vec3(0.6f, -4.25f,  5), glm::vec3(217.0f, 88.0f, 45.0f) / 255.0f), // 136
        VertexFormat(glm::vec3(0.6f, -4.25f,  5), glm::vec3(238.0f, 99.0f, 45.0f) / 255.0f), // 137
        VertexFormat(glm::vec3(0.6f, -4.25f,  5), glm::vec3(170.0f, 66.0f, 39.0f) / 255.0f), // 138

        VertexFormat(glm::vec3(0.35f, -4.2f,  5), glm::vec3(130.0f, 30.0f, 27.0f) / 255.0f), // 139
        VertexFormat(glm::vec3(0.35f, -4.2f,  5), glm::vec3(236.0f, 125.0f, 54.0f) / 255.0f), // 140
        VertexFormat(glm::vec3(0.35f, -4.2f,  5), glm::vec3(236.0f, 125.0f, 54.0f) / 255.0f), // 141
        VertexFormat(glm::vec3(0.35f, -4.2f,  5), glm::vec3(217.0f, 88.0f, 45.0f) / 255.0f), // 142
        VertexFormat(glm::vec3(0.35f, -4.2f,  5), glm::vec3(238.0f, 99.0f, 45.0f) / 255.0f), // 143

        VertexFormat(glm::vec3(0.06f, -4.22f,  5), glm::vec3(155.0f, 53.0f, 34.0f) / 255.0f), // 144
        VertexFormat(glm::vec3(0.06f, -4.22f,  5), glm::vec3(130.0f, 30.0f, 27.0f) / 255.0f), // 145

        VertexFormat(glm::vec3(0.6f, -3.28f,  5), glm::vec3(238.0f, 99.0f, 45.0f) / 255.0f), // 146
        VertexFormat(glm::vec3(0.6f, -3.28f,  5), glm::vec3(170.0f, 66.0f, 39.0f) / 255.0f), // 147

        VertexFormat(glm::vec3(1.03f, -3.32f,  5), glm::vec3(170.0f, 66.0f, 39.0f) / 255.0f), // 148

        VertexFormat(glm::vec3(2.263f, -2.15f, -5), glm::vec3(105.0f, 96.0f, 91.0f) / 255.0f) // 149

    };

    std::vector<unsigned int> indices = {
    0, 3, 6, 	    //  glm::vec3(228.0f, 183.0f, 74.0f)
    4, 5, 7, 	    //  glm::vec3(225.0f, 163.0f, 61.0f)
    1, 21, 8,	    //  glm::vec3(19.0f, 89.0f, 53.0f)
    11, 22, 2,	    //  glm::vec3(22.0f, 98.0f, 51.0f)
    12, 13, 23,	    //  glm::vec3(29.0f, 126.0f, 63.0f)
    14, 24, 15,	    //  glm::vec3(42.0f, 151.0f, 70.0f)
    16, 25, 27,	    //  glm::vec3(51.0f, 153.0f, 77.0f)
    9, 26, 28,	    //  glm::vec3(38.0f, 112.0f, 56.0f)
    29, 17, 18,	    //  glm::vec3(37.0f, 145.0f, 70.0f)
    10, 32, 30,	    //  glm::vec3(21.0f, 81.0f, 70.0f)
    33, 34, 43,	    //  glm::vec3(16.0f, 70.0f, 67.0f)
    19, 31, 35,	    //  glm::vec3(24.0f, 97.0f, 52.0f)
    20, 39, 36,	    //  glm::vec3(22.0f, 109.0f, 56.0f)
    44, 46, 37,	    //  glm::vec3(123.0f, 67.0f, 78.0f)
    40, 38, 47,	    //  glm::vec3(138.0f, 79.0f, 81.0f)
    45, 48, 56,	    //  glm::vec3(85.0f, 43.0f, 29.0f)
    57, 49, 58,	    //  glm::vec3(67.0f, 33.0f, 24.0f)
    41, 52, 50,	    // glm::vec3(199.0f, 179.0f, 174.0f)
    53, 42, 62,	    // glm::vec3(188.0f, 171.0f, 164.0f)
    51, 54, 63,	    // glm::vec3(188.0f, 171.0f, 164.0f)
    116, 64, 59,	// glm::vec3(188.0f, 171.0f, 164.0f)
    65, 60, 70,	    // glm::vec3(171.0f, 155.0f, 155.0f)
    66, 71, 72,	    // glm::vec3(171.0f, 155.0f, 155.0f)
    61, 84, 67,	    // glm::vec3(243.0f, 223.0f, 224.0f)
    85, 67, 86,	    // glm::vec3(243.0f, 223.0f, 224.0f)
    68, 82, 75,	    // glm::vec3(177.0f, 156.0f, 151.0f)
    69, 73, 76,	    // glm::vec3(207.0f, 191.0f, 191.0f)
    77, 74, 101,    // glm::vec3(121.0f, 110.0f, 104.0f)
    102, 78, 98,	// glm::vec3(121.0f, 110.0f, 104.0f)
    99, 79, 92,	    // glm::vec3(105.0f, 96.0f, 91.0f)
    93, 94, 100,	// glm::vec3(6.0f, 8.0f, 7.0f)
    83, 80, 87,	    // glm::vec3(105.0f, 96.0f, 91.0f)
    81, 88, 95,	    // glm::vec3(200.0f, 180.0f, 181.0f)
    89, 96, 103,	// glm::vec3(200.0f, 180.0f, 181.0f)
    107, 90, 104,	// glm::vec3(199.0f, 179.0f, 180.0f)
    106, 108, 105,	// glm::vec3(216.0f, 197.0f, 193.0f)
    97, 149, 80 // glm::vec3(105.0f, 96.0f, 91.0f)
    };

    Mesh* duck = new Mesh(name);

    if (!fill) {
        duck->SetDrawMode(GL_LINE_LOOP);
    }
    else {
        // Draw 2 triangles. Add the remaining 2 indices
        indices.push_back(0);
        indices.push_back(2);
    }

    duck->InitFromData(vertices, indices);
    return duck;
}