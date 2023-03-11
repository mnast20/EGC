#include "lab_m1/Tema1/Tema1.h"

#include <vector>
#include <iostream>
#include <windows.h>
#include <mmsystem.h>

#include "lab_m1/Tema1/transformations2D.h"
#include "lab_m1/Tema1/createObject2D.h"
#pragma comment(lib, "winmm.lib")

using namespace std;
using namespace m1;

/*
 *  To find out more about `FrameStart`, `Update`, `FrameEnd`
 *  and the order in which they are called, see `world.cpp`.
 */


Tema1::Tema1()
{
}


Tema1::~Tema1()
{
}

float Tema1::RandomCoordinate(glm::ivec2 resolution, int squareSide) {
    float random = ((float)rand()) / (float)RAND_MAX;
    float r = random * (window->GetResolution().x - squareSide);

    return r;
}

int Tema1::RandomDirection() {
    int r = (rand() > RAND_MAX / 2) ? 1 : 0;

    return r;
}

int Tema1::RandomAngle() {
    int randNum = rand() % (65 - 25 + 1) + 25;

    return randNum;
}

void Tema1::Init()
{
    glm::ivec2 resolution = window->GetResolution();
    auto camera = GetSceneCamera();
    camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0.01f, 400);
    camera->SetPosition(glm::vec3(0, 0, 50));
    camera->SetRotation(glm::vec3(0, 0, 0));
    camera->Update();
    GetCameraInput()->SetActive(false);

    glm::vec3 corner = glm::vec3(0, 0, 0);
    squareSide = 180;

    // Initialize tx and ty (the translation steps)
    translateX = 0;
    translateY = 0;

    used_lives = 0;
    used_bullets = 0;
    start_duck = 1;
    escape = 0;
    dead_duck = 0;
    randomCoordinate = 0;
    move_right = 0;

    translateXCloud1 = 0;
    translateXCloud2 = 420;
    translateXCloud3 = 800;

    startingResolutionX = (float) resolution.x;
    startingResolutionY = (float)resolution.y;

    speed = originalSpeed;

    Mesh* earth = createObject2D::CreateRectangle("earth", 100, 1920, 0, glm::vec3(17.0f, 115.0f, 58.0f) / 255.0f, true);
    AddMeshToList(earth);

    Mesh* duck_square = createObject2D::CreateSquare("duck_square", corner, (float) squareSide, glm::vec3(0, 0, 1));
    AddMeshToList(duck_square);

    Mesh* life = createObject2D::CreateCircle("life", 20, 0, glm::vec3(1, 0, 0), true);
    AddMeshToList(life);

    Mesh* bullet = createObject2D::CreateRectangle("bullet", 40, 20, 0, glm::vec3(0, 1, 0), true);
    AddMeshToList(bullet);

    Mesh* cloud = createObject2D::CreateCloud("cloud", -10, true);
    AddMeshToList(cloud);

    Mesh* rectangle1 = createObject2D::CreateRectangle("rectangle", 126, 300, 0, glm::vec3(1, 0, 0), false);
    AddMeshToList(rectangle1);

    Mesh* rectangle = createObject2D::CreateRectangle("chooseRectangle", 1, 1, 0, glm::vec3(1, 0, 0), false);
    AddMeshToList(rectangle);

    Mesh* duck = createObject2D::CreateDuck("duck", true);
    AddMeshToList(duck);

    Mesh* flyingDuck = createObject2D::CreateFlyingDuck("flyingDuck", true);
    AddMeshToList(flyingDuck);

    Mesh* wing = createObject2D::CreateWing("wing", true);
    AddMeshToList(wing);

    Mesh* scoreRectangle = createObject2D::CreateRectangle("scoreRectangle", resolution.y * 0.7f, 41, 0, glm::vec3(1, 1, 1), false);
    AddMeshToList(scoreRectangle);

    Mesh* scoreBar = createObject2D::CreateRectangle("scoreBar", 1, 40, 0, glm::vec3(30.0f, 144.0f, 255.0f) / 255.0f, true);
    AddMeshToList(scoreBar);

    Mesh* aimer = createObject2D::CreateRectangle("aimer", 30, 7, 10, glm::vec3(119.0f, 136.0f, 153.0f) / 255.0f, true);
    AddMeshToList(aimer);

    Mesh* aimerCircle = createObject2D::CreateCircle("aimercircle", 20, 10, glm::vec3(119.0f, 136.0f, 153.0f) / 255.0f, false);
    AddMeshToList(aimerCircle);

    // load fonts
    textRenderTitle.Load(window->props.selfDir + "\\src\\lab_m1\\Tema1\\Fonts\\Fluo Gums.ttf", 128);
    textRenderPlay.Load(window->props.selfDir + "\\src\\lab_m1\\Tema1\\Fonts\\Hack-Bold.ttf", 128);
    textRenderVictory.Load(window->props.selfDir + "\\src\\lab_m1\\Tema1\\Fonts\\americankestral1_2.ttf", 128);
    textRenderFail.Load(window->props.selfDir + "\\src\\lab_m1\\Tema1\\Fonts\\Bad Signal.otf", 128);
    textRenderDuck.Load(window->props.selfDir + "\\src\\lab_m1\\Tema1\\Fonts\\Duck.ttf", 128);

    // load bush mesh
    Mesh* bushMesh = new Mesh("bush");
    bushMesh->LoadMesh(window->props.selfDir + "\\src\\lab_m1\\Tema1\\Textures\\", "Bush.fbx");
    meshes[bushMesh->GetMeshID()] = bushMesh;

    // load grass mesh
    Mesh* grassMesh = new Mesh("grass");
    grassMesh->LoadMesh(window->props.selfDir + "\\src\\lab_m1\\Tema1\\Textures\\", "Grass.fbx");
    meshes[grassMesh->GetMeshID()] = grassMesh;

    activeTime = 0;
}


void Tema1::FrameStart()
{
    // Clears the color buffer (using the previously set color) and depth buffer
    glClearColor(skyRed, skyGreen, skyBlue, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::ivec2 resolution = window->GetResolution();

    GetSceneCamera()->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0.01f, 400);

    // Sets the screen area where to draw
    glViewport(0, 0, resolution.x, resolution.y);
}


void Tema1::Update(float deltaTimeSeconds)
{
    glm::ivec2 resolution = window->GetResolution();

    modelMatrix = glm::mat3(1);
    modelMatrix *= transformations2D::Translate(0, 0);

    // render earth
    RenderMesh2D(meshes["earth"], shaders["VertexColor"], modelMatrix);

    // render grass
    RenderMesh(meshes["grass"], glm::vec3(0, 0, 1), glm::vec3(200.0f));
    RenderMesh(meshes["grass"], glm::vec3(200, 0, 1), glm::vec3(200.0f));
    RenderMesh(meshes["grass"], glm::vec3(400, 0, 1), glm::vec3(200.0f));
    RenderMesh(meshes["grass"], glm::vec3(600, 0, 1), glm::vec3(200.0f));
    RenderMesh(meshes["grass"], glm::vec3(800, 0, 1), glm::vec3(200.0f));
    RenderMesh(meshes["grass"], glm::vec3(1000, 0, 1), glm::vec3(200.0f));
    RenderMesh(meshes["grass"], glm::vec3(1200, 0, 1), glm::vec3(200.0f));
    RenderMesh(meshes["grass"], glm::vec3(1400, 0, 1), glm::vec3(200.0f));
    RenderMesh(meshes["grass"], glm::vec3(1600, 0, 1), glm::vec3(200.0f));
    RenderMesh(meshes["grass"], glm::vec3(1800, 0, 1), glm::vec3(200.0f));
    RenderMesh(meshes["grass"], glm::vec3(2000, 0, 1), glm::vec3(200.0f));

    // game won
    if (!win && startGame && score >= maxScore && !dead_duck) {
        win = 1;
        playVictorySound = 1;
    }

    if (!startGame) {
        // render title and play button
        textRenderTitle.RenderText("DUCK HUNT", startingResolutionX / 2 - 450, 150, 0.8f, glm::vec3(0.8549f, 0.439f, 0.8392f));
        textRenderPlay.RenderText("Play", startingResolutionX / 2 - 149, 400, 1.0f, glm::vec3(0.1803f, 0.545f, 0.3411f));
        textRenderPlay.RenderText("Click Play to start the game", 325, startingResolutionY - 150, 0.3f, glm::vec3(1, 1, 1));

        float scaleFactorX = window->GetResolution().x / startingResolutionX;
        float scaleFactorY = window->GetResolution().y / startingResolutionY;

        modelMatrix = glm::mat3(1);
        modelMatrix *= transformations2D::Translate((startingResolutionX / 2 - 142) * scaleFactorX, (startingResolutionY - 520) * scaleFactorY);
        modelMatrix *= transformations2D::Scale(scaleFactorX, scaleFactorY);

        if (showSquare) {
            RenderMesh2D(meshes["rectangle"], shaders["VertexColor"], modelMatrix);
        }

        // render duck
        modelMatrix = glm::mat3(1);
        modelMatrix *= transformations2D::Translate((float)(resolution.x - 200), 192.0f);
        modelMatrix *= transformations2D::Scale(22.0f, 22.0f);

        RenderMesh2D(meshes["duck"], shaders["VertexColor"], modelMatrix);

        modelMatrix = glm::mat3(1);
        modelMatrix *= transformations2D::Translate(-4, 1);
        modelMatrix *= transformations2D::Translate((float)(resolution.x - 200), 192.0f);
        modelMatrix *= transformations2D::Scale(22.0f, 22.0f);

        RenderMesh2D(meshes["wing"], shaders["VertexColor"], modelMatrix);
    }
    else if (startGame && used_lives < 3 && !win) {
        skyRed = 0.678f;
        skyGreen = 0.847f;
        skyBlue = 0.902f;

        // render aimer
        modelMatrix = glm::mat3(1);
        modelMatrix *= transformations2D::Translate(mouseCoordinateX - 6, window->GetResolution().y - mouseCoordinateY);
        modelMatrix *= transformations2D::Rotate(RADIANS(90));

        RenderMesh2D(meshes["aimer"], shaders["VertexColor"], modelMatrix);

        modelMatrix = glm::mat3(1);
        modelMatrix *= transformations2D::Translate(mouseCoordinateX + 43, window->GetResolution().y - mouseCoordinateY);
        modelMatrix *= transformations2D::Rotate(RADIANS(90));

        RenderMesh2D(meshes["aimer"], shaders["VertexColor"], modelMatrix);

        modelMatrix = glm::mat3(1);
        modelMatrix *= transformations2D::Translate(mouseCoordinateX, window->GetResolution().y - mouseCoordinateY + 15);

        RenderMesh2D(meshes["aimer"], shaders["VertexColor"], modelMatrix);

        modelMatrix = glm::mat3(1);
        modelMatrix *= transformations2D::Translate(mouseCoordinateX, window->GetResolution().y - mouseCoordinateY - 35);

        RenderMesh2D(meshes["aimer"], shaders["VertexColor"], modelMatrix);

        if (wingAngle > 80) {
            wingAngle = 0;
        }

        // render score text
        auto str = "Score: " + std::to_string(score);
        textRenderPlay.RenderText(str, startingResolutionX / 2.32f, startingResolutionY * 0.03f, 0.3f, glm::vec3(1, 1, 1));

        // render score and rectangle
        modelMatrix = glm::mat3(1);
        modelMatrix *= transformations2D::Translate(window->GetResolution().x * 0.96f, window->GetResolution().y * 0.17f);

        RenderMesh2D(meshes["scoreRectangle"], shaders["VertexColor"], modelMatrix);

        if (score != 0) {
            modelMatrix *= transformations2D::Scale(1, window->GetResolution().y * 0.7f * score / (float)maxScore);
        }

        RenderMesh2D(meshes["scoreBar"], shaders["VertexColor"], modelMatrix);

        // render clouds
        modelMatrix = glm::mat3(1);
        modelMatrix *= transformations2D::Translate(resolution.x / 6.4f, resolution.y / 1.2f);
        modelMatrix *= transformations2D::Scale(30, 30);

        RenderMesh2D(meshes["cloud"], shaders["VertexColor"], modelMatrix);

        modelMatrix = glm::mat3(1);
        modelMatrix *= transformations2D::Translate(resolution.x / 2.064f, resolution.y / 1.6f);
        modelMatrix *= transformations2D::Scale(25, 25);

        RenderMesh2D(meshes["cloud"], shaders["VertexColor"], modelMatrix);

        modelMatrix = glm::mat3(1);
        modelMatrix *= transformations2D::Translate(resolution.x / 1.25f, resolution.y / 1.3f);
        modelMatrix *= transformations2D::Scale(35, 35);

        RenderMesh2D(meshes["cloud"], shaders["VertexColor"], modelMatrix);

        // render bushes
        RenderMesh(meshes["bush"], glm::vec3(window->GetResolution().x * 0.7893f, 160, 5), glm::vec3(170.0f));
        RenderMesh(meshes["bush"], glm::vec3(70, 153, 5), glm::vec3(150.0f));

        // render bullets
        if (used_bullets < 3) {
            modelMatrix = glm::mat3(1);
            modelMatrix *= transformations2D::Translate(window->GetResolution().x - 70.0f, window->GetResolution().y - 65.0f);

            RenderMesh2D(meshes["bullet"], shaders["VertexColor"], modelMatrix);
        }

        if (used_bullets < 2) {
            modelMatrix = glm::mat3(1);
            modelMatrix *= transformations2D::Translate(window->GetResolution().x - 120.0f, window->GetResolution().y - 65.0f);

            RenderMesh2D(meshes["bullet"], shaders["VertexColor"], modelMatrix);
        }

        if (used_bullets < 1) {
            modelMatrix = glm::mat3(1);
            modelMatrix *= transformations2D::Translate(window->GetResolution().x - 170.0f, window->GetResolution().y - 65.0f);

            RenderMesh2D(meshes["bullet"], shaders["VertexColor"], modelMatrix);
        }

        // render lives
        if (used_lives < 3) {
            modelMatrix = glm::mat3(1);
            modelMatrix *= transformations2D::Translate(50.0f, window->GetResolution().y - 40.0f);

            RenderMesh2D(meshes["life"], shaders["VertexColor"], modelMatrix);
        }

        if (used_lives < 2) {
            modelMatrix = glm::mat3(1);
            modelMatrix *= transformations2D::Translate(100.0f, window->GetResolution().y - 40.0f);

            RenderMesh2D(meshes["life"], shaders["VertexColor"], modelMatrix);
        }

        if (used_lives < 1) {
            modelMatrix = glm::mat3(1);
            modelMatrix *= transformations2D::Translate(150.0f, window->GetResolution().y - 40.0f);

            RenderMesh2D(meshes["life"], shaders["VertexColor"], modelMatrix);
        }

        if (!escape && !dead_duck && (used_bullets == 3 || used_lives == 3 || activeTime > 15)) {
            escape = 1;
            escapeTime = 0;
            checkEscapeTime = 1;
        }

        if (dead_duck == 1 && translateY <= 0) {
            dead_duck = 0;
            start_duck = 1;
            used_bullets = 0;
        }
        else if (dead_duck == 1) {
            translateY -= deltaTimeSeconds * speedEscape;
        }

        if (escape == 1 && translateY >= window->GetResolution().y) {
            start_duck = 1;
            escape = 0;
            used_lives++;
            used_bullets = 0;

            if (used_lives == 3) {
                playFailSound = 1;
            }
        }

        if (start_duck) {
            // generating a duck case
            wingAngle = 0; // reset wing angle
            translateX = RandomCoordinate(resolution, squareSide); // generate random X coordinate
            translateY = 0; // duck starts from ground
            move_right = RandomDirection(); // generate random direction
            angle = (float)RandomAngle(); // generate random angle

            if (!move_right) {
                angle = 180 - angle;
            }

            start_duck = 0;
            activeTime = 0;
            escape = 0;
            dead_duck = 0;
            nrDucks++;
            up = 1;

            // increase speed for every 5 ducks
            if (nrDucks % 5 == 0) {
                speed = speed + originalSpeed / 5;
            }
        }

        else if (!escape && !dead_duck) {
            // duck trajectory case
            if ((up == 1 && angle < 0) || (up == 0 && angle > 0)) {
                angle *= (-1);
            }

            if (move_right == 1) {
                if (angle > 0 && angle > 90 && angle < 180) {
                    angle = 180 - angle;
                }
                else if (angle < 0 && angle < -90 && angle > -180) {
                    angle = (180 + angle) * (-1);
                }
            }
            else {
                if (angle > 0 && angle < 90 && angle > 0) {
                    angle = 180 - angle;
                }
                else if (angle < 0 && angle > -90) {
                    angle = (180 + angle) * (-1);
                }
            }

            // calcuate the translation factors using the angle and the speed
            translateX += cos(RADIANS(angle)) * speed * deltaTimeSeconds;
            translateY += sin(RADIANS(angle)) * speed * deltaTimeSeconds;

            if (translateX + (float)squareSide > (float)window->GetResolution().x) {
                // duck hits the resolution coordinate for X
                move_right = 0;
                translateX = (float)(window->GetResolution().x - squareSide);
            }
            else if (translateX < 0) {
                // duck hits the 0 coordinate for X
                move_right = 1;
                translateX = 0;
            }

            if (translateY + (float)squareSide - 20 > (float) window->GetResolution().y) {
                // duck hits the resolution coordinate for Y
                translateY = (float)(window->GetResolution().y - squareSide + 20);
                up = 0;
            }
            else if (translateY < 0) {
                // duck hits the 0 coordinate for Y
                translateY = 0;
                up = 1;
            }
        }

        // duck escapes case
        if (escape == 1) {
            // duck goes up
            translateY += deltaTimeSeconds * speedEscape;
            escapeTime += deltaTimeSeconds;

            // play the duck escape sound
            if (escapeTime >= 0.35f && checkEscapeTime) {
                // play duck quack sound when escaping
                PlaySound(TEXT("src\\lab_m1\\Tema1\\SoundEffects\\duck-quack.wav"), NULL, SND_FILENAME | SND_ASYNC);
                checkEscapeTime = 0;
            }
        }

        // position the duck square
        modelMatrix = glm::mat3(1);
        modelMatrix *= transformations2D::Translate(translateX, translateY);

        if (showSquare) {
            RenderMesh2D(meshes["duck_square"], shaders["VertexColor"], modelMatrix);
        }

        modelMatrixWing = modelMatrix;
        modelMatrixDuck = modelMatrix;

        // position the duck
        modelMatrixDuck *= transformations2D::Translate(74, 100);

        if (move_right) {
            // mirror the duck
            modelMatrixDuck *= transformations2D::Translate(33, 0);
            modelMatrixDuck *= transformations2D::MirrorOY();
        }

        modelMatrixDuck *= transformations2D::Scale(22, 22);
        RenderMesh2D(meshes["flyingDuck"], shaders["VertexColor"], modelMatrixDuck);


        modelMatrixWing *= transformations2D::Translate(78, 101);

        if (move_right) {
            // modelMatrixWing *= transformations2D::Rotate(RADIANS(90 + wingAngle));
            modelMatrixWing *= transformations2D::Translate(33, 0);
            modelMatrixWing *= transformations2D::MirrorOY();
            modelMatrixWing *= transformations2D::Rotate(RADIANS(wingAngle));
        }
        else {
            modelMatrixWing *= transformations2D::Rotate(RADIANS(wingAngle));
        }

        // position the wing
        modelMatrixWing *= transformations2D::Scale(22, 22);

        RenderMesh2D(meshes["wing"], shaders["VertexColor"], modelMatrixWing);

        // incremet the wing angle
        wingAngle++;

        // increase the active time
        activeTime += deltaTimeSeconds;
    }
    else {
        // game ended
        if (!win) {
            // game lost case
            skyRed = 11.0f / 255.0f;
            skyGreen = 11.0f / 255.0f;
            skyBlue = 69.0f / 255.0f;

            textRenderFail.RenderText("YOU FAILED", 0.11f * startingResolutionX, 0.2f * startingResolutionY, 2.0f, glm::vec3(1, 0, 0));
            textRenderPlay.RenderText("The ducks win, we'll get them next time", startingResolutionX * 0.22f, startingResolutionY - 150, 0.25f, glm::vec3(227.0f, 66.0f, 52.0f) / 255.0f);

            // play the sound for game over
            if (playFailSound) {
                PlaySound(TEXT("src\\lab_m1\\Tema1\\SoundEffects\\sad_trombone.wav"), NULL, SND_FILENAME | SND_ASYNC);
                playFailSound = 0;
            }
        }
        else {
            // game won case
            textRenderVictory.RenderText("VICTORY", 0.048f * startingResolutionX, 0.35f * startingResolutionY, 1.0f, glm::vec3(199.0f, 21.0f, 133.0f) / 255.0f);
            textRenderDuck.RenderText("abcdefghijklmnop", 0, 0.69f * startingResolutionY, 1.4f, glm::vec3(0, 0, 1));

            // play victory sound
            if (playVictorySound) {
                PlaySound(TEXT("src\\lab_m1\\Tema1\\SoundEffects\\winbanjo.wav"), NULL, SND_FILENAME | SND_ASYNC);
                playVictorySound = 0;
            }
        }

        // render restart button
        textRenderPlay.RenderText("Restart", startingResolutionX / 3.0f, 0.53f * startingResolutionY, 0.8f, glm::vec3(255.0f, 99.0f, 71.0f) / 255.0f);

        float scaleFactorX = window->GetResolution().x / startingResolutionX;
        float scaleFactorY = window->GetResolution().y / startingResolutionY;

        modelMatrix = glm::mat3(1);
        modelMatrix *= transformations2D::Translate((startingResolutionX / 3.0f) * scaleFactorX, (startingResolutionY * 0.36f) * scaleFactorY);
        modelMatrix *= transformations2D::Scale(scaleFactorX, scaleFactorY);
        modelMatrix *= transformations2D::Scale(1.45f, 0.65f);

        if (showSquare) {
            RenderMesh2D(meshes["rectangle"], shaders["VertexColor"], modelMatrix);
        }
    }
}

void Tema1::FrameEnd()
{
}


/*
 *  These are callback functions. To find more about callbacks and
 *  how they behave, see `input_controller.h`.
 */


void Tema1::OnInputUpdate(float deltaTime, int mods)
{
}


void Tema1::OnKeyPress(int key, int mods)
{
    // Add key press event
    if (key == GLFW_KEY_F2) {
        // render squares
        showSquare = 1 - showSquare;
    }
}


void Tema1::OnKeyRelease(int key, int mods)
{
    // Add key release event
}


void Tema1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
    // Add mouse move event
    mouseCoordinateX = (float) mouseX;
    mouseCoordinateY = (float) mouseY;
}


void Tema1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button press event
    if (IS_BIT_SET(button, GLFW_MOUSE_BUTTON_LEFT) && !startGame) {
        // start game case
        float scaleFactorX = window->GetResolution().x / startingResolutionX;
        float scaleFactorY = window->GetResolution().y / startingResolutionY;

        float playCoordinateX = (startingResolutionX / 2 - 142) * scaleFactorX;
        float playCoordinateY = (startingResolutionY - 520) * scaleFactorY;

        if (mouseX >= playCoordinateX && mouseX <= playCoordinateX + 300 * scaleFactorX) {
            float difference = (float) (window->GetResolution().y - mouseY);

            if (difference >= playCoordinateY && difference <= playCoordinateY + 126 * scaleFactorY) {
                startGame = 1;
            }
        }
    }
    else if (IS_BIT_SET(button, GLFW_MOUSE_BUTTON_LEFT) && (win || used_lives == 3)) {
        // restart game case
        float scaleFactorX = window->GetResolution().x / startingResolutionX;
        float scaleFactorY = window->GetResolution().y / startingResolutionY;

        float restartCoordinateX = (startingResolutionX / 3.0f) * scaleFactorX;
        float restartCoordinateY = (startingResolutionY * 0.36f) * scaleFactorY;

        if (mouseX >= restartCoordinateX && mouseX <= restartCoordinateX + 300 * 1.45f * scaleFactorX) {
            float difference = (float) (window->GetResolution().y - mouseY);

            if (difference >= restartCoordinateY && difference <= restartCoordinateY + 126 * 0.65f * scaleFactorX) {
                startGame = 1;
                win = 0;
                used_bullets = 0;
                used_lives = 0;
                score = 0;
                nrDucks = 0;
                activeTime = 0;
                speed = originalSpeed;
                dead_duck = 0;
                escape = 0;
                start_duck = 1;
                    
            }
        }
    }
    else if (IS_BIT_SET(button, GLFW_MOUSE_BUTTON_LEFT) && used_bullets < 3 && !dead_duck && !escape) {
        // shoot duck case
        used_bullets++;

        // play gunshot sound
        PlaySound(TEXT("src\\lab_m1\\Tema1\\SoundEffects\\GunShot.wav"), NULL, SND_FILENAME | SND_ASYNC);

        if (mouseX >= translateX && mouseX <= translateX + squareSide) {
            float difference = (float) (window->GetResolution().y - mouseY);

            if (difference >= translateY && difference <= translateY + squareSide) {
                dead_duck = 1;
                score += 10;
            }
        }
    }
}


void Tema1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button release event
}


void Tema1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}


void Tema1::OnWindowResize(int width, int height)
{
}
