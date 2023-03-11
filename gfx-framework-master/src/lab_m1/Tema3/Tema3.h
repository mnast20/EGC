#pragma once

#include "components/simple_scene.h"
#include "lab_m1/Tema3/Tema3_camera.h"
#include "lab_m1/Tema3/createObj.h"
#include "lab_m1/Tema3/transforms3D.h"
#include "components/text_renderer.h"

namespace m1
{
    class Tema3 : public gfxc::SimpleScene
    {
     public:
        Tema3();
        ~Tema3();

        void Init() override;

        struct object {
            glm::vec3 coordinates;
            int type;

            object(glm::vec3 coord, int tp) {
                coordinates = coord;
                type = tp;
            }
        };

        struct punctiformObject {
            glm::vec3 coordinates;
            glm::vec3 color;

            punctiformObject(glm::vec3 coord, glm::vec3 colorObj) {
                coordinates = coord;
                color = colorObj;
            }
        };

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

        void RenderScene(float deltaTimeSeconds);
        void RenderSimpleMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix, Texture2D* texture1, Texture2D* texture2);
        int CheckInsideViewPort(glm::mat4 modelMatrix, glm::vec3 skierPosition);
        int TypeObject();
        int getNrSpawnedObjects();
        int getDistance();
        int getCoordinate();
        void SpawnObjects(glm::vec3 translateSkier);
        void DeleteObjects(glm::vec3 translateSkier);
        int checkCollission(glm::vec3 translateSkier);
        bool check(int coordinate);

     protected:
        implemented::Tema3_Camera *camera;
        glm::mat4 projectionMatrix;
        bool renderCameraTarget;
        glm::vec3 translateSkier = glm::vec3(0, 0, 0);
        float angleSkier = 0, angleSlope = -30;
        float speedSkier = 5, speedRotate = 15;
        glm::vec3 forwardSkier = glm::vec3(0, sin(RADIANS(-30)), 0);
        float distanceCamera = 37, yCamera = 35, zCamera = 12;
        int crash = 0;
        float distanceSunY = 80, distanceSunZ = 30;
        int menu_screen = 1;
        float skyRed = 173 / 255.0f, skyGreen = 216 / 255.0f, skyBlue = 230 / 255.0f;
        std::vector<glm::vec3> spotlightPosition, punctiformPosition;
        glm::vec3 spotlightDirection = glm::vec3(1, -1, -1), punctiformDirection = glm::vec3(0, 0, 0);
        glm::vec3 directionalLightPosition, directionalLightDirection = glm::vec3(0, -1, 0);
        float materialShininess = 0.5f, materialKd = 0.1, materialKs = 0.5;
        int spotLight[1];
        std::vector<object> objects;
        std::vector<punctiformObject> punctiforms;
        float deSpawnDistance = 70;
        float spawnDistanceY = 50, spawnDistanceZ = 5, spawnDistance = 50;
        float activeTime = 0;
        int score = 0;
        int nrSpotlight = 0, nrPunctiform = 0;
        std::vector<int> types;
        int yesEarth = 0, ski = 1;
        int yesRight = -1;
        int choose = 0;

        float fov, left = -30.0f, right = 30.0f, zNear = 0.01f, zFar = 200.0f, top = 20.0f, bottom = -10.0f, aspect;
        int ortho = 0;
        float cutOff = 60;
        int currentCoordinate = 0;

        float startingResolutionX;
        float startingResolutionY;

        std::unordered_map<std::string, Texture2D*> mapTextures;
        GLint minFilter, magFilter, wrappingMode;

        gfxc::TextRenderer textRenderTitle = gfxc::TextRenderer(window->props.selfDir, window->GetResolution().x, window->GetResolution().y);
        gfxc::TextRenderer textRenderPlay = gfxc::TextRenderer(window->props.selfDir, window->GetResolution().x, window->GetResolution().y);
        gfxc::TextRenderer textRenderFail = gfxc::TextRenderer(window->props.selfDir, window->GetResolution().x, window->GetResolution().y);
        gfxc::TextRenderer textRenderFrozen = gfxc::TextRenderer(window->props.selfDir, window->GetResolution().x, window->GetResolution().y);
        gfxc::TextRenderer textRenderChoose = gfxc::TextRenderer(window->props.selfDir, window->GetResolution().x, window->GetResolution().y);
        gfxc::TextRenderer textRenderSki = gfxc::TextRenderer(window->props.selfDir, window->GetResolution().x, window->GetResolution().y);
    };
}   // namespace m1
