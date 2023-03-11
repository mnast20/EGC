#include "lab_m1/lab1/lab1.h"

#include <vector>
#include <iostream>

using namespace std;
using namespace m1;


/*
 *  To find out more about `FrameStart`, `Update`, `FrameEnd`
 *  and the order in which they are called, see `world.cpp`.
 */


Lab1::Lab1()
{
    // TODO(student): Never forget to initialize class variables!
    Red = 0;
    Green = 0;
    Blue = 0;

    primitives_name = "box";

    bunny_x = 2;
    bunny_y = 1.5f;
    bunny_z = 2;

    archer_x = 2.2;
    archer_y = 1.9f;
    archer_z = 2;

    space = 0;

    // Red = 250;
    // Green = 218;
    // Blue = 221;

    // Red = 164;
    // Green = 219;
    // Blue = 232;

    // Red = 4;
    // Green = 215;
    // Blue = 215;

    // Red = 255;
    // Green = 0;
    // Blue = 0;

    // Red = 3;
    // Green = 159;
    // Blue = 159;

}


Lab1::~Lab1()
{
}


void Lab1::Init()
{
    // Load a mesh from file into GPU memory. We only need to do it once,
    // no matter how many times we want to draw this mesh.
    {
        Mesh* mesh = new Mesh("box");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "box.obj");
        meshes[mesh->GetMeshID()] = mesh;

    // TODO(student): Load some more meshes. The value of RESOURCE_PATH::MODELS
    // is actually a path on disk, go there and you will find more meshes.

        Mesh* mesh_sphere = new Mesh("sphere");
        mesh_sphere->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "sphere.obj");
        meshes[mesh_sphere->GetMeshID()] = mesh_sphere;

        Mesh* mesh_quad = new Mesh("quad");
        mesh_quad->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "quad.obj");
        meshes[mesh_quad->GetMeshID()] = mesh_quad;

        Mesh* mesh_teapot = new Mesh("teapot");
        mesh_teapot->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "teapot.obj");
        meshes[mesh_teapot->GetMeshID()] = mesh_teapot;

        Mesh* mesh_screen_quad = new Mesh("screen_quad");
        mesh_screen_quad->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "screen_quad.obj");
        meshes[mesh_screen_quad->GetMeshID()] = mesh_screen_quad;

        Mesh* mesh_plane = new Mesh("plane50");
        mesh_plane->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "plane50.obj");
        meshes[mesh_plane->GetMeshID()] = mesh_plane;

        Mesh* mesh_bunny = new Mesh("bunny");
        mesh_bunny->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "animals"), "bunny.obj");
        meshes[mesh_bunny->GetMeshID()] = mesh_bunny;

        Mesh* mesh_wall = new Mesh("concrete_wall");
        mesh_wall->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "props"), "concrete_wall.obj");
        meshes[mesh_wall->GetMeshID()] = mesh_wall;

        Mesh* mesh_bamboo = new Mesh("bamboo");
        mesh_bamboo->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "vegetation/bamboo"), "bamboo.obj");
        meshes[mesh_bamboo->GetMeshID()] = mesh_bamboo;

        Mesh* mesh_archer = new Mesh("archer");
        mesh_archer->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "characters/archer"), "archer.fbx");
        meshes[mesh_archer->GetMeshID()] = mesh_archer;
    }

}


void Lab1::FrameStart()
{
}


void Lab1::Update(float deltaTimeSeconds)
{
    glm::ivec2 resolution = window->props.resolution;

    // Sets the clear color for the color buffer

    // TODO(student): Generalize the arguments of `glClearColor`.
    // You can, for example, declare three variables in the class header,
    // that will store the color components (red, green, blue).
    // glClearColor(0, 0, 0, 1);

    glClearColor(Red, Green, Blue, 1);

    // Clears the color buffer (using the previously set color) and depth buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Sets the screen area where to draw
    glViewport(0, 0, resolution.x, resolution.y);

    // Render the object
    RenderMesh(meshes[primitives_name], glm::vec3(1, 0.5f, 0), glm::vec3(0.5f));

    // Render the object again but with different properties
    RenderMesh(meshes["box"], glm::vec3(-1, 0.5f, 0));

    // TODO(student): We need to render (a.k.a. draw) the mesh that
    // was previously loaded. We do this using `RenderMesh`. Check the
    // signature of this function to see the meaning of its parameters.
    // You can draw the same mesh any number of times.

    RenderMesh(meshes["bunny"], glm::vec3(bunny_x, bunny_y, bunny_z), glm::vec3(0.1f));
    RenderMesh(meshes["concrete_wall"], glm::vec3(-2, 0, -5), glm::vec3(0.2f));
    RenderMesh(meshes["bamboo"], glm::vec3(-1, 2.8f, -1), glm::vec3(0.7f));
    RenderMesh(meshes["archer"], glm::vec3(archer_x, archer_y, archer_z), glm::vec3(0.02f));
}


void Lab1::FrameEnd()
{
    DrawCoordinateSystem();
}


/*
 *  These are callback functions. To find more about callbacks and
 *  how they behave, see `input_controller.h`.
 */


void Lab1::OnInputUpdate(float deltaTime, int mods)
{
    // Treat continuous update based on input

    // TODO(student): Add some key hold events that will let you move
    // a mesh instance on all three axes. You will also need to
    // generalize the position used by `RenderMesh`.
    
    float speed = 6;
    float gravitation = 10;

    if (!window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT)) {
        if (window->KeyHold(GLFW_KEY_D)) {
            bunny_x += deltaTime * speed;
            archer_x += deltaTime * speed;
        }
        else if (window->KeyHold(GLFW_KEY_A)) {
            bunny_x -= deltaTime * speed;
            archer_x -= deltaTime * speed;
        }
        else if (window->KeyHold(GLFW_KEY_E)) {
            bunny_y += deltaTime * speed;
            archer_y += deltaTime * speed;
        }
        else if (window->KeyHold(GLFW_KEY_Q)) {
            bunny_y -= deltaTime * speed;
            archer_y -= deltaTime * speed;
        }
        else if (window->KeyHold(GLFW_KEY_W)) {
            bunny_z -= deltaTime * speed;
            archer_z -= deltaTime * speed;
        }
        else if (window->KeyHold(GLFW_KEY_S)) {
            bunny_z += deltaTime * speed;
            archer_z += deltaTime * speed;
        }
        else {
            if (window->KeyHold(GLFW_KEY_SPACE)) {
                bunny_y += 0.5f * gravitation * deltaTime * deltaTime;
                archer_y += 0.5f * gravitation * deltaTime * deltaTime;
            }

            space = 1;
        }
    }
}


void Lab1::OnKeyPress(int key, int mods)
{
    // Add key press event
    if (key == GLFW_KEY_F) {
        // TODO(student): Change the values of the color components.

        Red = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
        Green = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
        Blue = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);

        /*Red = (rand() > RAND_MAX / 2) ? 255 : 0;
        Green = (rand() > RAND_MAX / 2) ? 255 : 0;
        Blue = (rand() > RAND_MAX / 2) ? 255 : 0;*/
        
        /*
        if (Red == 250) {
            Green = 218;
            Blue = 221;
        }
        else {
            Green = 219;
            Blue = 232;
        }
        */
    }

    // TODO(student): Add a key press event that will let you cycle
    // through at least two meshes, rendered at the same position.
    // You will also need to generalize the mesh name used by `RenderMesh`.
    if (key == GLFW_KEY_C) {
        if (strcmp(primitives_name, "box") == 0) {
            primitives_name = "sphere";
        }
        else if (strcmp(primitives_name, "sphere") == 0) {
            primitives_name = "teapot";
        }
        else if (strcmp(primitives_name, "teapot") == 0) {
            primitives_name = "quad";
        }
        else if (strcmp(primitives_name, "quad") == 0) {
            primitives_name = "screen_quad";
        }
        else if (strcmp(primitives_name, "screen_quad") == 0) {
            primitives_name = "plane50";
        }
        else if (strcmp(primitives_name, "plane50") == 0) {
            primitives_name = "box";
        }
    }


}


void Lab1::OnKeyRelease(int key, int mods)
{
    // Add key release event
}


void Lab1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
    // Add mouse move event
}


void Lab1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button press event
}


void Lab1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button release event
}


void Lab1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
    // Treat mouse scroll event
}


void Lab1::OnWindowResize(int width, int height)
{
    // Treat window resize event
}
