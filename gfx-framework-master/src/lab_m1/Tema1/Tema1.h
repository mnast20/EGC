#pragma once

#include "components/simple_scene.h"
#include "components/text_renderer.h"


namespace m1
{
    class Tema1 : public gfxc::SimpleScene
    {
    public:
        Tema1();
        ~Tema1();

        void Init() override;

    private:
        void FrameStart() override;
        void Update(float deltaTimeSeconds) override;
        void FrameEnd() override;

        void OnInputUpdate(float deltaTime, int mods) override;
        void OnKeyPress(int key, int mods) override;
        void OnKeyRelease(int key, int mods) override;
        void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
        void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
        void OnWindowResize(int width, int height) override;

        float RandomCoordinate(glm::ivec2 resolution, int squareSide);
        int RandomDirection();
        int RandomAngle();

    protected:
        // matrices
        glm::mat3 modelMatrix = glm::mat3(0), modelMatrixWing = glm::mat3(0), modelMatrixDuck = glm::mat3(0);

        int squareSide = 0;

        // duck translate factor
        float translateX = 0, translateY = 0;

        // duck active time
        float activeTime = 0;

        int playFailSound = 0;
        int playVictorySound = 0;

        // number of used bullets and used lives
        int used_bullets = 0;
        int used_lives = 0;

        // duck states
        int start_duck = 0;
        int escape = 0;
        int dead_duck = 0;

        // time of escape related variables
        float escapeTime = 0;
        int checkEscapeTime = 1;

        // angles and coordinates
        float angle = 0;
        int wingAngle = 0;
        float randomCoordinate = 0;

        // movement directions
        int move_right = 0;
        int move_up = 0;
        int nrDucks = 0;
        int up = 1;

        // speed
        int speed = 0;
        int originalSpeed = 350;
        int startGame = 0;

        // score variables
        int score = 0, maxScore = 1000;

        // game won variable
        int win = 0;
        
        int showSquare = 0;

        // cloud coordinates
        float translateXCloud1 = 0, translateXCloud2 = 0, translateXCloud3 = 0;

        // starting resolution
        float startingResolutionX = 0, startingResolutionY = 0;
        float speedEscape = 300;

        // sky/background colours
        float skyRed = 0.678f, skyGreen = 0.847f, skyBlue = 0.902f;

        // mouse coodinates
        float mouseCoordinateX = 0, mouseCoordinateY = 0;

        // text renderers
        gfxc::TextRenderer textRenderTitle = gfxc::TextRenderer(window->props.selfDir, window->GetResolution().x, window->GetResolution().y);
        gfxc::TextRenderer textRenderPlay = gfxc::TextRenderer(window->props.selfDir, window->GetResolution().x, window->GetResolution().y);
        gfxc::TextRenderer textRenderVictory = gfxc::TextRenderer(window->props.selfDir, window->GetResolution().x, window->GetResolution().y);
        gfxc::TextRenderer textRenderFail = gfxc::TextRenderer(window->props.selfDir, window->GetResolution().x, window->GetResolution().y);
        gfxc::TextRenderer textRenderDuck = gfxc::TextRenderer(window->props.selfDir, window->GetResolution().x, window->GetResolution().y);
    };
}   // namespace m1
