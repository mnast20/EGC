#include "lab_m1/Tema3/Tema3.h"

#include <vector>
#include <string>
#include <iostream>
#include <algorithm> 

using namespace std;
using namespace m1;


/*
 *  To find out more about `FrameStart`, `Update`, `FrameEnd`
 *  and the order in which they are called, see `world.cpp`.
 */


Tema3::Tema3()
{
}


Tema3::~Tema3()
{
}


void Tema3::Init()
{
    renderCameraTarget = false;

    float zCamera2 = zCamera, yCamera2 = yCamera;
    yCamera = yCamera2 * cos(RADIANS(90 + angleSlope)) - zCamera * sin(RADIANS(90 + angleSlope));
    zCamera = yCamera2 * sin(RADIANS(90 + angleSlope)) + zCamera2 * cos(RADIANS(90 + angleSlope));

    /*float distanceSunZ2 = distanceSunZ, distanceSunY2 = distanceSunY;
    distanceSunY = distanceSunY2 * cos(RADIANS(90 + angleSlope)) - distanceSunZ * sin(RADIANS(90 + angleSlope));
    distanceSunZ = distanceSunY2 * sin(RADIANS(90 + angleSlope)) + distanceSunZ2 * cos(RADIANS(90 + angleSlope));*/

    camera = new implemented::Tema3_Camera(distanceCamera);
    camera->Set(glm::vec3(translateSkier.x, translateSkier.y + yCamera, translateSkier.z + zCamera), glm::vec3(translateSkier.x, translateSkier.y, translateSkier.z), glm::vec3(0, 1, 0));

    aspect = window->props.aspectRatio;
    fov = RADIANS(60);

    projectionMatrix = glm::perspective(fov, aspect, zNear, zFar);

    spotlightPosition.reserve(201);
    // punctiformPosition.reserve(201);
    punctiforms.reserve(201);

    for (int i = 0; i < 201; i++) {
        spotlightPosition.push_back(glm::vec3(0, 0, 0));
        // punctiformPosition.push_back(glm::vec3(0, 0, 0));
        punctiforms.push_back(punctiformObject(glm::vec3(0, 0, 0), glm::vec3(0, 0, 0)));
    }

    Mesh* earth = createObj::CreateSquare("earth", 100, glm::vec3(255, 255, 255) / 255.0f, true, true);
    AddMeshToList(earth);

    Mesh* skier = createObj::CreateParallelipiped("skier", 5, 2, 3, glm::vec3(164, 219, 232) / 255.0f, true);
    AddMeshToList(skier);

    Mesh* ski = createObj::CreateParallelipiped("ski", 0.2f, 8, 1, glm::vec3(0, 181, 226) / 255.0f, true);
    AddMeshToList(ski);

    Mesh* pole = createObj::CreateParallelipiped("pole", 9.5f, 1, 1, glm::vec3(169, 169, 169) / 255.0f, true);
    AddMeshToList(pole);

    Mesh* topPole = createObj::CreateParallelipiped("topPole", 1, 2, 6, glm::vec3(169, 169, 169) / 255.0f, true);
    AddMeshToList(topPole);

    Mesh* trunk = createObj::CreateParallelipiped("trunk", 6, 2, 2, glm::vec3(139, 69, 19) / 255.0f, true);
    AddMeshToList(trunk);

    Mesh* present = createObj::CreateParallelipiped("present", 3, 3, 3, glm::vec3(255, 0, 0) / 255.0f, true);
    AddMeshToList(present);

    {
        Mesh* mesh = new Mesh("sphere");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "sphere.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }

    // Load meshes
    {
        Mesh* mesh = new Mesh("cone");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "cone.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }

    // Load meshes
    {
        Mesh* mesh = new Mesh("cube");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "cube.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }

    const string sourceTextureDir = PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "Tema3", "textures");

    // Load textures
    {
        Texture2D* texture = new Texture2D();
        texture->Load2D(PATH_JOIN(sourceTextureDir, "Metal.png").c_str(), GL_REPEAT);
        mapTextures["Metal"] = texture;
    }

    // Load textures
    {
        Texture2D* texture = new Texture2D();
        texture->Load2D(PATH_JOIN(sourceTextureDir, "PineTree.png").c_str(), GL_REPEAT);
        mapTextures["PineTree"] = texture;
    }

    {
        Texture2D* texture = new Texture2D();
        texture->Load2D(PATH_JOIN(sourceTextureDir, "Present.png").c_str(), GL_REPEAT);
        mapTextures["Present"] = texture;
    }

    {
        Texture2D* texture = new Texture2D();
        texture->Load2D(PATH_JOIN(sourceTextureDir, "Rock.png").c_str(), GL_REPEAT);
        mapTextures["Rock"] = texture;
    }

    {
        Texture2D* texture = new Texture2D();
        texture->Load2D(PATH_JOIN(sourceTextureDir, "Ski.png").c_str(), GL_REPEAT);
        mapTextures["Ski"] = texture;
    }

    {
        Texture2D* texture = new Texture2D();
        texture->Load2D(PATH_JOIN(sourceTextureDir, "snow.png").c_str(), GL_REPEAT);
        mapTextures["snow"] = texture;
    }

    {
        Texture2D* texture = new Texture2D();
        texture->Load2D(PATH_JOIN(sourceTextureDir, "Ski.png").c_str(), GL_REPEAT);
        mapTextures["Snowboard"] = texture;
    }

    {
        Texture2D* texture = new Texture2D();
        texture->Load2D(PATH_JOIN(sourceTextureDir, "Skier.png").c_str(), GL_REPEAT);
        mapTextures["Skier"] = texture;
    }

    {
        Texture2D* texture = new Texture2D();
        texture->Load2D(PATH_JOIN(sourceTextureDir, "Wood.png").c_str(), GL_REPEAT);
        mapTextures["Wood"] = texture;
    }

    // Create a shader program for drawing face polygon with the color of the normal
    {
        Shader* shader = new Shader("Shader");
        shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "Tema3", "shaders", "VertexShader.glsl"), GL_VERTEX_SHADER);
        shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "Tema3", "shaders", "FragmentShader.glsl"), GL_FRAGMENT_SHADER);
        shader->CreateAndLink();
        shaders[shader->GetName()] = shader;
    }

    textRenderTitle.Load(window->props.selfDir + "\\src\\lab_m1\\Tema3\\fonts\\Icecold.ttf", 128);
    textRenderPlay.Load(window->props.selfDir + "\\src\\lab_m1\\Tema3\\Fonts\\Hack-Bold.ttf", 128);
    textRenderFrozen.Load(window->props.selfDir + "\\src\\lab_m1\\Tema3\\Fonts\\IceCaps.ttf", 128);
    textRenderFail.Load(window->props.selfDir + "\\src\\lab_m1\\Tema3\\Fonts\\IceCold.ttf", 128);
    textRenderChoose.Load(window->props.selfDir + "\\src\\lab_m1\\Tema3\\Fonts\\CuteSnow.otf", 128);
    textRenderSki.Load(window->props.selfDir + "\\src\\lab_m1\\Tema3\\Fonts\\Ski.ttf", 128);

    glm::ivec2 resolution = window->GetResolution();
    startingResolutionX = (float)resolution.x;
    startingResolutionY = (float)resolution.y;
}


void Tema3::FrameStart()
{
    // Clears the color buffer (using the previously set color) and depth buffer
    glClearColor(skyRed, skyGreen, skyBlue, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::ivec2 resolution = window->GetResolution();
    // Sets the screen area where to draw
    glViewport(0, 0, resolution.x, resolution.y);
}

void Tema3::RenderSimpleMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix, Texture2D* texture1, Texture2D* texture2)
{
    if (!mesh || !shader || !shader->GetProgramID())
        return;

    // Render an object using the specified shader and the specified position
    glUseProgram(shader->program);

    // Bind model matrix
    GLint loc_model_matrix = glGetUniformLocation(shader->program, "Model");
    glUniformMatrix4fv(loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));

    // Bind view matrix
    glm::mat4 viewMatrix = camera->GetViewMatrix();
    int loc_view_matrix = glGetUniformLocation(shader->program, "View");
    glUniformMatrix4fv(loc_view_matrix, 1, GL_FALSE, glm::value_ptr(viewMatrix));

    // Bind projection matrix
    glm::mat4 projectionMatrix = GetSceneCamera()->GetProjectionMatrix();
    int loc_projection_matrix = glGetUniformLocation(shader->program, "Projection");
    glUniformMatrix4fv(loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

    int yes_earth = glGetUniformLocation(shader->program, "yes_earth");
    glUniform1i(yes_earth, yesEarth);

    int yes_right = glGetUniformLocation(shader->program, "yes_right");
    glUniform1i(yes_right, yesRight);

    int time = glGetUniformLocation(shader->program, "time");
    glUniform1f(time, Engine::GetElapsedTime());

    int angle_rotate = glGetUniformLocation(shader->program, "angle_rotate");
    glUniform1f(angle_rotate, angleSkier);

    int position_player = glGetUniformLocation(shader->program, "position_player");
    glUniform3f(position_player, translateSkier.x, translateSkier.y, translateSkier.z);

    // TODO(student): Set any other shader uniforms that you need

    if (texture1)
    {
        // TODO(student): Do these:
        // - activate texture location 0
        // - bind the texture1 ID
        // - send theuniform value
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1->GetTextureID());
        glUniform1i(glGetUniformLocation(shader->program, "texture_1"), 0);
    }

    if (texture2)
    {
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2->GetTextureID());
        glUniform1i(glGetUniformLocation(shader->program, "texture_2"), 1);
    }

    int directional_light_position = glGetUniformLocation(shader->program, "directional_light_position");
    glUniform3f(directional_light_position, directionalLightPosition.x, directionalLightPosition.y, directionalLightPosition.z);

    int directional_light_direction = glGetUniformLocation(shader->program, "directional_light_direction");
    glUniform3f(directional_light_direction, directionalLightDirection.x, directionalLightDirection.y, directionalLightDirection.z);

    GLuint location1 = glGetUniformLocation(shader->program, "spotlight_position");
    glUniform3fv(location1, 201, glm::value_ptr(spotlightPosition[0]));

    int spotlight_direction = glGetUniformLocation(shader->program, "spotlight_direction");
    glUniform3f(spotlight_direction, spotlightDirection.x, spotlightDirection.y, spotlightDirection.z);

    // GLuint location3 = glGetUniformLocation(shader->program, "punctiform_position");
    // glUniform3fv(location3, 201, glm::value_ptr(punctiformPosition[0]));

    for (int i = 0; i < 201; ++i)
    {
        std::string name = std::string("punctiforms[") + std::to_string(i) + std::string("].coordinates");
        GLuint location = glGetUniformLocation(shader->program, name.c_str());
        glUniform3fv(location, 1, glm::value_ptr(punctiforms[i].coordinates));
    }

    for (int i = 0; i < 201; ++i)
    {
        std::string name = std::string("punctiforms[") + std::to_string(i) + std::string("].color");
        GLuint location = glGetUniformLocation(shader->program, name.c_str());
        glUniform3fv(location, 1, glm::value_ptr(punctiforms[i].color));
    }

    int punctiform_direction = glGetUniformLocation(shader->program, "punctiform_direction");
    glUniform3f(punctiform_direction, punctiformDirection.x, punctiformDirection.y, punctiformDirection.z);

    int nr_spotlight = glGetUniformLocation(shader->program, "nr_spotlight");
    glUniform1i(nr_spotlight, nrSpotlight);

    int nr_punctiform = glGetUniformLocation(shader->program, "nr_punctiform");
    glUniform1i(nr_punctiform, nrPunctiform);

    int cut_off = glGetUniformLocation(shader->program, "cut_off");
    glUniform1f(cut_off, cutOff);

    // Set eye position (camera position) uniform
    glm::vec3 eyePosition = camera->position;
    int eye_position = glGetUniformLocation(shader->program, "eye_position");
    glUniform3f(eye_position, eyePosition.x, eyePosition.y, eyePosition.z);

    // Set material property uniforms (shininess, kd, ks, object color) 
    int material_shininess = glGetUniformLocation(shader->program, "material_shininess");
    glUniform1i(material_shininess, materialShininess);

    int material_kd = glGetUniformLocation(shader->program, "material_kd");
    glUniform1f(material_kd, materialKd);

    int material_ks = glGetUniformLocation(shader->program, "material_ks");
    glUniform1f(material_ks, materialKs);

    // Draw the object
    glBindVertexArray(mesh->GetBuffers()->m_VAO);
    glDrawElements(mesh->GetDrawMode(), static_cast<int>(mesh->indices.size()), GL_UNSIGNED_INT, 0);
}

int Tema3::CheckInsideViewPort(glm::mat4 modelMatrix, glm::vec3 skierPosition) {
    glm::vec4 v_pos = modelMatrix * glm::vec4(skierPosition, 1.);
    return abs(v_pos.x) < v_pos.w &&
            abs(v_pos.y) < v_pos.w &&
            0 < v_pos.z &&
            v_pos.z < v_pos.w;
}

int Tema3::TypeObject() {
    int r = rand() % 3;

    return r;
}

void Tema3::DeleteObjects(glm::vec3 translateSkier) {
    for (int i = 0; i < objects.size(); i++) {
        glm::vec3 coordinatesObject = objects[i].coordinates;

        float distance = glm::distance(coordinatesObject, translateSkier);

        if (distance > deSpawnDistance) {
            if (objects[i].type == 0 || objects[i].type == 3) {
                for (int j = 0; j < nrPunctiform; j++) {
                    if (objects[i].type == 3) {
                        if (objects[i].coordinates.x == punctiforms[j].coordinates.x && objects[i].coordinates.y == (punctiforms[j].coordinates.y - 2) && objects[i].coordinates.z == (punctiforms[j].coordinates.z - 2)) {
                            punctiforms.erase(punctiforms.begin() + j);
                            punctiforms.push_back(punctiformObject(glm::vec3(0, 0, 0), glm::vec3(0, 0, 0)));
                            nrPunctiform--;
                            break;
                        }
                    }
                    else {
                        if (objects[i].coordinates.x == punctiforms[j].coordinates.x && objects[i].coordinates.y == (punctiforms[j].coordinates.y - 6) && objects[i].coordinates.z == (punctiforms[j].coordinates.z - 5)) {
                            punctiforms.erase(punctiforms.begin() + j);
                            punctiforms.push_back(punctiformObject(glm::vec3(0, 0, 0), glm::vec3(0, 0, 0)));
                            nrPunctiform--;
                            break;
                        }
                    }
                }
            }
            else if (objects[i].type == 2) {
                int foundSpotLight = 0;
                for (int j = 0; j < nrSpotlight; j++) {
                    if ((objects[i].coordinates.x == (spotlightPosition[j].x - 3) || objects[i].coordinates.x == (spotlightPosition[j].x + 3)) && objects[i].coordinates.y == (spotlightPosition[j].y - 20) && objects[i].coordinates.z == (spotlightPosition[j].z)) {
                        spotlightPosition[j] = glm::vec3(0, 0, 0);
                        foundSpotLight++;
                    }

                    if (foundSpotLight == 2) {
                        nrSpotlight -= 2;
                        break;
                    }
                }
            }
            objects.erase(objects.begin() + i);
            i--;
        }
    }
}

int Tema3::getNrSpawnedObjects() {
    int max = 10, min = 3;
    int range = max - min + 1;
    int numberObjects = rand() % range + min;

    return numberObjects;
}

int Tema3::getDistance() {
    int max = 7, min = 2;
    int range = max - min + 1;
    int dist = rand() % range + min;

    if (rand() % 2 == 1) {
        dist *= (-1);
    }

    return dist;
}

int Tema3::getCoordinate() {
    int max = 40, min = 0;
    int range = max - min + 1;
    int coordinate = rand() % range + min;

    if (rand() % 2 == 1) {
        coordinate *= (-1);
    }

    return coordinate;
}

bool Tema3::check(const int coordinate) {
    if (currentCoordinate == coordinate - 2 || currentCoordinate == coordinate - 1 || currentCoordinate == coordinate) {
        return true;
    }

    return false;
}

void Tema3::SpawnObjects(glm::vec3 translateSkier) {
    float spawnDistY = spawnDistance * sin(RADIANS(90 + angleSlope));
    float spawnDistZ = spawnDistance * cos(RADIANS(90 + angleSlope));

    int nrSpawnObjects = getNrSpawnedObjects();

    currentCoordinate = getCoordinate();
    int nrObj = 0;

    objects.push_back(object(glm::vec3(translateSkier.x + currentCoordinate, translateSkier.y - spawnDistY, translateSkier.z + spawnDistZ), 3));

    punctiforms[nrPunctiform].coordinates = glm::vec3(translateSkier.x + currentCoordinate, translateSkier.y - spawnDistY + 2, translateSkier.z + spawnDistZ + 2);
    punctiforms[nrPunctiform].color = glm::vec3(255, 0, 0) / 255.0f;
    nrPunctiform++;
    nrSpawnObjects--;

    vector<int> unavailable;
    unavailable.push_back(currentCoordinate);

    for (int i = 1; i <= 5; i++) {
        unavailable.push_back(currentCoordinate + i);
        unavailable.push_back(currentCoordinate - i);
    }

    while (nrSpawnObjects > 0 && unavailable.size() < 40) {
        currentCoordinate = getCoordinate();
        if (std::find(unavailable.begin(), unavailable.end(), currentCoordinate) == unavailable.end()) {
            int type = TypeObject();
            objects.push_back(object(glm::vec3(translateSkier.x + currentCoordinate, translateSkier.y - spawnDistY, translateSkier.z + spawnDistZ), type));

            if (type == 2) {
                spotlightPosition[nrSpotlight] = glm::vec3(translateSkier.x + currentCoordinate - 3, translateSkier.y - spawnDistY + 4, translateSkier.z + spawnDistZ + 8);
                spotlightPosition[nrSpotlight + 1] = glm::vec3(translateSkier.x + currentCoordinate + 3, translateSkier.y - spawnDistY + 20.f, translateSkier.z + spawnDistZ);

                nrSpotlight += 2;
                // cout << "Occupied coordinate by spotlight: " << currentCoordinate << "\n";
            }
            else if (type == 0) {
                punctiforms[nrPunctiform].coordinates = glm::vec3(translateSkier.x + currentCoordinate, translateSkier.y - spawnDistY + 6, translateSkier.z + spawnDistZ + 5);
                punctiforms[nrPunctiform].color = glm::vec3(46, 139, 87) / 255.0f;
                nrPunctiform++;
                // cout << "Occupied coordinate by punctiform: " << currentCoordinate << "\n\n";
            }

            unavailable.push_back(currentCoordinate);

            for (int i = 1; i <= 5; i++) {
                unavailable.push_back(currentCoordinate + i);
                unavailable.push_back(currentCoordinate - i);
            }

            nrSpawnObjects--;
        }

    }

   /* cout << "Spawning:\n";
    cout << "Number of spotlights: " << nrSpotlight << '\n';
    cout << "Number of punctiforms: " << nrPunctiform << '\n';
    cout << '\n';

    for (int i = 0; i < nrPunctiform; i++) {
        cout << punctiformPosition[i] << ' ';
    }

    cout << '\n';*/
}

int Tema3::checkCollission(glm::vec3 translateSkier) {
    for (int i = 0; i < objects.size(); i++) {
        float distance = sqrt(pow(translateSkier.x - objects[i].coordinates.x, 2) + pow(translateSkier.y - objects[i].coordinates.y, 2) +
            pow(translateSkier.z - objects[i].coordinates.z, 2));

        if (distance <= 2) {
            if (objects[i].type == 3) {
                score += 10;
                for (int j = 0; j < nrPunctiform; j++) {
                    if (objects[i].coordinates.x == punctiforms[j].coordinates.x && objects[i].coordinates.y == (punctiforms[j].coordinates.y - 2) && objects[i].coordinates.z == (punctiforms[j].coordinates.z - 2)) {
                        punctiforms.erase(punctiforms.begin() + j);
                        punctiforms.push_back(punctiformObject(glm::vec3(0, 0, 0), glm::vec3(0, 0, 0)));
                        nrPunctiform--;
                        // cout << "Deleted!\n\n";
                        break;
                    }
                }
                objects.erase(objects.begin() + i);
                i--;
            }
            else {
                return 1;
            }
        }
        else if (objects[i].type == 1) {
            float distance = sqrt(pow(translateSkier.x - (objects[i].coordinates.x + 2), 2) + pow(translateSkier.y - objects[i].coordinates.y, 2) +
                pow(translateSkier.z - objects[i].coordinates.z, 2));

            if (distance <= 2) {
                return 1;
            }
        }
    }

    return 0;
}

void Tema3::RenderScene(float deltaTimeSeconds) {
    {
        yesEarth = 1;
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix *= transforms3D::Translate(translateSkier.x, translateSkier.y, translateSkier.z);
        modelMatrix *= transforms3D::RotateOX(RADIANS(angleSlope));

        // RenderMesh(meshes["earth"], shaders["VertexColor"], modelMatrix);
        RenderSimpleMesh(meshes["earth"], shaders["Shader"], modelMatrix, mapTextures["snow"], mapTextures["snow"]);
        yesEarth = 0;
    }

    {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix *= transforms3D::Translate(translateSkier.x, translateSkier.y + 0.4f, translateSkier.z);
        modelMatrix *= transforms3D::RotateOX(RADIANS(90 + angleSlope));
        modelMatrix *= transforms3D::RotateOY(RADIANS(angleSkier));
        modelMatrix *= transforms3D::Scale(3, 5, 2);

        // RenderMesh(meshes["skier"], shaders["VertexColor"], modelMatrix);
        RenderSimpleMesh(meshes["cube"], shaders["Shader"], modelMatrix, mapTextures["Skier"], mapTextures["Skier"]);

        glm::mat4 playerMatrix = modelMatrix;

        if (ski) {
            // ski
            modelMatrix = playerMatrix;
            modelMatrix *= transforms3D::Translate(-0.4f, 0, 0);
            modelMatrix *= transforms3D::Scale(1, 0.2f, 8);
            modelMatrix *= transforms3D::Scale(1 / 3.0f, 1 / 5.0f, 1 / 2.0f);

            // RenderMesh(meshes["ski"], shaders["VertexColor"], modelMatrix);
            RenderSimpleMesh(meshes["cube"], shaders["Shader"], modelMatrix, mapTextures["Ski"], mapTextures["Ski"]);

            modelMatrix = playerMatrix;
            modelMatrix *= transforms3D::Translate(0.4f, 0, 0);
            modelMatrix *= transforms3D::Scale(1, 0.2f, 8);
            modelMatrix *= transforms3D::Scale(1 / 3.0f, 1 / 5.0f, 1 / 2.0f);

            // RenderMesh(meshes["ski"], shaders["VertexColor"], modelMatrix);
            RenderSimpleMesh(meshes["cube"], shaders["Shader"], modelMatrix, mapTextures["Ski"], mapTextures["Ski"]);
        }
        else {
            // snowboard
            modelMatrix = playerMatrix;
            modelMatrix *= transforms3D::Translate(0, 0, 0);
            modelMatrix *= transforms3D::Scale(3, 0.2f, 10);
            modelMatrix *= transforms3D::Scale(1 / 3.0f, 1 / 5.0f, 1 / 2.0f);

            // RenderMesh(meshes["ski"], shaders["VertexColor"], modelMatrix);
            RenderSimpleMesh(meshes["cube"], shaders["Shader"], modelMatrix, mapTextures["Snowboard"], mapTextures["Snowboard"]);
        }
    }

    {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix *= transforms3D::Translate(translateSkier.x, translateSkier.y + distanceSunY, translateSkier.z + distanceSunZ);
        modelMatrix *= transforms3D::Scale(20, 20, 20);
        RenderMesh(meshes["sphere"], shaders["Simple"], modelMatrix);

    }

    float distanceY = spawnDistanceY, distanceZ = spawnDistanceZ;
    float spawnDistY = spawnDistance * sin(RADIANS(90 + angleSlope));
    float spawnDistZ = spawnDistance * cos(RADIANS(90 + angleSlope));

    for (int i = 0; i < objects.size(); i++) {
        switch (objects[i].type) {
            case 0: // tree
                {
                    glm::mat4 modelMatrix = glm::mat4(1);
                    modelMatrix *= transforms3D::Translate(objects[i].coordinates.x, objects[i].coordinates.y, objects[i].coordinates.z);
                    glm::mat4 treeMatrix = modelMatrix;
                    modelMatrix *= transforms3D::Scale(2, 6, 2);

                    RenderSimpleMesh(meshes["cube"], shaders["Shader"], modelMatrix, mapTextures["Wood"], mapTextures["Wood"]);

                    modelMatrix = treeMatrix;
                    modelMatrix *= transforms3D::Translate(0, 10, 0);
                    modelMatrix *= transforms3D::Scale(5, 5, 5);

                    RenderSimpleMesh(meshes["cone"], shaders["Shader"], modelMatrix, mapTextures["PineTree"], mapTextures["PineTree"]);

                    modelMatrix = treeMatrix;
                    modelMatrix *= transforms3D::Translate(0, 14, 0);
                    modelMatrix *= transforms3D::Scale(3.5f, 3.5f, 3.5f);

                    RenderSimpleMesh(meshes["cone"], shaders["Shader"], modelMatrix, mapTextures["PineTree"], mapTextures["PineTree"]);
                }
                break;
            case 1: // rock
                {

                    glm::mat4 modelMatrix = glm::mat4(1);
                    modelMatrix *= transforms3D::Translate(objects[i].coordinates.x, objects[i].coordinates.y, objects[i].coordinates.z);
                    glm::mat4 rockMatrix = modelMatrix;
                    modelMatrix *= transforms3D::Scale(5, 4, 4);

                    RenderSimpleMesh(meshes["sphere"], shaders["Shader"], modelMatrix, mapTextures["Rock"], mapTextures["Rock"]);

                    modelMatrix = rockMatrix;
                    modelMatrix *= transforms3D::Translate(2, 0, 0);
                    modelMatrix *= transforms3D::Scale(6, 4.5f, 4.5f);

                    RenderSimpleMesh(meshes["sphere"], shaders["Shader"], modelMatrix, mapTextures["Rock"], mapTextures["Rock"]);
                }
                break;
            case 2: // pole
                {
                    glm::mat4 modelMatrix = glm::mat4(1);
                    modelMatrix *= transforms3D::Translate(objects[i].coordinates.x, objects[i].coordinates.y, objects[i].coordinates.z);
                    glm::mat4 poleMatrix = modelMatrix;
                    modelMatrix *= transforms3D::Scale(1, 20, 1);

                    RenderSimpleMesh(meshes["cube"], shaders["Shader"], modelMatrix, mapTextures["Metal"], mapTextures["Metal"]);

                    modelMatrix = poleMatrix;
                    modelMatrix *= transforms3D::Translate(0, 20, 0);
                    modelMatrix *= transforms3D::RotateOY(RADIANS(180));
                    modelMatrix *= transforms3D::Scale(8, 1, 2);

                    RenderSimpleMesh(meshes["cube"], shaders["Shader"], modelMatrix, mapTextures["Metal"], mapTextures["Metal"]);
                }
                break;
            case 3: // present
                {
                    glm::mat4 modelMatrix = glm::mat4(1);
                    modelMatrix *= transforms3D::Translate(objects[i].coordinates.x, objects[i].coordinates.y, objects[i].coordinates.z);
                    modelMatrix *= transforms3D::RotateOX(RADIANS(90 + angleSlope));
                    modelMatrix *= transforms3D::Scale(3, 3, 3);

                    RenderSimpleMesh(meshes["cube"], shaders["Shader"], modelMatrix, mapTextures["Present"], mapTextures["Present"]);
                }
                break;


        }
    }

    string scoreString = "Score: " + std::to_string(score);
    textRenderPlay.RenderText(scoreString, 10, 10, 0.3f, glm::vec3(70, 130, 180) / 255.0f);
}

void Tema3::Update(float deltaTimeSeconds)
{
    // Render the camera target. This is useful for understanding where
    // the rotation point is, when moving in third-person camera mode.
    if (menu_screen) {
        if (!choose) {
            textRenderTitle.RenderText("Ski Free!", startingResolutionX / 2 - 420, 150, 1.3f, glm::vec3(102, 153, 204) / 255.0f);
            textRenderPlay.RenderText("Play", startingResolutionX / 2 - 149, 350, 1.0f, glm::vec3(70, 130, 180) / 255.0f);
            textRenderPlay.RenderText("Click Play to start the game", 325, startingResolutionY - 220, 0.3f, glm::vec3(70, 130, 180) / 255.0f);
            textRenderSki.RenderText("abcdefghijkl", 5, startingResolutionX - 10, 0.3f, glm::vec3(70, 130, 180) / 255.0f);
        }
        else {
            textRenderPlay.RenderText("Choose your equipment", 0.2f * startingResolutionX, 10, 0.5f, glm::vec3(70, 130, 180) / 255.0f);
            textRenderChoose.RenderText("Ski", 0.5f * startingResolutionX - 70, (1 / 3.0f) * startingResolutionY - 50, 1.5f, glm::vec3(70, 130, 180) / 255.0f);
            textRenderChoose.RenderText("Snowboard", 0.3f * startingResolutionX - 30, (2 / 3.0f) * startingResolutionY - 30, 1.5f, glm::vec3(70, 130, 180) / 255.0f);
        }
    } else if (!crash) {
        if (activeTime > 5 || activeTime == 0) {
            SpawnObjects(translateSkier);
            activeTime = 0;
        }

        crash = checkCollission(translateSkier);

        RenderScene(deltaTimeSeconds);

        translateSkier.z += cos(RADIANS(90 + angleSlope)) * speedSkier * deltaTimeSeconds;
        translateSkier.y -= sin(RADIANS(90 + angleSlope)) * speedSkier * deltaTimeSeconds;
        translateSkier.x += sin(RADIANS(angleSkier)) * speedRotate * deltaTimeSeconds;

        DeleteObjects(translateSkier);

        directionalLightPosition = glm::vec3(0, distanceSunY, distanceSunZ);
        directionalLightDirection = glm::vec3(0, -1, 0);

        activeTime += deltaTimeSeconds;

        camera->Set(glm::vec3(translateSkier.x, translateSkier.y + yCamera, translateSkier.z + zCamera), glm::vec3(translateSkier.x, translateSkier.y, translateSkier.z), glm::vec3(0, 1, 0));
    }
    else {
        textRenderFail.RenderText("YOU CRASHED!", 0.13f * startingResolutionX, 0.2f * startingResolutionY, 1.0f, glm::vec3(1, 0, 0));
        string scoreString = "Score: " + std::to_string(score);
        textRenderPlay.RenderText(scoreString, startingResolutionX / 2.6f - 20, 0.40f * startingResolutionY, 0.6f, glm::vec3(255.0f, 99.0f, 71.0f) / 255.0f);
        textRenderPlay.RenderText("Restart", startingResolutionX / 3.0f, 0.53f * startingResolutionY, 0.8f, glm::vec3(255.0f, 99.0f, 71.0f) / 255.0f);
        textRenderFrozen.RenderText("You froze to death", startingResolutionX * 0.06f, startingResolutionY - 200, 0.9f, glm::vec3(227.0f, 66.0f, 52.0f) / 255.0f);
    }
}


void Tema3::FrameEnd()
{
    // DrawCoordinateSystem(camera->GetViewMatrix(), projectionMatrix);
}


void Tema3::RenderMesh(Mesh * mesh, Shader * shader, const glm::mat4 & modelMatrix)
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


void Tema3::OnInputUpdate(float deltaTime, int mods)
{
    // move the camera only if MOUSE_RIGHT button is pressed
    if (window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT))
    {
        float cameraSpeed = 15.0f;

        if (window->KeyHold(GLFW_KEY_W)) {
            // TODO(student): Translate the camera forward
            camera->TranslateForward(deltaTime * cameraSpeed);
        }

        if (window->KeyHold(GLFW_KEY_A)) {
            // TODO(student): Translate the camera to the left
            camera->TranslateRight((-1) * deltaTime * cameraSpeed);
        }

        if (window->KeyHold(GLFW_KEY_S)) {
            // TODO(student): Translate the camera backward
            camera->TranslateForward((-1) * deltaTime * cameraSpeed);
        }

        if (window->KeyHold(GLFW_KEY_D)) {
            // TODO(student): Translate the camera to the right
            camera->TranslateRight(deltaTime * cameraSpeed);
        }

        if (window->KeyHold(GLFW_KEY_Q)) {
            // TODO(student): Translate the camera downward
            camera->TranslateUpward((-1) * deltaTime * cameraSpeed);
        }

        if (window->KeyHold(GLFW_KEY_E)) {
            // TODO(student): Translate the camera upward
            camera->TranslateUpward(deltaTime * cameraSpeed);
        }
    }

    // TODO(student): Change projection parameters. Declare any extra
    // variables you might need in the class header. Inspect this file
    // for any hardcoded projection arguments (can you find any?) and
    // replace them with those extra variables.
    if (window->KeyHold(GLFW_KEY_1)) {
        fov += deltaTime;

        if (!ortho) {
            projectionMatrix = glm::perspective(fov, aspect, zNear, zFar);
        }
    }
    else if (window->KeyHold(GLFW_KEY_2)) {
        fov -= deltaTime;

        if (!ortho) {
            projectionMatrix = glm::perspective(fov, aspect, zNear, zFar);
        }
    }
    if (window->KeyHold(GLFW_KEY_DOWN)) {
        top += deltaTime * 20;
        bottom -= deltaTime * 20;

        if (ortho) {
            projectionMatrix = glm::ortho(left, right, bottom, top, zNear, zFar);
        }
    }
    else if (window->KeyHold(GLFW_KEY_UP)) {
        top -= deltaTime * 20;
        bottom += deltaTime * 20;

        if (ortho) {
            projectionMatrix = glm::ortho(left, right, bottom, top, zNear, zFar);
        }
    }
    if (window->KeyHold(GLFW_KEY_LEFT)) {
        right += deltaTime * 20;
        left -= deltaTime * 20;

        if (ortho) {
            projectionMatrix = glm::ortho(left, right, bottom, top, zNear, zFar);
        }
    } else if (window->KeyHold(GLFW_KEY_RIGHT)) {
        right -= deltaTime * 20;
        left += deltaTime * 20;

        if (ortho) {
            projectionMatrix = glm::ortho(left, right, bottom, top, zNear, zFar);
        }
    }
}


void Tema3::OnKeyPress(int key, int mods)
{
    // Add key press event
    if (key == GLFW_KEY_T)
    {
        renderCameraTarget = !renderCameraTarget;
    }
    // TODO(student): Switch projections

    if (key == GLFW_KEY_P) {
        projectionMatrix = glm::perspective(fov, aspect, zNear, zFar);
    }
    if (key == GLFW_KEY_O) {
        projectionMatrix = glm::ortho(left, right, bottom, top, zNear, zFar);
        ortho = 1;
    }
}


void Tema3::OnKeyRelease(int key, int mods)
{
    // Add key release event
}


void Tema3::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
    // Add mouse move event

    if (window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT))
    {
        float sensivityOX = 0.001f;
        float sensivityOY = 0.001f;

        if (window->GetSpecialKeyState() == 0) {
            renderCameraTarget = false;
            // TODO(student): Rotate the camera in first-person mode around
            // OX and OY using `deltaX` and `deltaY`. Use the sensitivity
            // variables for setting up the rotation speed.
            camera->RotateFirstPerson_OX((-1) * sensivityOX * deltaY);
            camera->RotateFirstPerson_OY((-1) * sensivityOY * deltaX);
        }

        if (window->GetSpecialKeyState() & GLFW_MOD_CONTROL) {
            renderCameraTarget = true;
            // TODO(student): Rotate the camera in third-person mode around
            // OX and OY using `deltaX` and `deltaY`. Use the sensitivity
            // variables for setting up the rotation speed.
            camera->RotateThirdPerson_OX((-1) * sensivityOX * deltaY);
            camera->RotateThirdPerson_OY((-1) * sensivityOY * deltaX);
        }
    }
    else {
        angleSkier = mouseX / (float) window->GetResolution().x * 2.0f * 45 - 45;

        if (angleSkier < 0) {
            yesRight = 0;
        }
        else if (angleSkier > 0) {
            yesRight = 1;
        }
        else {
            yesRight = -1;
        }
    }
}


void Tema3::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button press event
    if (IS_BIT_SET(button, GLFW_MOUSE_BUTTON_LEFT) && menu_screen && !choose) {
        // start game case
        float scaleFactorX = window->GetResolution().x / startingResolutionX;
        float scaleFactorY = window->GetResolution().y / startingResolutionY;

        float playCoordinateX = (startingResolutionX / 2 - 142) * scaleFactorX;
        float playCoordinateY = (startingResolutionY - 470) * scaleFactorY;

        if (mouseX >= playCoordinateX && mouseX <= playCoordinateX + 300 * scaleFactorX) {
            float difference = (float)(window->GetResolution().y - mouseY);

            if (difference >= playCoordinateY && difference <= playCoordinateY + 126 * scaleFactorY) {
                choose = 1;
                /*skyRed = 32 / 255.0f;
                skyGreen = 42 / 255.0f;
                skyBlue = 68 / 255.0f;*/
            }
        }
    }
    else if (IS_BIT_SET(button, GLFW_MOUSE_BUTTON_LEFT) && choose) {
        if (IS_BIT_SET(button, GLFW_MOUSE_BUTTON_LEFT) && choose) {
            float scaleFactorX = window->GetResolution().x / startingResolutionX;
            float scaleFactorY = window->GetResolution().y / startingResolutionY;

            float skiCoordinateX = (0.3f * startingResolutionX + 182) * scaleFactorX;
            float skiCoordinateY = ((2 / 3.0f) * startingResolutionY - 102) * scaleFactorY;

            float snowboardCoordinateX = (0.5f * startingResolutionX - 290) * scaleFactorX;
            float snowboardCoordinateY = ((1 / 3.0f) * startingResolutionY - 124) * scaleFactorY;

            if (mouseX >= skiCoordinateX && mouseX <= skiCoordinateX + 152 * scaleFactorX) {
                float difference = (float)(window->GetResolution().y - mouseY);
                if (difference >= skiCoordinateY && difference <= skiCoordinateY + 151 * scaleFactorY) {
                    choose = 0;
                    menu_screen = 0;
                    ski = 1;
                }
            }
            if (mouseX >= snowboardCoordinateX && mouseX <= snowboardCoordinateX + 615 * scaleFactorX) {
                float difference = (float)(window->GetResolution().y - mouseY);
                if (difference >= snowboardCoordinateY && difference <= snowboardCoordinateY + 152 * scaleFactorY) {
                    choose = 0;
                    menu_screen = 0;
                    ski = 0;
                }
            }
        }
    }
    else if (IS_BIT_SET(button, GLFW_MOUSE_BUTTON_LEFT) && crash) {
        float scaleFactorX = window->GetResolution().x / startingResolutionX;
        float scaleFactorY = window->GetResolution().y / startingResolutionY;

        float restartCoordinateX = (startingResolutionX / 3.0f) * scaleFactorX;
        float restartCoordinateY = (startingResolutionY * 0.36f) * scaleFactorY;

        if (mouseX >= restartCoordinateX && mouseX <= restartCoordinateX + 300 * 1.45f * scaleFactorX) {
            float difference = (float)(window->GetResolution().y - mouseY);

            if (difference >= restartCoordinateY && difference <= restartCoordinateY + 126 * 0.65f * scaleFactorX) {
                crash = 0;
                menu_screen = 1;
                choose = 1;

                for (int i = objects.size() - 1; i >= 0; i--) {
                    objects.erase(objects.begin() + i);
                }

                for (int i = 0; i < 201; i++) {
                    spotlightPosition[i] = glm::vec3(0, 0, 0);
                    punctiforms[i].coordinates = glm::vec3(0, 0, 0);
                    punctiforms[i].color = glm::vec3(0, 0, 0);
                }

                nrPunctiform = 0;
                nrSpotlight = 0;

                translateSkier = glm::vec3(0, 0, 0);
            }
        }
    }
}


void Tema3::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button release event
}


void Tema3::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}


void Tema3::OnWindowResize(int width, int height)
{
}
