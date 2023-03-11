#include "lab_m1/Tema2/Tema2.h"

#include <vector>
#include <string>
#include <iostream>
#include <windows.h>
#include <set>
#include <mmsystem.h>

#pragma comment(lib, "winmm.lib")

using namespace std;
using namespace m1;


/*
 *  To find out more about `FrameStart`, `Update`, `FrameEnd`
 *  and the order in which they are called, see `world.cpp`.
 */


Tema2::Tema2()
{
}


Tema2::~Tema2()
{
}

int Tema2::checkInRaceTrackBounds(glm::vec3 carPosition) {
    int j = 0;

    for (int i = 0; i < indices_racetrack_margins.size(); i += 3) {
        if (checkInsideTriangle(carPosition, marginPoints[indices_racetrack_margins[i]],
            marginPoints[indices_racetrack_margins[i + 1]],
            marginPoints[indices_racetrack_margins[i + 2]], triangle_areas[j])) {
            return 1;
        }

        j++;
    }

    return 0;
}

void Tema2::calculateEnemyPositionDistances(int enemy_position) {
    int other_enemy_position = enemy_position + 3;
    for (int i = 0; i < enemyCarPositions[enemy_position].size() - 2; i++) {
        if (i % 2 == 0) {
            enemy_distances[enemy_position].push_back(glm::distance(enemyCarPositions[enemy_position][i], enemyCarPositions[enemy_position][i + 2]));
        }
        else {
            enemy_distances[other_enemy_position].push_back(glm::distance(enemyCarPositions[enemy_position][i], enemyCarPositions[enemy_position][i + 2]));
        }
    }

    enemy_distances[enemy_position].push_back(glm::distance(enemyCarPositions[enemy_position][enemyCarPositions[enemy_position].size() - 2], enemyCarPositions[enemy_position][0]));
    enemy_distances[other_enemy_position].push_back(glm::distance(enemyCarPositions[enemy_position][enemyCarPositions[enemy_position].size() - 1], enemyCarPositions[enemy_position][1]));
}

void Tema2::RemoveTrees() {
    std::set<int, greater<int>> positions;

    std::vector<glm::vec3>::iterator it = treePositions.begin();
    treePositions.erase(it + 69 * 2);

    for (int i = treePositions.size() - 1; i >= 0; i--) {
        it = treePositions.begin();

        if (checkInRaceTrackBounds(treePositions[i])) {
            treePositions.erase(it + i);
        }
    }


    cout << "\n\n";
}

float Tema2::triangleArea(glm::vec3 pA, glm::vec3 pB, glm::vec3 pC) {
    glm::vec3 AB = pB - pA;
    glm::vec3 AC = pC - pA;

    float cross_product = AB.x * AC.z - AB.z * AC.x;

    return abs(cross_product) / 2;
}

void Tema2::Init()
{
    polygonMode = GL_FILL;
    renderCameraTarget = false;

    yCoordinate = 0.01f * raceTrackScale;
    translateCar = glm::vec3(createObject::getMiddlePositions()[1].x * raceTrackScale, yCoordinate, createObject::getMiddlePositions()[1].z * raceTrackScale);

    global_camera = new implemented::Cam(dist_camera);

    camera = new implemented::Cam(dist_camera);
    forwardCar = glm::normalize(createObject::getMiddlePositions()[2] - createObject::getMiddlePositions()[1]);
    glm::vec3 offs = (-1.0f) * forwardCar * camera->distanceToTarget + glm::vec3(0, height_camera, 0);
    camera->Set(translateCar + offs, glm::vec3(translateCar.x, translateCar.y, translateCar.z), glm::vec3(0, 1, 0));

    prev_camera = new implemented::Cam(camera->distanceToTarget);

    speedCamera = new implemented::Cam(10);
    speedCamera->Set(glm::vec3(0, 10, 0), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));

    orthoCamera = new implemented::Cam(dist_ortho_camera);
    orthoCamera->Set(glm::vec3(translateCar.x, translateCar.y + height_ortho_camera, translateCar.z), glm::vec3(translateCar.x, translateCar.y, translateCar.z), glm::vec3(0, 1, 0));

    aspect = window->props.aspectRatio;
    fov = RADIANS(60);

    glm::ivec2 resolution = window->GetResolution();

    {
        Mesh* pagodaMesh = new Mesh("pagodaMesh");
        pagodaMesh->LoadMesh(window->props.selfDir + "\\src\\lab_m1\\Tema2\\models\\", "transparent_pagoda.fbx");
        meshes[pagodaMesh->GetMeshID()] = pagodaMesh;
    }

    {
        Mesh* FujiMesh = new Mesh("FujiMesh");
        FujiMesh->LoadMesh(window->props.selfDir + "\\src\\lab_m1\\Tema2\\models\\", "Fuji.fbx");
        meshes[FujiMesh->GetMeshID()] = FujiMesh;
    }

    {
        Mesh* TempleGateMesh = new Mesh("TempleGateMesh");
        TempleGateMesh->LoadMesh(window->props.selfDir + "\\src\\lab_m1\\Tema2\\models\\", "TempleGate.fbx");
        meshes[TempleGateMesh->GetMeshID()] = TempleGateMesh;
    }

    {
        Mesh* TokyoTowerMesh = new Mesh("TokyoTowerMesh");
        TokyoTowerMesh->LoadMesh(window->props.selfDir + "\\src\\lab_m1\\Tema2\\models\\", "Tokyo_Tower.fbx");
        meshes[TokyoTowerMesh->GetMeshID()] = TokyoTowerMesh;
    }

    {
        Mesh* JapaneseTempleMesh = new Mesh("JapaneseTempleMesh");
        JapaneseTempleMesh->LoadMesh(window->props.selfDir + "\\src\\lab_m1\\Tema2\\models\\", "Japanese_temple.fbx");
        meshes[JapaneseTempleMesh->GetMeshID()] = JapaneseTempleMesh;
    }

    Mesh* menuEarth = createObject::CreateRectangle("menuEarth", 100, 1920, glm::vec3(0, 0, 0), glm::vec3(50, 205, 50) / 255.0f, true);
    AddMeshToList(menuEarth);

    Mesh* earth = createObject::CreateSquare("earth", glm::vec3(0, 0, 0), 10000, glm::vec3(50, 205, 50) / 255.0f, true);
    AddMeshToList(earth);

    Mesh* straight_road = createObject::CreateRectangle("straight_road", 10000, 20, glm::vec3(0, 0, 0), glm::vec3(36, 37, 38) / 255.0f, true);
    AddMeshToList(straight_road);

    raceTrack = createObject::CreateRaceTrack("raceTrack", glm::vec3(36, 37, 38) / 255.0f, true);
    AddMeshToList(raceTrack);

    Mesh* car = createObject::CreateParallelipiped("car", carHeight, carWidth, carLength, glm::vec3(255, 20, 147) / 255.0f, true);
    AddMeshToList(car);

    Mesh* enemyCar = createObject::CreateParallelipiped("enemyCar", carHeight, carWidth, carLength, glm::vec3(138, 43, 226) / 255.0f, true);
    AddMeshToList(enemyCar);

    glm::vec3 colors[4];

    colors[0] = glm::vec3(50, 26, 24) / 255.0f;
    colors[1] = glm::vec3(255, 96, 150) / 255.0f;
    colors[2] = glm::vec3(255, 96, 150) / 255.0f;
    colors[3] = glm::vec3(255, 96, 150) / 255.0f;

    Mesh* tree = createObject::CreateTree("tree", 6, 2, 2, 4, 5, 5, 1, 3, 3, colors, true);
    AddMeshToList(tree);

    Mesh* speedBar = createObject::CreateRectangle("speedBar", resolution.x * 0.7f + 5.0f, 40, glm::vec3(20, (resolution.x * 0.7f + 5.0f) / 2, 0), glm::vec3(255, 0, 0) / 255.0f, true);
    AddMeshToList(speedBar);

    Mesh* speedBorder = createObject::CreateRectangle("speedBorder", resolution.x * 0.7f + 10.0f, 42, glm::vec3(0, 0, 0), glm::vec3(1, 1, 1), false);
    AddMeshToList(speedBorder);

    Mesh* banner = createObject::CreateParallelipiped("banner", 30, 2, 2, glm::vec3(222, 184, 135) / 255.0f, true);
    AddMeshToList(banner);

    Mesh* rectangle = createObject::CreateRectangle("rectangle", 126, 300, glm::vec3(0, 0, 0), glm::vec3(1, 0, 0), false);
    AddMeshToList(rectangle);

    marginPoints = transformations3D::ScaleVectorArray(raceTrackScale, raceTrackScale, raceTrackScale, createObject::getRaceTrackMargins());

    for (int i = 0; i < marginPoints.size() - 3; i += 2) {
        indices_racetrack_margins.push_back(i);
        indices_racetrack_margins.push_back(i + 1);
        indices_racetrack_margins.push_back(i + 3);

        triangle_areas.push_back(triangleArea(marginPoints[i], marginPoints[i + 1], marginPoints[i + 3]));

        indices_racetrack_margins.push_back(i);
        indices_racetrack_margins.push_back(i + 2);
        indices_racetrack_margins.push_back(i + 3);

        triangle_areas.push_back(triangleArea(marginPoints[i], marginPoints[i + 2], marginPoints[i + 3]));
    }

    indices_racetrack_margins.push_back(marginPoints.size() - 2);
    indices_racetrack_margins.push_back(marginPoints.size() - 1);
    indices_racetrack_margins.push_back(1);

    triangle_areas.push_back(triangleArea(marginPoints[marginPoints.size() - 2], marginPoints[marginPoints.size() - 1], marginPoints[1]));

    indices_racetrack_margins.push_back(marginPoints.size() - 2);
    indices_racetrack_margins.push_back(0);
    indices_racetrack_margins.push_back(1);

    triangle_areas.push_back(triangleArea(marginPoints[marginPoints.size() - 2], marginPoints[0], marginPoints[1]));

    treePositions = transformations3D::ScaleVectorArray(raceTrackScale, raceTrackScale, raceTrackScale, createObject::getPositions(0.35f, createObject::getTreePositions()));

    RemoveTrees();

    enemyCarPositions[0] = transformations3D::ScaleVectorArray(raceTrackScale, raceTrackScale, raceTrackScale, createObject::getPositions(0.05f, createObject::getMiddlePositions()));
    enemyCarPositions[1] = transformations3D::ScaleVectorArray(raceTrackScale, raceTrackScale, raceTrackScale, createObject::getPositions(0.10f, createObject::getMiddlePositions()));
    enemyCarPositions[2] = transformations3D::ScaleVectorArray(raceTrackScale, raceTrackScale, raceTrackScale, createObject::getPositions(0.15f, createObject::getMiddlePositions()));

    translateEnemy[0] = enemyCarPositions[0][0];
    translateEnemy[1] = enemyCarPositions[1][0];
    translateEnemy[2] = enemyCarPositions[2][0];

    translateEnemy[3] = enemyCarPositions[0][1];
    translateEnemy[4] = enemyCarPositions[1][1];
    translateEnemy[5] = enemyCarPositions[2][1];

    distance_index_enemy_position[0] = 0;
    distance_index_enemy_position[1] = 0;
    distance_index_enemy_position[2] = 0;

    distance_index_enemy_position[3] = 0;
    distance_index_enemy_position[4] = 0;
    distance_index_enemy_position[5] = 0;

    next_index_enemy_position[0] = 2;
    next_index_enemy_position[1] = 2;
    next_index_enemy_position[2] = 2;

    next_index_enemy_position[3] = 3;
    next_index_enemy_position[4] = 3;
    next_index_enemy_position[5] = 3;

    enemy_angle[0] = 0;
    enemy_angle[1] = 0;
    enemy_angle[2] = 0;
    enemy_angle[3] = 0;
    enemy_angle[4] = 0;
    enemy_angle[5] = 0;

    speedEnemy[0] = 100.0f;
    speedEnemy[1] = 110.0f;
    speedEnemy[2] = 120.0f;
    speedEnemy[3] = 90.0f;
    speedEnemy[4] = 80.0f;
    speedEnemy[5] = 70.0f;

    Mesh* up_banner = createObject::CreateParallelipiped("up_banner", glm::distance(marginPoints[0], marginPoints[1]), 2, 2, glm::vec3(222, 184, 135) / 255.0f, true);
    AddMeshToList(up_banner);

    Mesh* checkers = createObject::CreateCheckers("checkers", 12, glm::distance(marginPoints[0], marginPoints[1]), 20, 2, glm::vec3(0, 0, 0), glm::vec3(1, 1, 1), true);
    AddMeshToList(checkers);

    for (int i = 0; i < 3; i++) {
        calculateEnemyPositionDistances(i);
    }

    projectionMatrix = glm::perspective(fov, aspect, zNear, zFar);

    miniViewportArea = ViewportArea(resolution.x - 250, 50, 200, 200);
    speedViewport = ViewportArea(50, 100, 40, resolution.y  * 0.7f);

    // Create a shader program for drawing face polygon with the color of the normal
    {
        Shader* shader = new Shader("Shader");
        shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "Tema2", "shaders", "VertexShader.glsl"), GL_VERTEX_SHADER);
        shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "Tema2", "shaders", "FragmentShader.glsl"), GL_FRAGMENT_SHADER);
        shader->CreateAndLink();
        shaders[shader->GetName()] = shader;
    }

    // load fonts
    textRenderCount.Load(window->props.selfDir + "\\src\\lab_m1\\Tema2\\fonts\\AVENGEANCE.ttf", 128);
    textRenderTitle.Load(window->props.selfDir + "\\src\\lab_m1\\Tema2\\fonts\\osaka-re.ttf", 128);
    textRenderPlay.Load(window->props.selfDir + "\\src\\lab_m1\\Tema2\\Fonts\\Hack-Bold.ttf", 128);


    startingResolutionX = (float)resolution.x;
    startingResolutionY = (float)resolution.y;

    pagodaPosition = glm::vec3(createObject::getMiddlePositions()[15].x * raceTrackScale - 200, 220, createObject::getMiddlePositions()[15].z * raceTrackScale);
    FujiPosition = glm::vec3(createObject::getMiddlePositions()[43].x * raceTrackScale, 130, createObject::getMiddlePositions()[43].z * raceTrackScale + 200);
    templeGatePosition = glm::vec3(createObject::getMiddlePositions()[114].x * raceTrackScale + 100, 50, createObject::getMiddlePositions()[114].z * raceTrackScale);
    tokyoTowerPosition = glm::vec3(createObject::getMiddlePositions()[193].x * raceTrackScale, 250, createObject::getMiddlePositions()[193].z * raceTrackScale + 400);
    japaneseTemplePosition = glm::vec3(createObject::getMiddlePositions()[284].x * raceTrackScale + 500, 200, createObject::getMiddlePositions()[284].z * raceTrackScale);
}


void Tema2::FrameStart()
{
    // Clears the color buffer (using the previously set color) and depth buffer
    glClearColor(skyRed, skyGreen, skyBlue, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::ivec2 resolution = window->GetResolution();
    // Sets the screen area where to draw
    glViewport(0, 0, resolution.x, resolution.y);
    
}

Mesh* Tema2::CreateMesh(const char* name, const std::vector<VertexFormat>& vertices, const std::vector<unsigned int>& indices)
{
    unsigned int VAO = 0;
    // Create the VAO and bind it
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    // Create the VBO and bind it
    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    // Send vertices data into the VBO buffer
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * vertices.size(), &vertices[0], GL_STATIC_DRAW);

    // Create the IBO and bind it
    unsigned int IBO;
    glGenBuffers(1, &IBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);

    // Send indices data into the IBO buffer
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * indices.size(), &indices[0], GL_STATIC_DRAW);

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

    // Unbind the VAO
    glBindVertexArray(0);

    // Check for OpenGL errors
    CheckOpenGLError();

    // Mesh information is saved into a Mesh object
    meshes[name] = new Mesh(name);
    meshes[name]->InitFromBuffer(VAO, static_cast<unsigned int>(indices.size()));
    meshes[name]->vertices = vertices;
    meshes[name]->indices = indices;
    return meshes[name];
}

void Tema2::RenderSimpleMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix)
{
    if (!mesh || !shader || !shader->GetProgramID())
        return;

    // Render an object using the specified shader and the specified position
    glUseProgram(shader->program);

    int location = glGetUniformLocation(shader->program, "Model");
    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(modelMatrix));

    int viewLocation = glGetUniformLocation(shader->program, "View");

    glm::mat4 viewMatrix = global_camera->GetViewMatrix();
    glUniformMatrix4fv(viewLocation, 1, GL_FALSE, glm::value_ptr(viewMatrix));

    int projectionLocation = glGetUniformLocation(shader->program, "Projection");

    glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

    int car_position = glGetUniformLocation(shader->program, "car_position");
    glUniform3f(car_position, translateCar.x, translateCar.y, translateCar.z);

    int scale_factor = glGetUniformLocation(shader->program, "scale_factor");
    glUniform1f(scale_factor, scaleFactor);

    // Draw the object
    glBindVertexArray(mesh->GetBuffers()->m_VAO);
    glDrawElements(mesh->GetDrawMode(), static_cast<int>(mesh->indices.size()), GL_UNSIGNED_INT, 0);
}

int Tema2::checkInsideTriangle(glm::vec3 P, glm::vec3 A, glm::vec3 B, glm::vec3 C, float ABC_triangleArea) {
    float area_sum = 0;

    area_sum += triangleArea(A, B, P);
    area_sum += triangleArea(A, C, P);
    area_sum += triangleArea(B, C, P);

    if (glm::abs(ABC_triangleArea - area_sum) < 0.1f) {
        return 1;
    }

    return 0;
}

int Tema2::checkSign(float x) {
    if (x < 0) {
        return -1;
    }

    return 1;
}

int Tema2::checkCollision(glm::vec3 positionCar) {
    float distance;

    for (int i = 0; i < 6; i++) {
        distance = sqrt(pow(positionCar.x - translateEnemy[i].x, 2) + pow(positionCar.y - translateEnemy[i].y, 2) +
                        pow(positionCar.z - translateEnemy[i].z, 2));

        if (distance <= carLength) {
            return 1;
        }
    }

    return 0;
}

int Tema2::checkInBoundsVector(glm::vec3 currentPosition, glm::vec3 nextPosition) {

    if (checkSign(currentPosition.x) != checkSign(nextPosition.x) || checkSign(currentPosition.z) != checkSign(nextPosition.z)) {
        return 1;
    }

    float absCurrentX = abs(currentPosition.x);
    float absCurrentZ = abs(currentPosition.z);

    float absNextX = abs(nextPosition.x);
    float absNextZ = abs(nextPosition.z);

    if (absCurrentX > absNextX || absCurrentZ > absNextZ) {
        return 0;
    }

    return 1;
}

void Tema2::moveEnemy(int enemy_index, float deltaTimeSeconds, int startingPoint) {
    int ind = enemy_index % 3;

    int previous_index = next_index_enemy_position[enemy_index] - 2;

    if (previous_index < 0) {
        previous_index = enemyCarPositions[ind].size() - 1;

        if (startingPoint == 0) {
            previous_index = enemyCarPositions[ind].size() - 2;
        }
    }

    glm::vec3 direction = glm::normalize(enemyCarPositions[ind][next_index_enemy_position[enemy_index]] - translateEnemy[enemy_index]);

    glm::vec3 direction2 = glm::normalize(enemyCarPositions[ind][next_index_enemy_position[enemy_index]] - enemyCarPositions[ind][previous_index]);

    enemy_angle[enemy_index] = glm::atan2(direction2.x, direction2.z);

    translateEnemy[enemy_index] += direction * speedEnemy[enemy_index] * deltaTimeSeconds;

    float currentDistance = enemy_distances[enemy_index][distance_index_enemy_position[enemy_index]];
        
    float passed_distance = glm::distance(translateEnemy[enemy_index], enemyCarPositions[ind][previous_index]);

    if (passed_distance > currentDistance) {
        translateEnemy[enemy_index] = enemyCarPositions[ind][next_index_enemy_position[enemy_index]];
        next_index_enemy_position[enemy_index] = next_index_enemy_position[enemy_index] + 2;
        distance_index_enemy_position[enemy_index] = distance_index_enemy_position[enemy_index] + 1;
    }

    if (next_index_enemy_position[enemy_index] >= enemyCarPositions[ind].size()) {
        next_index_enemy_position[enemy_index] = startingPoint;
    }

    if (distance_index_enemy_position[enemy_index] >= enemy_distances[enemy_index].size()) {
        distance_index_enemy_position[enemy_index] = 0;
    }

    if (previous_index < 0) {
        previous_index = enemyCarPositions[ind].size() - 1;

        if (startingPoint == 0) {
            previous_index = enemyCarPositions[ind].size() - 2;
        }
    }
}


void Tema2::RenderScene(float deltaTimeSeconds) {
    if (ortho == 1) {
        orthoCamera->Set(glm::vec3(translateCar.x + 1.0f, translateCar.y + height_ortho_camera, translateCar.z), glm::vec3(translateCar.x, translateCar.y, translateCar.z), glm::vec3(0, 1, 0));
        global_camera->copyCamera(orthoCamera);
    }
    else if (ortho == 0) {
        global_camera->copyCamera(camera);
    }

    // Render the earth
    {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix *= transformations3D::Translate(-5000, 0, -5000);
        modelMatrix *= transformations3D::RotateOX(RADIANS(90));
        RenderSimpleMesh(meshes["earth"], shaders["Shader"], modelMatrix);
    }

     // Render race track
    {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix *= transformations3D::Translate(0, 0, 0);
        modelMatrix *= transformations3D::Scale(raceTrackScale, raceTrackScale, raceTrackScale);
        RenderSimpleMesh(meshes["raceTrack"], shaders["Shader"], modelMatrix);
    }

    // Render banner
    {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix *= transformations3D::Translate(marginPoints[0].x, marginPoints[0].y, marginPoints[0].z);
        RenderSimpleMesh(meshes["banner"], shaders["Shader"], modelMatrix);
    }

    // Render banner
    {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix *= transformations3D::Translate(marginPoints[1].x, marginPoints[1].y, marginPoints[1].z);
        RenderSimpleMesh(meshes["banner"], shaders["Shader"], modelMatrix);
    }

    if (!ortho) {
        // Render pagoda
        {
            pagodaPosition.y = 220;
            pagodaPosition.y = 220 - pow(distance(translateCar, pagodaPosition), 2) * scaleFactor;

            glm::mat4 modelMatrix = glm::mat4(1);
            modelMatrix *= transformations3D::Translate(pagodaPosition.x, pagodaPosition.y, pagodaPosition.z);
            modelMatrix *= transformations3D::Scale(500, 500, 500);
            modelMatrix *= transformations3D::RotateOY(RADIANS(90));
            RenderMesh(meshes["pagodaMesh"], shaders["Simple"], modelMatrix);
        }

        // Render Fuji
        {
            FujiPosition.y = 130;
            FujiPosition.y = 130 - pow(distance(translateCar, FujiPosition), 2) * scaleFactor;

            glm::mat4 modelMatrix = glm::mat4(1);
            modelMatrix *= transformations3D::Translate(FujiPosition.x, FujiPosition.y, FujiPosition.z);
            modelMatrix *= transformations3D::Scale(500, 500, 500);
            modelMatrix *= transformations3D::RotateOY(RADIANS(185));
            RenderMesh(meshes["FujiMesh"], shaders["Simple"], modelMatrix);
        }

        // Render gate
        {
            templeGatePosition.y = 50;
            templeGatePosition.y = 50 - pow(distance(translateCar, templeGatePosition), 2) * scaleFactor;

            glm::mat4 modelMatrix = glm::mat4(1);
            modelMatrix *= transformations3D::Translate(templeGatePosition.x, templeGatePosition.y, templeGatePosition.z);
            modelMatrix *= transformations3D::Scale(500, 500, 500);
            modelMatrix *= transformations3D::RotateOY(RADIANS(270));
            RenderMesh(meshes["TempleGateMesh"], shaders["Simple"], modelMatrix);
        }

        // Render tower
        {
            tokyoTowerPosition.y = 250;
            tokyoTowerPosition.y = 250 - pow(distance(translateCar, tokyoTowerPosition), 2) * scaleFactor;

            glm::mat4 modelMatrix = glm::mat4(1);
            modelMatrix *= transformations3D::Translate(tokyoTowerPosition.x, tokyoTowerPosition.y, tokyoTowerPosition.z);
            modelMatrix *= transformations3D::Scale(500, 500, 500);
            modelMatrix *= transformations3D::RotateOY(RADIANS(180));
            modelMatrix *= transformations3D::RotateOZ(RADIANS(2));
            RenderMesh(meshes["TokyoTowerMesh"], shaders["Simple"], modelMatrix);
        }

        // Render temple
        {
            japaneseTemplePosition.y = 220;
            japaneseTemplePosition.y = 220 - pow(distance(translateCar, japaneseTemplePosition), 2) * scaleFactor;

            glm::mat4 modelMatrix = glm::mat4(1);
            modelMatrix *= transformations3D::Translate(japaneseTemplePosition.x, japaneseTemplePosition.y, japaneseTemplePosition.z);
            modelMatrix *= transformations3D::Scale(500, 500, 500);
            modelMatrix *= transformations3D::RotateOY(RADIANS(90));
            modelMatrix *= transformations3D::RotateOZ(RADIANS(0));
            RenderMesh(meshes["JapaneseTempleMesh"], shaders["Simple"], modelMatrix);
        }
    }

    // Render banner
    {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix *= transformations3D::Translate(marginPoints[0].x, 32, marginPoints[0].z);
        modelMatrix *= transformations3D::RotateOY(RADIANS(-0.5f));
        modelMatrix *= transformations3D::RotateOX(RADIANS(90));
        RenderSimpleMesh(meshes["up_banner"], shaders["Shader"], modelMatrix);
    }

    // Render checkers
    {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix *= transformations3D::Translate(marginPoints[1].x, 20, marginPoints[1].z - 0.96f);
        modelMatrix *= transformations3D::RotateOY(RADIANS(90.0f));
        RenderSimpleMesh(meshes["checkers"], shaders["Shader"], modelMatrix);
    }

    for (int i = 0; i < treePositions.size(); i++) {
        // Render tree
        {
            glm::mat4 modelMatrix = glm::mat4(1);
            modelMatrix *= transformations3D::Translate(treePositions[i].x, 0, treePositions[i].z);
            modelMatrix *= transformations3D::Scale(2.5f, 2.5f, 2.5f);
            RenderSimpleMesh(meshes["tree"], shaders["Shader"], modelMatrix);
        }
    }

    // Render car
    {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix *= transformations3D::Translate(translateCar.x, translateCar.y, translateCar.z);
        modelMatrix *= transformations3D::RotateOY(rotateAngle);
        RenderSimpleMesh(meshes["car"], shaders["Shader"], modelMatrix);
    }

    // Render enemy car1
    {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix *= transformations3D::Translate(translateEnemy[0].x, translateEnemy[0].y, translateEnemy[0].z);
        modelMatrix *= transformations3D::RotateOY(enemy_angle[0]);
        RenderSimpleMesh(meshes["enemyCar"], shaders["Shader"], modelMatrix);
    }

    // Render enemy car2
    {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix *= transformations3D::Translate(translateEnemy[1].x, translateEnemy[1].y, translateEnemy[1].z);
        modelMatrix *= transformations3D::RotateOY(enemy_angle[1]);
        RenderSimpleMesh(meshes["enemyCar"], shaders["Shader"], modelMatrix);
    }

    // Render enemy car3
    {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix *= transformations3D::Translate(translateEnemy[2].x, translateEnemy[2].y, translateEnemy[2].z);
        modelMatrix *= transformations3D::RotateOY(enemy_angle[2]);
        RenderSimpleMesh(meshes["enemyCar"], shaders["Shader"], modelMatrix);
    }

    // Render enemy car4
    {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix *= transformations3D::Translate(translateEnemy[3].x, translateEnemy[3].y, translateEnemy[3].z);
        modelMatrix *= transformations3D::RotateOY(enemy_angle[3]);
        RenderSimpleMesh(meshes["enemyCar"], shaders["Shader"], modelMatrix);
    }

    // Render enemy car5
    {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix *= transformations3D::Translate(translateEnemy[4].x, translateEnemy[4].y, translateEnemy[4].z);
        modelMatrix *= transformations3D::RotateOY(enemy_angle[4]);
        RenderSimpleMesh(meshes["enemyCar"], shaders["Shader"], modelMatrix);
    }

    // Render enemy car6
    {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix *= transformations3D::Translate(translateEnemy[5].x, translateEnemy[5].y, translateEnemy[5].z);
        modelMatrix *= transformations3D::RotateOY(enemy_angle[5]);
        RenderSimpleMesh(meshes["enemyCar"], shaders["Shader"], modelMatrix);
    }
}

void Tema2::Update(float deltaTimeSeconds)
{
    glPolygonMode(GL_FRONT_AND_BACK, polygonMode);
    glm::ivec2 resolution = window->GetResolution();

    if (menu_screen) {
        // render title and play button
        textRenderTitle.RenderText("Tokyo Drift", startingResolutionX / 2 - 500, 150, 1.3f, glm::vec3(186, 85, 211) / 255.0f);
        textRenderPlay.RenderText("Play", startingResolutionX / 2 - 149, 350, 1.0f, glm::vec3(255, 20, 147) / 255.0f);
        textRenderPlay.RenderText("Click Play to start the game", 325, startingResolutionY - 220, 0.3f, glm::vec3(255, 20, 147) / 255.0f);
    
        float scaleFactorX = window->GetResolution().x / startingResolutionX;
        float scaleFactorY = window->GetResolution().y / startingResolutionY;

        // Render the earth
        {
            glm::mat4 modelMatrix = glm::mat4(1);
            modelMatrix *= transformations3D::Translate(-40, 0, -1000);
            modelMatrix *= transformations3D::RotateOX(RADIANS(89));
            RenderMesh(meshes["earth"], shaders["VertexColor"], modelMatrix);
        }

        // Render straight road
        {
            glm::mat4 modelMatrix = glm::mat4(1);
            modelMatrix *= transformations3D::Translate(0, 0, 0);
            modelMatrix *= transformations3D::Translate(-40, 0, -700);
            modelMatrix *= transformations3D::RotateOX(RADIANS(89.0f));
            RenderMesh(meshes["straight_road"], shaders["VertexColor"], modelMatrix);
        }
    }
    else {
        ortho = 0;

        glViewport(0, 0, resolution.x, resolution.y);
        projectionMatrix = glm::perspective(fov, aspect, zNear, zFar);
        RenderScene(deltaTimeSeconds);

        if (activeTime < 1.0f) {
            textRenderCount.RenderText("3", startingResolutionX / 2 - 20, startingResolutionY / 2, 1.0f, glm::vec3(1, 1, 1));
        }
        if (activeTime >= 1.0f && activeTime < 2.0f) {
            textRenderCount.RenderText("2", startingResolutionX / 2 - 20, startingResolutionY / 2, 1.0f, glm::vec3(1, 1, 1));
        }
        if (activeTime >= 2.0f && activeTime < 3.0f) {
            textRenderCount.RenderText("1", startingResolutionX / 2 - 20, startingResolutionY / 2, 1.0f, glm::vec3(1, 1, 1));
        }

        if (activeTime >= 3.0f && activeTime < 4.0f) {
            textRenderCount.RenderText("START!", startingResolutionX / 2 - 150, startingResolutionY / 2, 1.0f, glm::vec3(1, 1, 1));
            PlaySound(TEXT("src\\lab_m1\\Tema2\\sounds\\Tokyo_Drift_Teriyaki_Boyz.wav"), NULL, SND_LOOP | SND_ASYNC);
            startGame = 1;
        }

        ortho = 1;
        glClear(GL_DEPTH_BUFFER_BIT);
        glViewport(resolution.x - 250, 50, miniViewportArea.width, miniViewportArea.height);
        projectionMatrix = glm::ortho(left, right, bottom, top, zNearOrtho, zFarOrtho);
        RenderScene(deltaTimeSeconds);

        glClear(GL_DEPTH_BUFFER_BIT);
        glViewport(0, 0, resolution.x, resolution.y);
        glClearColor(skyRed, skyGreen, skyBlue, 1);
        speedCamera->Set(glm::vec3(1.0f, 10, 0), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
        global_camera->copyCamera(speedCamera);

       {
            glm::mat4 modelMatrix = glm::mat4(1);
            modelMatrix *= transformations3D::Translate(135, 0, 186.05f);
            modelMatrix *= transformations3D::RotateOZ(RADIANS(90));
            modelMatrix *= transformations3D::RotateOY(RADIANS(90));
            modelMatrix *= transformations3D::Scale(0.3f, scaleBarY, 1.0f);
            RenderSimpleMesh(meshes["speedBar"], shaders["VertexColor"], modelMatrix);
        }

        {
            glm::mat4 modelMatrix = glm::mat4(1);
            modelMatrix *= transformations3D::Translate(0, 0, 180);
            modelMatrix *= transformations3D::RotateOZ(RADIANS(90));
            modelMatrix *= transformations3D::RotateOY(RADIANS(90));
            modelMatrix *= transformations3D::Scale(0.3f, 0.3f, 1.0f);
            RenderSimpleMesh(meshes["speedBorder"], shaders["VertexColor"], modelMatrix);
        }

        if (startGame) {
            moveEnemy(0, deltaTimeSeconds, 0);
            moveEnemy(1, deltaTimeSeconds, 0);
            moveEnemy(2, deltaTimeSeconds, 0);

            moveEnemy(3, deltaTimeSeconds, 1);
            moveEnemy(4, deltaTimeSeconds, 1);
            moveEnemy(5, deltaTimeSeconds, 1);
        }

        activeTime += deltaTimeSeconds;
    }
}


void Tema2::FrameEnd()
{

}


void Tema2::RenderMesh(Mesh * mesh, Shader * shader, const glm::mat4 & modelMatrix)
{
    if (!mesh || !shader || !shader->program)
        return;

    // Render an object using the specified shader and the specified position
    shader->Use();
    glUniformMatrix4fv(shader->loc_view_matrix, 1, GL_FALSE, glm::value_ptr(camera->GetViewMatrix()));
    glUniformMatrix4fv(shader->loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
    glUniformMatrix4fv(shader->loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));

    mesh->Render();
}


/*
 *  These are callback functions. To find more about callbacks and
 *  how they behave, see `input_controller.h`.
 */


void Tema2::OnInputUpdate(float deltaTime, int mods)
{
    if (startGame && !menu_screen) {
        // move the camera only if MOUSE_RIGHT button is pressed

        prev_camera->copyCamera(camera);

        glm::vec3 prev_position = camera->position;
        glm::vec3 prev_forward = camera->forward;
        glm::vec3 prev_up = camera->up;
        glm::vec3 prev_right = camera->right;
        glm::vec3 prev_direction = camera->direction;
        glm::vec3 prev_center = camera->center;


        if (window->KeyHold(GLFW_KEY_W)) {
            prevPositionCar = translateCar;
            forwardCar = camera->forward;
            forwardCar.y = 0;
            forwardCar = glm::normalize(forwardCar);
            translateCar += forwardCar * deltaTime * speed;

            glm::vec3 offs = (-1.0f) * forwardCar * camera->distanceToTarget + glm::vec3(0, height_camera, 0);

            if (!checkCollision(prevPositionCar) && checkInRaceTrackBounds(translateCar)) {
                forwardCar = camera->forward;
                forwardCar.y = 0;
                forwardCar = glm::normalize(forwardCar);
                translateCar += forwardCar * deltaTime * speed;

                glm::vec3 offs = (-1.0f) * forwardCar * camera->distanceToTarget + glm::vec3(0, height_camera, 0);
                camera->Set(translateCar + offs, glm::vec3(translateCar.x, translateCar.y, translateCar.z), glm::vec3(0, 1, 0));
            }
            else {
                translateCar = prevPositionCar;
            }
        }

        if (window->KeyHold(GLFW_KEY_S)) {
            prevPositionCar = translateCar;
            forwardCar = camera->forward;
            forwardCar.y = 0;
            forwardCar = glm::normalize(forwardCar);
            translateCar -= forwardCar * deltaTime * speed;

            glm::vec3 offs = (-1.0f) * forwardCar * camera->distanceToTarget + glm::vec3(0, height_camera, 0);

            if (!checkCollision(prevPositionCar) && checkInRaceTrackBounds(translateCar)) {
                camera->Set(translateCar + offs, glm::vec3(translateCar.x, translateCar.y, translateCar.z), glm::vec3(0, 1, 0));
            }
            else {
                translateCar = prevPositionCar;
            }
        }

        if (window->KeyHold(GLFW_KEY_A)) {
            if (!checkCollision(prevPositionCar)) {
                camera->RotateThirdPerson_OY(speedRotation * deltaTime);

                forwardCar = camera->forward;
                forwardCar.y = 0;
                forwardCar = glm::normalize(forwardCar);

                rotateAngle += speedRotation * deltaTime;

                glm::vec3 offs = (-1.0f) * forwardCar * camera->distanceToTarget + glm::vec3(0, height_camera, 0);
                camera->Set(translateCar + offs, glm::vec3(translateCar.x, translateCar.y, translateCar.z), glm::vec3(0, 1, 0));
            }


        }

        if (window->KeyHold(GLFW_KEY_D)) {
            if (!checkCollision(prevPositionCar)) {
                camera->RotateThirdPerson_OY((-1) * speedRotation * deltaTime);

                forwardCar = camera->forward;
                forwardCar.y = 0;
                forwardCar = glm::normalize(forwardCar);

                rotateAngle += (-1) * speedRotation * deltaTime;

                glm::vec3 offs = (-1.0f) * forwardCar * camera->distanceToTarget + glm::vec3(0, height_camera, 0);
                camera->Set(translateCar + offs, glm::vec3(translateCar.x, translateCar.y, translateCar.z), glm::vec3(0, 1, 0));
            }
        }
         
        if (window->KeyHold(GLFW_KEY_LEFT_SHIFT) && scaleBarY > 0.0001f && !up) {
            scaleBarY -= deltaTime * 0.1f;
            speed += deltaTime * 30;

            if (scaleBarY < 0.0001f) {
                scaleBarY = 0.0001f;
                up = 1;
            }

            pressed = 1;
        }
        else if (scaleBarY < 0.3f && up) {
            scaleBarY += deltaTime * 0.1f;
            speed -= deltaTime * 30;

            if (abs(speed - originalSpeed) < 0.00001f) {
                speed = originalSpeed;
            }

            if (scaleBarY > 0.3f) {
                scaleBarY = 0.3f;
                up = 0;

                if (abs(speed - originalSpeed) > 0.00001f) {
                    speed = originalSpeed;
                }
            }

            pressed = 0;
        }

    }
}


void Tema2::OnKeyPress(int key, int mods)
{
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


void Tema2::OnKeyRelease(int key, int mods)
{
    // Add key release event
    if (key == GLFW_KEY_LEFT_SHIFT && pressed) {
        up = 1;
    }
}


void Tema2::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
    // Add mouse move event
}


void Tema2::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button press event
    if (IS_BIT_SET(button, GLFW_MOUSE_BUTTON_LEFT) && menu_screen) {
        // start game case
        float scaleFactorX = window->GetResolution().x / startingResolutionX;
        float scaleFactorY = window->GetResolution().y / startingResolutionY;

        float playCoordinateX = (startingResolutionX / 2 - 142) * scaleFactorX;
        float playCoordinateY = (startingResolutionY - 470) * scaleFactorY;

        if (mouseX >= playCoordinateX && mouseX <= playCoordinateX + 300 * scaleFactorX) {
            float difference = (float)(window->GetResolution().y - mouseY);

            if (difference >= playCoordinateY && difference <= playCoordinateY + 126 * scaleFactorY) {
                menu_screen = 0;
            }
        }
    }
}


void Tema2::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button release event
}


void Tema2::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}


void Tema2::OnWindowResize(int width, int height)
{
}
