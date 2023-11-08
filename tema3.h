#pragma once

#include "components/simple_scene.h"
#include "components/transform.h"
#include "lab_m1/tema3/object_t3.h"


namespace m1
{
    class Tema3 : public gfxc::SimpleScene
    {
    public:
        Tema3();
        ~Tema3();

        void Init() override;

    private:
        void FrameStart() override;
        void Update(float deltaTimeSeconds) override;
        void FrameEnd() override;

        void RenderSimpleMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix, const glm::vec3& color, const glm::vec3 lightColor[9], const glm::vec3 lightPosition[9], Texture2D* texture1 = NULL);
        void RenderSimpleMesh2(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix, const glm::vec3& color);
        void RenderMesh2Dd(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix, const glm::vec4& color);
        void RenderSimpleMeshT(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix, Texture2D* texture1 = NULL, Texture2D* texture2 = NULL);



        void GenerateDancer(glm::vec3& cubePosition, glm::vec3 lightColor[9], glm::vec3 lightPosition[9], glm::vec3 cubelightColor[8][8]);



        void OnInputUpdate(float deltaTime, int mods) override;
        void OnKeyPress(int key, int mods) override;
        void OnKeyRelease(int key, int mods) override;
        void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
        void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
        void OnWindowResize(int width, int height) override;
        void MoveDancer(float deltaTime, int &direction, glm::vec3 *cubePosition, int &step);
        void MoveLight(float deltaTime, int& direction, float angle, float cx, float cy, glm::vec3* cubePosition, int& step);
        Texture2D* CreateRandomTexture(unsigned int width, unsigned int height);


        struct Square
        {
            glm::vec3 position;
            glm::vec3 color;
            glm::vec3 lightPosition;
        };
        std::vector<Square> squares;
        
        glm::vec3 lightPosition[9];
        glm::vec3 lightColor[9];
        glm::vec3 cubelightColor[8][8];

        glm::vec3 spotlightPosition;
        glm::vec3 spotlightColor;
        glm::vec3 spotlightDirection;
            
        glm::vec3 spotlightPosition1;
        glm::vec3 spotlightColor1;

        glm::vec3 spotlightPosition2;
        glm::vec3 spotlightColor2;

        glm::vec3 spotlightPosition3;
        glm::vec3 spotlightColor3;


        glm::vec3 floorlightPosition;
        glm::vec3 floorlightColor;
        glm::vec3 cubePosition;
        glm::vec3 cubePosition1;
        glm::vec3 cubePosition2;
        glm::vec3 cubePosition3;


        glm::vec3 lightDirection;
        unsigned int materialShininess;
        float materialKd;
        float materialKs;
        float materialKe;
        float materialKa;
        int sceneType;
        int direction;
        int direction1;
        int direction2;
        int direction3;
        int spotDirection;
        int spotDirection1;
        int spotDirection2;
        int spotDirection3;
        int stepSpot;
        int stepSpot1;
        int stepSpot2;
        int stepSpot3;
        int f;

        std::unordered_map<std::string, Texture2D*> mapTextures;

        float time;

        int step;
        int step1;
        int step2;
        int step3;


        
      
        int typeOfLight;

        // TODO(student): If you need any other class variables, define them here.

    };
}   // namespace m1
