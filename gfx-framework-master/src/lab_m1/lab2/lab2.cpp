#include "lab_m1/lab2/lab2.h"

#include <vector>
#include <iostream>

#include "core/engine.h"
#include "utils/gl_utils.h"

#define M_PI 3.1415926535897932384626433832795

using namespace std;
using namespace m1;


/*
 *  To find out more about `FrameStart`, `Update`, `FrameEnd`
 *  and the order in which they are called, see `world.cpp`.
 */


Lab2::Lab2()
{
}


Lab2::~Lab2()
{
}

glm::vec3 Lab2::CalculateCoordinates(int basic_angle, int &current_angle, float r) {
    float d_pi = 2 * M_PI;
    float x = r * cos(current_angle * M_PI / 180);
    float y = r * sin(current_angle * M_PI / 180);

    // float x = r * 0.86f;
    // float y = r * 0.5f;

    current_angle += basic_angle;
    cout << current_angle;

    return glm::vec3(x, y, 0);
}

glm::vec3 Lab2::RandomRGB() {
    float Red = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
    float Green = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
    float Blue = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);

    return glm::vec3(Red, Green, Blue);
}

void Lab2::Init()
{
    cullFace = GL_BACK;
    polygonMode = GL_FILL;

    // Load a mesh from file into GPU memory
    {
        Mesh* mesh = new Mesh("box");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "box.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }

    // Create a mesh box using custom data
    {
        vector<VertexFormat> vertices
        {
            VertexFormat(glm::vec3(-1, -1, 1), RandomRGB()),
            // TODO(student): Complete the vertices data for the cube mesh
            VertexFormat(glm::vec3(3, -1, 1), RandomRGB()),
            VertexFormat(glm::vec3(-1, 3, 1), RandomRGB()),
            VertexFormat(glm::vec3(3, 3, 1), RandomRGB()),
            VertexFormat(glm::vec3(-1, -1, 5), RandomRGB()),
            VertexFormat(glm::vec3(3, -1, 5), RandomRGB()),
            VertexFormat(glm::vec3(-1, 3,  5), RandomRGB()),
            VertexFormat(glm::vec3(3, 3,  5), RandomRGB())
        };

        vector<unsigned int> indices =
        {
            0, 1, 2,    // indices for first triangle
            1, 3, 2,    // indices for second triangle
            // TODO(student): Complete indices data for the cube mesh
            2, 3, 7,
            2, 7, 6,
            1, 7, 3,
            1, 5, 7,
            6, 7, 4,
            7, 5, 4,
            0, 4, 1,
            1, 4, 5,
            2, 6, 4,
            0, 2, 4
        };

        vector<VertexFormat> vertices_tetra
        {
            VertexFormat(glm::vec3(0, 0, 0), RandomRGB()),
            VertexFormat(glm::vec3(3, 5.19, 0), RandomRGB()),
            VertexFormat(glm::vec3(6, 0, 0), RandomRGB()),
            VertexFormat(glm::vec3(3, 0, 5.19f), RandomRGB())
        };

        vector<unsigned int> indices_tetra =
        {
            1, 0, 2,   // indices for first triangle
            1, 3, 0,    // indices for second triangle
            3, 2, 0,
            1, 2, 3
        };

        vector<VertexFormat> vertices_tetra_2
        {
            VertexFormat(glm::vec3(0, 0, 0), glm::vec3(1, 1, 0)),      // 0
            VertexFormat(glm::vec3(3, 5.19, 0), glm::vec3(1, 0, 1)),   // 1
            VertexFormat(glm::vec3(6, 0, 0), glm::vec3(1, 1, 0)),      // 2
            VertexFormat(glm::vec3(3, 0, 5.19f), glm::vec3(0, 1, 1)),  // 3
            VertexFormat(glm::vec3(0, 0, 0), glm::vec3(1, 0, 1)),      // 4
            VertexFormat(glm::vec3(3, 5.19, 0), glm::vec3(0, 1, 1)),   // 5
            VertexFormat(glm::vec3(6, 0, 0), glm::vec3(1, 0, 0)),      // 6
            VertexFormat(glm::vec3(3, 0, 5.19f), glm::vec3(1, 1, 0)),  // 7
            VertexFormat(glm::vec3(0, 0, 0), glm::vec3(0, 1, 1)),      // 8
            VertexFormat(glm::vec3(3, 5.19, 0), glm::vec3(1, 0, 0)),   // 9
            VertexFormat(glm::vec3(6, 0, 0), glm::vec3(1, 0, 1)),      // 10
            VertexFormat(glm::vec3(3, 0, 5.19f), glm::vec3(1, 0, 0))  // 11

        };

        vector<unsigned int> indices_tetra_2 =
        {
            //1, 0, 2,   // indices for first triangle
            //1, 3, 0,    // indices for second triangle
            //3, 2, 0,
            //1, 2, 3,

            //5, 4, 6,
            //5, 7, 4,
            //7, 6, 4,
            //5, 6, 7,
            // 
            //9, 8, 10,
            //9, 11, 8,     
            //11, 10, 8,
            //9, 10, 11

            1, 4, 10,
            5, 3, 8,
            7, 2, 0,
            9, 6, 11

        };

        int angle = 30;
        int current_angle = 0;
        float r = 5;

        vector<VertexFormat> vertices_circle
        {
            VertexFormat(glm::vec3(0, 0, 0), glm::vec3(1, 0, 1)), // 0
            VertexFormat(CalculateCoordinates(angle, current_angle, r), glm::vec3(1, 0, 1)), // 1
            VertexFormat(CalculateCoordinates(angle, current_angle, r), glm::vec3(1, 0, 1)), // 2
            VertexFormat(CalculateCoordinates(angle, current_angle, r), glm::vec3(1, 0, 1)), // 3
            VertexFormat(CalculateCoordinates(angle, current_angle, r), glm::vec3(1, 0, 1)), // 4
            VertexFormat(CalculateCoordinates(angle, current_angle, r), glm::vec3(1, 0, 1)), // 5
            VertexFormat(CalculateCoordinates(angle, current_angle, r), glm::vec3(1, 0, 1)), // 6
            VertexFormat(CalculateCoordinates(angle, current_angle, r), glm::vec3(1, 0, 1)), // 7
            VertexFormat(CalculateCoordinates(angle, current_angle, r), glm::vec3(1, 0, 1)), // 8
            VertexFormat(CalculateCoordinates(angle, current_angle, r), glm::vec3(1, 0, 1)), // 9
            VertexFormat(CalculateCoordinates(angle, current_angle, r), glm::vec3(1, 0, 1)), // 10
            VertexFormat(CalculateCoordinates(angle, current_angle, r), glm::vec3(1, 0, 1)), // 11
            VertexFormat(CalculateCoordinates(angle, current_angle, r), glm::vec3(1, 0, 1)), // 12
        };

        vector<unsigned int> indices_circle =
        {
            1, 0, 2,    // indices for first triangle
            2, 0, 3,    // indices for second triangle
            3, 0, 4,
            4, 0, 5,
            5, 0, 6,
            6, 0, 7,
            7, 0, 8,
            8, 0, 9,
            9, 0, 10,
            10, 0, 11,
            11, 0, 12,
            12, 0, 1
        };

        vector<VertexFormat> vertices_square
        {
            VertexFormat(glm::vec3(0, 5, 0), RandomRGB()),
            VertexFormat(glm::vec3(5, 5, 0), RandomRGB()),
            VertexFormat(glm::vec3(5, 0, 0), RandomRGB()),
            VertexFormat(glm::vec3(0, 0, 0), RandomRGB())
        };

        vector<unsigned int> indices_square =
        {
            0, 1, 2,    // indices for first triangle
            0, 3, 2,    // indices for second triangle
        };

        meshes["cube_A"] = new Mesh("generated cube 1");
        meshes["cube_A"]->InitFromData(vertices, indices);

        // Actually create the mesh from the data
        CreateMesh("cube_B", vertices, indices);

        // TODO(student): Create a tetrahedron mesh. You can create it with
        // only 4 vertices, or you can choose the harder route and create it
        // with 12 vertices. Think about it, why would you want that, and how
        // would you do it? After all, a tetrahedron has only 4 vertices
        // by definition!
        CreateMesh("tetrahedron", vertices_tetra, indices_tetra);

        // TODO(student): Create a square using two triangles with
        // opposing vertex orientations.
        CreateMesh("square", vertices_square, indices_square);

        CreateMesh("tetrahedron_2", vertices_tetra_2, indices_tetra_2);

        CreateMesh("circle", vertices_circle, indices_circle);
    }
}


void Lab2::CreateMesh(const char *name, const std::vector<VertexFormat> &vertices, const std::vector<unsigned int> &indices)
{
    unsigned int VAO = 0;
    // TODO(student): Create the VAO and bind it
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    unsigned int VBO = 0;
    // TODO(student): Create the VBO and bind it
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    // TODO(student): Send vertices data into the VBO buffer
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * vertices.size(), &vertices[0], GL_STATIC_DRAW);

    unsigned int IBO = 0;
    // TODO(student): Create the IBO and bind it
    glGenBuffers(1, &IBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);

    // TODO(student): Send indices data into the IBO buffer
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * indices.size(), &indices[0], GL_STATIC_DRAW);

    // ========================================================================
    // This section demonstrates how the GPU vertex shader program
    // receives data. It will be learned later, when GLSL shaders will be
    // introduced. For the moment, just think that each property value from
    // our vertex format needs to be sent to a certain channel, in order to
    // know how to receive it in the GLSL vertex shader.

    // Set vertex position attribute
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), 0);

    // Set vertex normal attribute
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(sizeof(glm::vec3)));

    // Set texture coordinate attribute
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(2 * sizeof(glm::vec3)));

    // Set vertex color attribute
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(2 * sizeof(glm::vec3) + sizeof(glm::vec2)));
    // ========================================================================

    // TODO(student): Unbind the VAO
    glBindVertexArray(0);

    // Check for OpenGL errors
    if (GetOpenGLError() == GL_INVALID_OPERATION)
    {
        cout << "\t[NOTE] : For students : DON'T PANIC! This error should go away when completing the tasks." << std::endl;
        cout << "\t[NOTE] : For developers : This happens because OpenGL core spec >=3.1 forbids null VAOs." << std::endl;
    }

    // Mesh information is saved into a Mesh object
    meshes[name] = new Mesh(name);
    meshes[name]->InitFromBuffer(VAO, static_cast<unsigned int>(indices.size()));
}


void Lab2::FrameStart()
{
    // Clears the color buffer (using the previously set color) and depth buffer
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::ivec2 resolution = window->GetResolution();

    // Sets the screen area where to draw
    glViewport(0, 0, resolution.x, resolution.y);
}


void Lab2::Update(float deltaTimeSeconds)
{
    glLineWidth(3);
    glPointSize(5);
    glPolygonMode(GL_FRONT_AND_BACK, polygonMode);

    // TODO(student): Enable face culling
    glEnable(GL_CULL_FACE);

    // TODO(student): Set face custom culling. Use the `cullFace` variable.
    glCullFace(cullFace);
    // glFrontFace(GL_CW);

    // Render an object using face normals for color
    RenderMesh(meshes["box"], shaders["VertexNormal"], glm::vec3(0, 0.5f, -1.5f), glm::vec3(0.75f));

    // Render an object using colors from vertex
    RenderMesh(meshes["cube_A"], shaders["VertexColor"], glm::vec3(-1.5f, 0.5f, 0), glm::vec3(0.25f));

    // TODO(student): Draw the mesh that was created with `CreateMesh()`
    RenderMesh(meshes["cube_B"], shaders["VertexColor"], glm::vec3(5, 0.49f, 1), glm::vec3(0.5f));

    // TODO(student): Draw the tetrahedron
    RenderMesh(meshes["tetrahedron"], shaders["VertexColor"], glm::vec3(0, 0, 0), glm::vec3(0.5f));

    // TODO(student): Draw the square
    RenderMesh(meshes["square"], shaders["VertexColor"], glm::vec3(0, 0, 6), glm::vec3(1));

    RenderMesh(meshes["tetrahedron_2"], shaders["VertexColor"], glm::vec3(-3, 0, -4), glm::vec3(0.5f));

    RenderMesh(meshes["circle"], shaders["VertexColor"], glm::vec3(-4, 0, -5), glm::vec3(1));

    // TODO(student): Disable face culling
    glDisable(GL_CULL_FACE);

}


void Lab2::FrameEnd()
{
    DrawCoordinateSystem();
}


/*
 *  These are callback functions. To find more about callbacks and
 *  how they behave, see `input_controller.h`.
 */


void Lab2::OnInputUpdate(float deltaTime, int mods)
{
}


void Lab2::OnKeyPress(int key, int mods)
{
    // TODO(student): Switch between GL_FRONT and GL_BACK culling.
    // Save the state in `cullFace` variable and apply it in the
    // `Update()` method, NOT here!

    if (key == GLFW_KEY_SPACE)
    {
        switch (polygonMode)
        {
        case GL_POINT:
            polygonMode = GL_FILL;
            break;
        case GL_LINE:
            polygonMode = GL_POINT;
            break;
        default:
            polygonMode = GL_LINE;
            break;
        }
    }

    if (key == GLFW_KEY_F2) {
        if (cullFace == GL_BACK) {
            cullFace = GL_FRONT;
        }
        else {
            cullFace = GL_BACK;
        }

    }
}


void Lab2::OnKeyRelease(int key, int mods)
{
    // Add key release event
}


void Lab2::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
    // Add mouse move event
}


void Lab2::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button press event
}


void Lab2::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button release event
}


void Lab2::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}


void Lab2::OnWindowResize(int width, int height)
{
}
