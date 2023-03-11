#include "lab_m1/lab3/lab3.h"

#include <vector>
#include <iostream>

#include "lab_m1/lab3/transform2D.h"
#include "lab_m1/lab3/object2D.h"

using namespace std;
using namespace m1;

#define M_PI 3.1415926535897932384626433832795f

/*
 *  To find out more about `FrameStart`, `Update`, `FrameEnd`
 *  and the order in which they are called, see `world.cpp`.
 */


Lab3::Lab3()
{
}


Lab3::~Lab3()
{
}


void Lab3::Init()
{
    glm::ivec2 resolution = window->GetResolution();
    auto camera = GetSceneCamera();
    camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0.01f, 400);
    camera->SetPosition(glm::vec3(0, 0, 50));
    camera->SetRotation(glm::vec3(0, 0, 0));
    camera->Update();
    GetCameraInput()->SetActive(false);

    glm::vec3 corner = glm::vec3(0, 0, 0);
    float squareSide = 100;
    ok = 0;
    nr_rotation = 0;
    first = 0;

    // TODO(student): Compute coordinates of a square's center, and store
    // then in the `cx` and `cy` class variables (see the header). Use
    // `corner` and `squareSide`. These two class variables will be used
    // in the `Update()` function. Think about it, why do you need them?
    cx = corner.x + squareSide / 2;
    cy = corner.y + squareSide / 2;

    cx2 = cx + 100; // (cx + 100)
    cy2 = cy + 100; // (cy + 100)

    // Initialize tx and ty (the translation steps)
    // translateX = 0;
    translateX = 0;
    translateY = 0;

    // translateX2 = 0;
    translateX2 = (-1) * cx - cx2;
    // translateY2 = 0;
    translateY2 = (-1) * cx;
    // Initialize sx and sy (the scale factors)
    scaleX = 1;
    scaleY = 1;

    // Initialize angularStep
    angularStep = 0;
    angularStep2 = 0;

    Mesh* square1 = object2D::CreateSquare("square1", corner, squareSide, glm::vec3(1, 0, 0), true);
    AddMeshToList(square1);

    Mesh* square2 = object2D::CreateSquare("square2", corner, squareSide, glm::vec3(0, 1, 0));
    AddMeshToList(square2);

    Mesh* square3 = object2D::CreateSquare("square3", corner, squareSide, glm::vec3(0, 0, 1));
    AddMeshToList(square3);

    Mesh* square4 = object2D::CreateSquare("square4", corner, squareSide, glm::vec3(1, 0, 1));
    AddMeshToList(square4);

    glm::ivec2 res = window->GetResolution();

    scale_up = 1;
    keep_translate = 1;
}


void Lab3::FrameStart()
{
    // Clears the color buffer (using the previously set color) and depth buffer
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::ivec2 resolution = window->GetResolution();
    // Sets the screen area where to draw
    glViewport(0, 0, resolution.x, resolution.y);
}


void Lab3::Update(float deltaTimeSeconds)
{
    // TODO(student): Update steps for translation, rotation and scale,
    // in order to create animations. Use the class variables in the
    // class header, and if you need more of them to complete the task,
    // add them over there!

    modelMatrix = glm::mat3(1);

    modelMatrix *= transform2D::Translate(50, 250);

    modelMatrix *= transform2D::Translate(translateX, translateY);

    /*if (keep_translate == 1) {
        if (translateX > 100 || translateY > 100) {
            keep_translate = 0;
        }
        else {
            translateX += deltaTimeSeconds * 100;
            translateY += deltaTimeSeconds * 100;
        }
    }

    if (keep_translate == 0) {
        if (translateX <= 0 && translateY <= 0) {
            keep_translate = 1;

            translateX += deltaTimeSeconds * 100;
            translateY += deltaTimeSeconds * 100;
        }
        else {
            translateX -= deltaTimeSeconds * 100;
            translateY -= deltaTimeSeconds * 100;
        }
    }*/

    if (keep_translate == 1) {
        if (translateX > 100) {
            keep_translate = 0;
        }
        else {
            translateX += deltaTimeSeconds * 100;
        }
    }

    if (keep_translate == 0) {
        if (translateX <= 0) {
            keep_translate = 1;

            translateX += deltaTimeSeconds * 100;
        }
        else {
            translateX -= deltaTimeSeconds * 100;
        }
    }

    // translateX += deltaTimeSeconds * 100;
    // translateY += deltaTimeSeconds * 100;

    // TODO(student): Create animations by multiplying the current
    // transform matrix with the matrices you just implemented.
    // Remember, the last matrix in the chain will take effect first!

    RenderMesh2D(meshes["square1"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(500, 250);

    modelMatrix *= transform2D::Translate(cx, cy) *
                transform2D::Scale(scaleX, scaleY) *
                transform2D::Translate((-1) * cx, (-1) * cy);
    // TODO(student): Create animations by multiplying the current
    // transform matrix with the matrices you just implemented
    // Remember, the last matrix in the chain will take effect first!

    if (scale_up == 1) {
        if (scaleX > 4 || scaleY > 4) {
            scale_up = 0;
        }
        else {
            scaleX += deltaTimeSeconds;
            scaleY += deltaTimeSeconds;
        }
    }

    if (scale_up == 0) {
        if (scaleX <= 0 && scaleY <= 0) {
            scale_up = 1;
            scaleX += deltaTimeSeconds;
            scaleY += deltaTimeSeconds;
        }
        else {
            scaleX -= deltaTimeSeconds;
            scaleY -= deltaTimeSeconds;
        }
    }

    // scaleX += deltaTimeSeconds;
    // scaleY += deltaTimeSeconds;

    RenderMesh2D(meshes["square2"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(800, 250);
    modelMatrix *= transform2D::Translate(cx, cy) *
        transform2D::Rotate(angularStep) *
        transform2D::Translate((-1) * cx, (-1) * cy);

    // TODO(student): Create animations by multiplying the current
    // transform matrix with the matrices you just implemented
    // Remember, the last matrix in the chain will take effect first!

    angularStep -= deltaTimeSeconds;

    RenderMesh2D(meshes["square3"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);

    if (translateX2 <= (cx2 + 50) * (nr_rotation - 1) && translateY2 <= 0 && first == 1) {
        translateX2 = (cx2 + 50) * (nr_rotation);
        translateY2 = cy2 * 1;
    }

    modelMatrix *= transform2D::Translate(translateX2, translateY2);

    // TODO(student): Create animations by multiplying the current
    // transform matrix with the matrices you just implemented
    // Remember, the last matrix in the chain will take effect first!

    // (-3) * M_PI / 2

   // if (ok == 1) {
   //     translateY2 -= deltaTimeSeconds * 100;
   // }

   //if (translateY2 < 0) {
   //     ok = 0;
   //    // translateY2 = 0;
   //    first = 0;
   //    
   // }

   // if (angularStep2 < (-1) * M_PI) {
   //     angularStep2 = 0;
   //     nr_rotation++;
   //     first = 1;

   //     ok = 1;
   //     translateX2 = (cx2 + 50) * (nr_rotation);
   //     translateY2 = cy2 * 1;
   //     // translateY2 = 350;

   // }
   // else if (ok != 1) {
   //     modelMatrix *= transform2D::Translate(cx2, cy2) *
   //         transform2D::Rotate(angularStep2) *
   //         transform2D::Translate((-1) * cx2, (-1) * cy2);

   //     angularStep2 -= deltaTimeSeconds;
   // }

    if (angularStep2 < (-1) * M_PI) {
        angularStep2 = 0;
        nr_rotation++;

        translateX2 = (cx2 + 50) * (nr_rotation);
        translateY2 = 0;
        // translateY2 = 350;

    }
    else {
        modelMatrix *= transform2D::Translate(cx2, cy2) *
            transform2D::Rotate(angularStep2) *
            transform2D::Translate((-1) * cx2, (-1) * cy2);

        angularStep2 -= deltaTimeSeconds;
    }

    RenderMesh2D(meshes["square4"], shaders["VertexColor"], modelMatrix);
}


void Lab3::FrameEnd()
{
}


/*
 *  These are callback functions. To find more about callbacks and
 *  how they behave, see `input_controller.h`.
 */


void Lab3::OnInputUpdate(float deltaTime, int mods)
{
}


void Lab3::OnKeyPress(int key, int mods)
{
    // Add key press event
}


void Lab3::OnKeyRelease(int key, int mods)
{
    // Add key release event
}


void Lab3::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
    // Add mouse move event
}


void Lab3::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button press event
}


void Lab3::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button release event
}


void Lab3::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}


void Lab3::OnWindowResize(int width, int height)
{
}
