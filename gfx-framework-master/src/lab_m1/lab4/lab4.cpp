#include "lab_m1/lab4/lab4.h"

#include <vector>
#include <string>
#include <iostream>

#include "lab_m1/lab4/transform3D.h"

using namespace std;
using namespace m1;


/*
 *  To find out more about `FrameStart`, `Update`, `FrameEnd`
 *  and the order in which they are called, see `world.cpp`.
 */


Lab4::Lab4()
{
}


Lab4::~Lab4()
{
}


void Lab4::Init()
{
    polygonMode = GL_FILL;

    Mesh* mesh = new Mesh("box");
    mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "box.obj");
    meshes[mesh->GetMeshID()] = mesh;

    cx = 50;
    cy = 50;
    cz = 50;

    // Initialize tx, ty and tz (the translation steps)
    translateX = 0;
    translateY = 0;
    translateZ = 0;

    // Initialize sx, sy and sz (the scale factors)
    scaleX = 1;
    scaleY = 1;
    scaleZ = 1;

    // Initialize angular steps
    angularStepOX = 0;
    angularStepOY = 0;
    angularStepOZ = 0;

    angularStepOXSun = 0;
    angularStepOYSun = 0;
    angularStepOZSun = 0;

    angularStepOXSatelite = 0;
    angularStepOYSatelite = 0;
    angularStepOZSatelite = 0;
    angularStepOYSatelite2 = 0;

    angularStepOXPlanet = 0;
    angularStepOYPlanet = 0;
    angularStepOZPlanet = 0;
    angularStepOYPlanet2 = 0;

    // Sets the resolution of the small viewport
    glm::ivec2 resolution = window->GetResolution();
    miniViewportArea = ViewportArea(50, 50, resolution.x / 5.f, resolution.y / 5.f);

    floatX = miniViewportArea.x;
    floatY = miniViewportArea.y;
    floatWidth = miniViewportArea.width;
    floatHeight = miniViewportArea.height;
}


void Lab4::FrameStart()
{
    // Clears the color buffer (using the previously set color) and depth buffer
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Sets the screen area where to draw
    glm::ivec2 resolution = window->GetResolution();
    glViewport(0, 0, resolution.x, resolution.y);
}


void Lab4::RenderScene() {
    modelMatrix = glm::mat4(1);
    modelMatrix *= transform3D::Translate(-2.5f, 0.5f, -1.5f);
    modelMatrix *= transform3D::Translate(translateX, translateY, translateZ);
    RenderMesh(meshes["box"], shaders["VertexNormal"], modelMatrix);

    modelMatrix = glm::mat4(1);
    modelMatrix *= transform3D::Translate(0.0f, 0.5f, -1.5f);
    modelMatrix *= transform3D::Scale(scaleX, scaleY, scaleZ);
    RenderMesh(meshes["box"], shaders["Simple"], modelMatrix);

    modelMatrix = glm::mat4(1);
    modelMatrix *= transform3D::Translate(2.5f, 0.5f, -1.5f);
    modelMatrix *= transform3D::RotateOX(angularStepOX);
    modelMatrix *= transform3D::RotateOY(angularStepOY);
    modelMatrix *= transform3D::RotateOZ(angularStepOZ);
    RenderMesh(meshes["box"], shaders["VertexNormal"], modelMatrix);


    // sun
    modelMatrix = glm::mat4(1);
    modelMatrix *= transform3D::Translate(0, 0, -20);
    modelMatrix *= transform3D::Scale(4, 4, 4);
    modelMatrix *= transform3D::RotateOX(angularStepOXSun);
    modelMatrix *= transform3D::RotateOY(angularStepOYSun);
    modelMatrix *= transform3D::RotateOZ(angularStepOZSun);
    RenderMesh(meshes["box"], shaders["VertexNormal"], modelMatrix);


    // planet
    //modelMatrix = glm::mat4(1);
    //// modelMatrix *= transform3D::Translate(0, 0, -10);
    //modelMatrix *= transform3D::Scale(2, 2, 2);
    //modelMatrix *= transform3D::RotateOX(angularStepOXPlanet);
    //modelMatrix *= transform3D::RotateOY(angularStepOYPlanet);
    //// modelMatrix *= transform3D::RotateOZ(angularStepOZPlanet);
    //modelMatrix *= transform3D::Translate(0, 0, -10);
    //modelMatrix *= transform3D::RotateOY(angularStepOYPlanet2);

    modelMatrix *= transform3D::RotateOY(angularStepOYPlanet);
    modelMatrix *= transform3D::Scale(2, 2, 2);
    modelMatrix *= transform3D::Translate(0, 0, -10);
   //  modelMatrix *= transform3D::Translate(0, 0, -20) * transform3D::RotateOY(angularStepOYPlanet) * transform3D::Translate(0, 0, 20);
    modelMatrix *= transform3D::RotateOY(angularStepOYPlanet2);
    RenderMesh(meshes["box"], shaders["VertexNormal"], modelMatrix);

    // satellite
   modelMatrix *= transform3D::RotateOY(angularStepOYSatelite);
   modelMatrix *= transform3D::Translate(0, 0, -5);
   modelMatrix *= transform3D::RotateOY(angularStepOYSatelite2);
    RenderMesh(meshes["box"], shaders["VertexNormal"], modelMatrix);
}

void Lab4::Update(float deltaTimeSeconds)
{
    glLineWidth(3);
    glPointSize(5);
    glPolygonMode(GL_FRONT_AND_BACK, polygonMode);

    RenderScene();
    DrawCoordinateSystem();

    glClear(GL_DEPTH_BUFFER_BIT);
    glViewport(miniViewportArea.x, miniViewportArea.y, miniViewportArea.width, miniViewportArea.height);

    // TODO(student): render the scene again, in the new viewport
    RenderScene();
    DrawCoordinateSystem();

    angularStepOYSun += deltaTimeSeconds * 0.3f;
    angularStepOYPlanet += deltaTimeSeconds * 0.8f;
    angularStepOYPlanet2 += deltaTimeSeconds * 0.8f;
    angularStepOYSatelite2 += deltaTimeSeconds;
    angularStepOYSatelite += deltaTimeSeconds;

    floatX = miniViewportArea.x;
    floatY = miniViewportArea.y;
    floatWidth = miniViewportArea.width;
    floatHeight = miniViewportArea.height;
}


void Lab4::FrameEnd()
{
    DrawCoordinateSystem();
}


/*
 *  These are callback functions. To find more about callbacks and
 *  how they behave, see `input_controller.h`.
 */


void Lab4::OnInputUpdate(float deltaTime, int mods)
{
    // TODO(student): Add transformation logic
    if (!window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT)) {
        // Translate first cube
        if (window->KeyHold(GLFW_KEY_W)) {
            translateZ -= deltaTime;
        }
        if (window->KeyHold(GLFW_KEY_A)) {
            translateX -= deltaTime;
        }
        if (window->KeyHold(GLFW_KEY_S)) {
            translateZ += deltaTime;
        }
        if (window->KeyHold(GLFW_KEY_D)) {
            translateX += deltaTime;
        }
        if (window->KeyHold(GLFW_KEY_R)) {
            translateY += deltaTime;
        }
        if (window->KeyHold(GLFW_KEY_F)) {
            translateY -= deltaTime;
        }

        // Scale second cube
        if (window->KeyHold(GLFW_KEY_1)) {
            scaleX += deltaTime;
            scaleY += deltaTime;
        }

        if (window->KeyHold(GLFW_KEY_2)) {
            scaleX -= deltaTime;
            scaleY -= deltaTime;
        }

        // Rotate third cube
        if (window->KeyHold(GLFW_KEY_3)) {
            angularStepOX -= deltaTime;
        }
        if (window->KeyHold(GLFW_KEY_4)) {

            angularStepOX += deltaTime;
        }
        if (window->KeyHold(GLFW_KEY_5)) {
            angularStepOY -= deltaTime;
        }
        if (window->KeyHold(GLFW_KEY_6)) {
            angularStepOY += deltaTime;
        }
        if (window->KeyHold(GLFW_KEY_7)) {
            angularStepOZ -= deltaTime;
        }
        if (window->KeyHold(GLFW_KEY_8)) {
            angularStepOZ += deltaTime;
        }

        // move viewport
        if (window->KeyHold(GLFW_KEY_I)) {
            floatY += deltaTime * 100;
            miniViewportArea.y = (int) floatY;
        }
        if (window->KeyHold(GLFW_KEY_J)) {
            floatX -= deltaTime * 100;
            miniViewportArea.y = (int)floatX;
        }
        if (window->KeyHold(GLFW_KEY_K)) {
            floatY -= deltaTime * 100;
            miniViewportArea.y = (int)floatY;
        }
        if (window->KeyHold(GLFW_KEY_L)) {
            floatX += deltaTime * 100;
            miniViewportArea.y = (int) floatX;
        }

        // scale viewport
        if (window->KeyHold(GLFW_KEY_U)) {
            floatWidth -= deltaTime * 100;
            floatHeight -= deltaTime * 100;
            miniViewportArea.width = (int) floatWidth;
            miniViewportArea.height = (int) floatHeight;
        }
        if (window->KeyHold(GLFW_KEY_O)) {
            floatWidth += deltaTime * 100;
            floatHeight += deltaTime * 100;
            miniViewportArea.width = (int) floatWidth;
            miniViewportArea.height = (int) floatHeight;
        }
    }
}


void Lab4::OnKeyPress(int key, int mods)
{
    // Add key press event
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
}


void Lab4::OnKeyRelease(int key, int mods)
{
    // Add key release event
}


void Lab4::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
    // Add mouse move event
}


void Lab4::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button press event
}


void Lab4::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button release event
}


void Lab4::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}


void Lab4::OnWindowResize(int width, int height)
{
}
