#pragma once

#include "components/simple_scene.h"
#include "lab_m1/Tema2/Tema2_camera.h"
#include "lab_m1/Tema2/createObject.h"
#include "lab_m1/Tema2/transformations3D.h"
#include <vector>

#include "components/simple_scene.h"
#include "components/text_renderer.h"

namespace m1
{
    class Tema2 : public gfxc::SimpleScene
    {
     public:
         struct ViewportArea
         {
             ViewportArea() : x(0), y(0), width(1), height(1) {}
             ViewportArea(int x, int y, int width, int height)
                 : x(x), y(y), width(width), height(height) {}
             int x;
             int y;
             int width;
             int height;
         };

        Tema2();
        ~Tema2();

        void Init() override;

     private:
        void FrameStart() override;
        void Update(float deltaTimeSeconds) override;
        void FrameEnd() override;

        void RenderMesh(Mesh *mesh, Shader *shader, const glm::mat4 &modelMatrix) override;

        void OnInputUpdate(float deltaTime, int mods) override;
        void OnKeyPress(int key, int mods) override;
        void OnKeyRelease(int key, int mods) override;
        void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
        void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
        void OnWindowResize(int width, int height) override;

        Mesh* CreateMesh(const char* name, const std::vector<VertexFormat>& vertices, const std::vector<unsigned int>& indices);
        void RenderSimpleMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix);
        int checkInBoundsVector(glm::vec3 currentPosition, glm::vec3 nextPosition);
        int checkSign(float x);
        int checkInRaceTrackBounds(glm::vec3 carPosition);
        void moveEnemy(int enemy_index, float deltaTimeSeconds, int startingPoint);
        int checkCollision(glm::vec3 positionCar);
        void RenderScene(float deltaTimeSeconds);
        void calculateEnemyPositionDistances(int enemy_position);
        float triangleArea(glm::vec3 pA, glm::vec3 pB, glm::vec3 pC);
        int checkInsideTriangle(glm::vec3 P, glm::vec3 A, glm::vec3 B, glm::vec3 C, float ABC_triangleArea);
        void RemoveTrees();

     protected:
        implemented::Cam *camera, *orthoCamera, *speedCamera, *prev_camera, *global_camera;
        glm::mat4 projectionMatrix;
        bool renderCameraTarget;

        ViewportArea miniViewportArea, speedViewport;

        float fov, aspect, left = -200.0f, right = 200.0f, zNear = 0.01f, zFar = 1500.0f, top = 200.0f, bottom = -200.0f, zNearOrtho = -400.0f, zFarOrtho = 400.0f;
        int ortho = 0;
        float skyRed = 56 / 255.0f, skyGreen = 40 / 255.0f, skyBlue = 92 / 255.0f;
        // float skyRed = 0.678f, skyGreen = 0.847f, skyBlue = 0.902f;
        float speed = 100.0f, originalSpeed = 100.0f, speedRotation = 3.0f, speedEnemy[6];
        glm::vec3 translateCar, centerCar, forwardCar, prevPositionCar;
        glm::vec3 translateEnemy[6], centerEnemy[6];
        std::vector<glm::vec3> marginPoints;
        float rotateAngle = 0;
        float scaleFactor = 0.00022f, raceTrackScale = 300.0f;
        Mesh* raceTrack;
        std::vector<glm::vec3> treePositions, enemyCarPositions[3];
        float carHeight = 8, carWidth = 8, carLength = 10;
        int distance_index_enemy_position[6], next_index_enemy_position[6];
        float enemy_angle[6];
        int nr_positions_enemies;
        float height_camera = 12, x_dist_camera = 35, z_dist_camera = 0, height_ortho_camera = 10;
        float dist_camera = 37, dist_ortho_camera = 100;
        int current_index = 0;
        std::vector<float> enemy_distances[6];
        std::vector<float> triangle_areas;
        float current_triangle_index = 0;
        float yCoordinate;
        GLenum polygonMode;

        std::vector<int> indices_racetrack_margins;

        gfxc::TextRenderer textRenderTitle = gfxc::TextRenderer(window->props.selfDir, window->GetResolution().x, window->GetResolution().y);
        gfxc::TextRenderer textRenderCount = gfxc::TextRenderer(window->props.selfDir, window->GetResolution().x, window->GetResolution().y);
        gfxc::TextRenderer textRenderPlay = gfxc::TextRenderer(window->props.selfDir, window->GetResolution().x, window->GetResolution().y);

        float startingResolutionX, startingResolutionY;
        int startGame = 0, menu_screen = 1, showSquare = 0, up = 0, pressed = 0;
        float activeTime = 0, scaleBarY = 0.3f;

        glm::vec3 pagodaPosition, FujiPosition, templeGatePosition, tokyoTowerPosition, japaneseTemplePosition;
    };
}   // namespace m1
