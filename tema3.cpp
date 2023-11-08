#include "lab_m1/tema3/tema3.h"

#include <vector>
#include <string>
#include <iostream>

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
    {
        Mesh* mesh = new Mesh("box");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "box.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }

    {
        Mesh* mesh = new Mesh("sphere");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "sphere.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }

    {
        Mesh* mesh = new Mesh("plane");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "plane50.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }

    {
        mapTextures["random"] = CreateRandomTexture(25, 25);
    }

    // Create a shader program for drawing face polygon with the color of the normal
    {
        Shader* shader = new Shader("LabShader");
        shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "tema3",  "VertexShader.glsl"), GL_VERTEX_SHADER);
        shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "tema3",  "FragmentShader.glsl"), GL_FRAGMENT_SHADER);
        shader->CreateAndLink();
        shaders[shader->GetName()] = shader;
    }

    {
        Shader* shader = new Shader("Floor");
        shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "tema3", "FloorVS.glsl"), GL_VERTEX_SHADER);
        shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "tema3", "FloorFS.glsl"), GL_FRAGMENT_SHADER);
        shader->CreateAndLink();
        shaders[shader->GetName()] = shader;
    }

    {
        Shader* shader = new Shader("CircleColor");
        shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "tema3", "ColorVS.glsl"), GL_VERTEX_SHADER);
        shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "tema3", "ColorFS.glsl"), GL_FRAGMENT_SHADER);
        shader->CreateAndLink();
        shaders[shader->GetName()] = shader;
    }

    {
        Shader* shader = new Shader("SphereShader");
        shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "tema3", "SphereVS.glsl"), GL_VERTEX_SHADER);
        shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "tema3", "SphereFS.glsl"), GL_FRAGMENT_SHADER);
        shader->CreateAndLink();
        shaders[shader->GetName()] = shader;
    }


    for (int i = 0; i < 8; i++){
        for (int j = 0; j < 8; j++) {
            float r = ((double)rand() / RAND_MAX);
            float g = ((double)rand() / RAND_MAX);
            float b = ((double)rand() / RAND_MAX);
            Square s;
            s.position = glm::vec3(i, 0, j);
            s.color = glm::vec3(r, g, b);
            cubelightColor[i][j] = s.color;
            squares.push_back(s);
        }
    }

    {
      
        int pos_x = rand() % 3;
        int pos_z = rand() % 3;

        int pos_x1 = 4 + rand() % 3;
        int pos_z1 = rand() % 3;

        int pos_x2 = rand() % 3;
        int pos_z2 = 4 + rand() % 3;

        int pos_x3 = 4+ rand() % 3;
        int pos_z3 = 4 + rand() % 3;

        cubePosition = glm::vec3(pos_x, 0.5, pos_z);
        cubePosition1 = glm::vec3(pos_x1, 0.5, pos_z1);
        cubePosition2 = glm::vec3(pos_x2, 0.5, pos_z2);
        cubePosition3 = glm::vec3(pos_x3, 0.5, pos_z3);


      
        lightDirection = glm::vec3(0, 1, 0);
        //lightDirection = glm::vec3(0, 1, 0);

      
        materialShininess = 30;
        materialKd = 0.5;
        materialKs = 0.5;
        typeOfLight = 1;

        spotlightColor = glm::vec3(1, 0, 0);
        spotlightPosition = glm::vec3(2, 1.5, 2);

        spotlightColor1 = glm::vec3(0, 0, 1);
        spotlightPosition1 = glm::vec3(3, 1.5, 3);

        spotlightColor2 = glm::vec3(0.3, 0.3, 0.7);
        spotlightPosition2 = glm::vec3(3, 1.5, 5);

        spotlightColor3 = glm::vec3(1, 0.5, 0);
        spotlightPosition3 = glm::vec3(6, 1.5, 2);

        spotlightDirection = glm::vec3(0, -1, 0);
    }
    direction = 1;
    direction1 = 2;
    direction2 = 3;
    direction3 = 4;

     spotDirection = 2;
     spotDirection1 = 1;
     spotDirection2 = 3;
     spotDirection3 = 4;
     stepSpot = 50;
     stepSpot1 = 160;
     stepSpot2 = 30;
     stepSpot3 = 89;

     time = 0;

    step = 20;  
    step1 = 100;
    step2 = 250;
    step3 = 50;
    sceneType = 1;
    f = 2 + rand() % 7;


}


void Tema3::FrameStart()
{
    // Clears the color buffer (using the previously set color) and depth buffer
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::ivec2 resolution = window->GetResolution();
    // Sets the screen area where to draw
    glViewport(0, 0, resolution.x, resolution.y);
}
void Tema3::GenerateDancer(glm::vec3 &cubePosition, glm::vec3 lightColor[9], glm::vec3 lightPosition[9], glm::vec3 cubelightColor[8][8]) {
    glm::mat4 modelMatrix = glm::mat4(1);
    modelMatrix = glm::translate(modelMatrix, cubePosition);
    modelMatrix = glm::scale(modelMatrix, glm::vec3(0.5,1, 0.5));
    int x = (int)round(cubePosition.x);
    int z = (int)round(cubePosition.z);


    if (x != 0 && z != 7) {
        lightColor[0] = cubelightColor[x - 1][z - 1];
    }
    else {
        lightColor[0] = glm::vec3(0, 0, 0);
    }
    if (x != 0) {

        lightColor[1] = cubelightColor[x - 1][z];
    }
    else {
        lightColor[1] = glm::vec3(0, 0, 0);
    }
    if (x != 0 && z != 7) {

        lightColor[2] = cubelightColor[x - 1][z + 1];
    }
    else {
        lightColor[2] = glm::vec3(0, 0, 0);
    }
    if (z != 0) {

        lightColor[3] = cubelightColor[x][z - 1];
    }
    else {
        lightColor[3] = glm::vec3(0, 0, 0);
    }

    lightColor[4] = cubelightColor[x][z];
    if (z != 7) {

        lightColor[5] = cubelightColor[x][z + 1];
    }
    else {
        lightColor[5] = glm::vec3(0, 0, 0);
    }
    if (x != 7 && z != 0) {

        lightColor[6] = cubelightColor[x + 1][z - 1];
    }
    else {
        lightColor[6] = glm::vec3(0, 0, 0);
    }
    if (x != 7) {

        lightColor[7] = cubelightColor[x + 1][z];
    }
    else {
        lightColor[7] = glm::vec3(0, 0, 0);
    }
    if (x != 7 && z != 7) {

        lightColor[8] = cubelightColor[x + 1][z + 1];
    }
    else {
        lightColor[8] = glm::vec3(0, 0, 0);

    }


    lightPosition[0] = glm::vec3(x - 1, 0, z - 1);
    lightPosition[1] = glm::vec3(x - 1, 0, z);
    lightPosition[2] = glm::vec3(x - 1, 0, z + 1);
    lightPosition[3] = glm::vec3(x, 0, z - 1);
    lightPosition[4] = glm::vec3(x, 0, z);
    lightPosition[5] = glm::vec3(x, 0, z + 1);
    lightPosition[6] = glm::vec3(x + 1, 0, z - 1);
    lightPosition[7] = glm::vec3(x + 1, 0, z);
    lightPosition[8] = glm::vec3(x + 1, 0, z + 1);

    // modelMatrix = glm::rotate(modelMatrix, RADIANS(60.0f), glm::vec3(1, 1, 0));
    RenderSimpleMesh(meshes["box"], shaders["LabShader"], modelMatrix, glm::vec3(0.25, 0.75, 0.75), lightColor, lightPosition);
}

void Tema3::Update(float deltaTimeSeconds)
{
    time += deltaTimeSeconds;

    Mesh* cerc = object_new::CreateCircle("cerc", glm::vec3(spotlightPosition.x, 5, spotlightPosition.z), 0.8, spotlightColor, 360, true);
    AddMeshToList(cerc);
    Mesh* cerc1 = object_new::CreateCircle("cerc1", glm::vec3(spotlightPosition1.x, 5, spotlightPosition1.z), 0.8, spotlightColor1, 360, true);
    AddMeshToList(cerc1);
    Mesh* cerc2 = object_new::CreateCircle("cerc2", glm::vec3(spotlightPosition2.x, 5, spotlightPosition2.z), 0.8, spotlightColor2, 360, true);
    AddMeshToList(cerc2);
    Mesh* cerc3 = object_new::CreateCircle("cerc3", glm::vec3(spotlightPosition3.x, 5, spotlightPosition3.z), 0.8, spotlightColor3, 360, true);
    AddMeshToList(cerc3);

    
    GenerateDancer(cubePosition, lightColor, lightPosition, cubelightColor);
    MoveDancer(deltaTimeSeconds, direction, &cubePosition, step);

    GenerateDancer(cubePosition1, lightColor, lightPosition, cubelightColor);
    MoveDancer(deltaTimeSeconds, direction1, &cubePosition1, step1);

    GenerateDancer(cubePosition2, lightColor, lightPosition, cubelightColor);
    MoveDancer(deltaTimeSeconds, direction2, &cubePosition2, step2);

    GenerateDancer(cubePosition3, lightColor, lightPosition, cubelightColor);
    MoveDancer(deltaTimeSeconds, direction3, &cubePosition3, step3);


    
    glm::mat4 modelMatrix1;
    // Render ground
    for(Square s:squares)
    {
       
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, s.position);
        modelMatrix = glm::scale(modelMatrix, glm::vec3(0.02f));
        // TODO(student): Add or change the object colors
        floorlightColor = s.color;
        floorlightPosition = s.position;
        if (sceneType == 1) {
            RenderSimpleMesh2(meshes["plane"], shaders["Floor"], modelMatrix, s.color);
            
        }
        else if(sceneType ==2) {
       
            RenderSimpleMesh(meshes["plane"], shaders["LabShader"], modelMatrix, glm::vec3(0.25, 0.75, 0.75), lightColor, lightPosition);
        }
        
       
         
        if (s.position.x == 7) {
            modelMatrix1 = glm::mat4(1);
            modelMatrix1 = glm::translate(modelMatrix1, glm::vec3(s.position.x + 0.5, 1.75, s.position.z));
            modelMatrix1 = glm::scale(modelMatrix1, glm::vec3(0.02, 0.07, 0.02));
            modelMatrix1 = glm::rotate(modelMatrix1, RADIANS(90.0f), glm::vec3(0, 0, 1));
            if (sceneType == 1) {
                lightColor[0] = cubelightColor[7][(int)round(s.position.z)];
                lightPosition[0] = glm::vec3(7, 0, s.position.z);

            }
            else {
                lightColor[0] = glm::vec3(0, 0, 0);
                lightPosition[0] = glm::vec3(0, 0, 0);
            }
            lightColor[1] = glm::vec3(0, 0, 0);
            lightColor[2] = glm::vec3(0, 0, 0);
            lightColor[3] = glm::vec3(0, 0, 0);
            lightColor[4] = glm::vec3(0, 0, 0);
            lightColor[5] = glm::vec3(0, 0, 0);
            lightColor[6] = glm::vec3(0, 0, 0);
            lightColor[7] = glm::vec3(0, 0, 0);
            lightColor[8] = glm::vec3(0, 0, 0);

            lightPosition[1] = glm::vec3(0, 0, 0);
            lightPosition[2] = glm::vec3(0, 0, 0);
            lightPosition[3] = glm::vec3(0, 0, 0);
            lightPosition[4] = glm::vec3(0, 0, 0);
            lightPosition[5] = glm::vec3(0, 0, 0);
            lightPosition[6] = glm::vec3(0, 0, 0);
            lightPosition[7] = glm::vec3(0, 0, 0);
            lightPosition[8] = glm::vec3(0, 0, 0);
            RenderSimpleMesh(meshes["plane"], shaders["LabShader"], modelMatrix1, glm::vec3(0.25, 0.75, 0.75), lightColor, lightPosition);
        }

        if (s.position.z == 0) {
            modelMatrix1 = glm::mat4(1);
            modelMatrix1 = glm::translate(modelMatrix1, glm::vec3(s.position.x, 1.75, s.position.z - 0.5));
            modelMatrix1 = glm::scale(modelMatrix1, glm::vec3(0.02, 0.07, 0.02));
            modelMatrix1 = glm::rotate(modelMatrix1, RADIANS(90.0f), glm::vec3(1, 0, 0));

            if (sceneType == 1) {
                lightColor[0] = cubelightColor[(int)round(s.position.x)][0];

                lightPosition[0] = glm::vec3(s.position.x, 0, 0);


            }
            else {
                lightColor[0] = glm::vec3(0, 0, 0);

                lightPosition[0] = glm::vec3(0, 0, 0);
            }
            lightColor[1] = glm::vec3(0, 0, 0);
            lightColor[2] = glm::vec3(0, 0, 0);
            lightColor[3] = glm::vec3(0, 0, 0);
            lightColor[4] = glm::vec3(0, 0, 0);
            lightColor[5] = glm::vec3(0, 0, 0);
            lightColor[6] = glm::vec3(0, 0, 0);
            lightColor[7] = glm::vec3(0, 0, 0);
            lightColor[8] = glm::vec3(0, 0, 0);

            lightPosition[1] = glm::vec3(0, 0, 0);
            lightPosition[2] = glm::vec3(0, 0, 0);
            lightPosition[3] = glm::vec3(0, 0, 0);
            lightPosition[4] = glm::vec3(0, 0, 0);
            lightPosition[5] = glm::vec3(0, 0, 0);
            lightPosition[6] = glm::vec3(0, 0, 0);
            lightPosition[7] = glm::vec3(0, 0, 0);
            lightPosition[8] = glm::vec3(0, 0, 0);
            RenderSimpleMesh(meshes["plane"], shaders["LabShader"], modelMatrix1, glm::vec3(0.25, 0.75, 0.75), lightColor, lightPosition);
        }

        if (s.position.z == 7) {
            modelMatrix1 = glm::mat4(1);
            modelMatrix1 = glm::translate(modelMatrix1, glm::vec3(s.position.x, 1.75, s.position.z + 0.5));
            modelMatrix1 = glm::scale(modelMatrix1, glm::vec3(0.02, 0.07, 0.02));
            modelMatrix1 = glm::rotate(modelMatrix1, RADIANS(90.0f), glm::vec3(1, 0, 0));
            modelMatrix1 = glm::rotate(modelMatrix1, RADIANS(180.0f), glm::vec3(0, 0, 1));
            if (sceneType == 1) {
                lightColor[0] = cubelightColor[(int)round(s.position.x)][7];

                lightPosition[0] = glm::vec3(s.position.x, 0, 7);



            }
            else {
                lightColor[0] = glm::vec3(0, 0, 0);

                lightPosition[0] = glm::vec3(0, 0, 0);
            }
            lightColor[1] = glm::vec3(0, 0, 0);
            lightColor[2] = glm::vec3(0, 0, 0);
            lightColor[3] = glm::vec3(0, 0, 0);
            lightColor[4] = glm::vec3(0, 0, 0);
            lightColor[5] = glm::vec3(0, 0, 0);
            lightColor[6] = glm::vec3(0, 0, 0);
            lightColor[7] = glm::vec3(0, 0, 0);
            lightColor[8] = glm::vec3(0, 0, 0);

            lightPosition[1] = glm::vec3(0, 0, 0);
            lightPosition[2] = glm::vec3(0, 0, 0);
            lightPosition[3] = glm::vec3(0, 0, 0);
            lightPosition[4] = glm::vec3(0, 0, 0);
            lightPosition[5] = glm::vec3(0, 0, 0);
            lightPosition[6] = glm::vec3(0, 0, 0);
            lightPosition[7] = glm::vec3(0, 0, 0);
            lightPosition[8] = glm::vec3(0, 0, 0);
            RenderSimpleMesh(meshes["plane"], shaders["LabShader"], modelMatrix1, glm::vec3(0.25, 0.75, 0.75), lightColor, lightPosition);
        }
       
    } 
    if (sceneType == 2) {
        // glEnable(GL_CULL_FACE);

        glCullFace(GL_BACK); glDepthMask(GL_FALSE);

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glm::mat3 modelMatrix = glm::mat3(1);
        RenderMesh2Dd(meshes["cerc"], shaders["CircleColor"], modelMatrix, glm::vec4(spotlightColor, 1));
        RenderMesh2Dd(meshes["cerc1"], shaders["CircleColor"], modelMatrix, glm::vec4(spotlightColor1, 1));
        RenderMesh2Dd(meshes["cerc2"], shaders["CircleColor"], modelMatrix, glm::vec4(spotlightColor2, 1));
        RenderMesh2Dd(meshes["cerc3"], shaders["CircleColor"], modelMatrix, glm::vec4(spotlightColor3, 1));



        glDepthMask(GL_TRUE);
        glDisable(GL_BLEND);
        //glDisable(GL_CULL_FACE);


        if (stepSpot < 0) {
            stepSpot = 200;
            f = 2 + rand() % 7;
        }
        stepSpot--;
        //spot rosu
        float s = sin(deltaTimeSeconds * M_2_PI / 2);
        float c = cos(deltaTimeSeconds * M_2_PI / 2);

        // translate point back to origin:
        spotlightPosition.x -= 3;
        spotlightPosition.z -= 3;

        // rotate point
        float xnew = spotlightPosition.x * c - spotlightPosition.z * s;
        float ynew = spotlightPosition.x * s + spotlightPosition.z * c;

        // translate point back:
        spotlightPosition.x = xnew + 3;
        spotlightPosition.z = ynew + 3;

        //spot1

        s = sin(deltaTimeSeconds * M_2_PI / f);
        c = cos(deltaTimeSeconds * M_2_PI / f);

        // translate point back to origin:
        spotlightPosition1.x -= 2;
        spotlightPosition1.z -= 2;

        // rotate point
        xnew = spotlightPosition1.x * c - spotlightPosition1.z * s;
        ynew = spotlightPosition1.x * s + spotlightPosition1.z * c;

        // translate point back:
        spotlightPosition1.x = xnew + 2;
        spotlightPosition1.z = ynew + 2;

        //spot2

        s = sin(deltaTimeSeconds * M_2_PI / f);
        c = cos(deltaTimeSeconds * M_2_PI / f);

        // translate point back to origin:
        spotlightPosition2.x -= 3.5;
        spotlightPosition2.z -= 3.5;

        // rotate point
        xnew = spotlightPosition2.x * c - spotlightPosition2.z * s;
        ynew = spotlightPosition2.x * s + spotlightPosition2.z * c;

        // translate point back:
        spotlightPosition2.x = xnew + 3.5;
        spotlightPosition2.z = ynew + 3.5;


        //spot3
        s = sin(deltaTimeSeconds * M_2_PI / f);
        c = cos(deltaTimeSeconds * M_2_PI / f);

        // translate point back to origin:
        spotlightPosition3.x -= 4.5;
        spotlightPosition3.z -= 4.5;

        // rotate point
        xnew = spotlightPosition3.x * c - spotlightPosition3.z * s;
        ynew = spotlightPosition3.x * s + spotlightPosition3.z * c;

        // translate point back:
        spotlightPosition3.x = xnew + 4.5;
        spotlightPosition3.z = ynew + 4.5;
    }

    if (sceneType == 3) {
        modelMatrix1 = glm::mat4(1);
        modelMatrix1 = glm::translate(modelMatrix1, glm::vec3(3.5, 3.5, 3.5));
        modelMatrix1 = glm::scale(modelMatrix1, glm::vec3(0.16));
        modelMatrix1 = glm::rotate(modelMatrix1, RADIANS(180.0f), glm::vec3(0, 0, 1));
        lightColor[0] = glm::vec3(1, 1, 1);
        lightColor[1] = glm::vec3(0, 0, 0);
        lightColor[2] = glm::vec3(0, 0, 0);
        lightColor[3] = glm::vec3(0, 0, 0);
        lightColor[4] = glm::vec3(0, 0, 0);
        lightColor[5] = glm::vec3(0, 0, 0);
        lightColor[6] = glm::vec3(0, 0, 0);
        lightColor[7] = glm::vec3(0, 0, 0);
        lightColor[8] = glm::vec3(0, 0, 0);

        lightPosition[0] = glm::vec3(4, 3.5, 4);
        lightPosition[1] = glm::vec3(0, 0, 0);
        lightPosition[2] = glm::vec3(0, 0, 0);
        lightPosition[3] = glm::vec3(0, 0, 0);
        lightPosition[4] = glm::vec3(0, 0, 0);
        lightPosition[5] = glm::vec3(0, 0, 0);
        lightPosition[6] = glm::vec3(0, 0, 0);
        lightPosition[7] = glm::vec3(0, 0, 0);
        lightPosition[8] = glm::vec3(0, 0, 0);
        RenderSimpleMesh(meshes["plane"], shaders["LabShader"], modelMatrix1, glm::vec3(0.25, 0.75, 0.75), lightColor, lightPosition, mapTextures["random"]);

        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(3.5, 0, 3.5));
        modelMatrix = glm::scale(modelMatrix, glm::vec3(0.16));
        
        RenderSimpleMesh(meshes["plane"], shaders["LabShader"], modelMatrix, glm::vec3(0.25, 0.75, 0.75), lightColor, lightPosition);
        modelMatrix1 = glm::mat4(1);
        modelMatrix1 = glm::translate(modelMatrix1, glm::vec3(4, 2.7, 4));
        modelMatrix1 = glm::scale(modelMatrix1, glm::vec3(1.5));
        RenderSimpleMeshT(meshes["sphere"], shaders["SphereShader"], modelMatrix1, mapTextures["random"]);

    }



}


void Tema3::FrameEnd()
{
   // DrawCoordinateSystem();
}

void Tema3::RenderSimpleMeshT(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix, Texture2D* texture1, Texture2D* texture2)
{
    if (!mesh || !shader || !shader->GetProgramID())
        return;

    // Render an object using the specified shader and the specified position
    glUseProgram(shader->program);

    int light_direction = glGetUniformLocation(shader->program, "light_dir");
    glUniform3f(light_direction, lightDirection.x, lightDirection.y, lightDirection.z);

    int time1 = glGetUniformLocation(shader->program, "time");
    glUniform1f(time1, time);

    int light_position = glGetUniformLocation(shader->program, "disco_ball_position");
    glUniform3f(light_position, 4, 2.7,4);

    // Bind model matrix
    GLint loc_model_matrix = glGetUniformLocation(shader->program, "Model");
    glUniformMatrix4fv(loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));

    // Bind view matrix
    glm::mat4 viewMatrix = GetSceneCamera()->GetViewMatrix();
    int loc_view_matrix = glGetUniformLocation(shader->program, "View");
    glUniformMatrix4fv(loc_view_matrix, 1, GL_FALSE, glm::value_ptr(viewMatrix));

    // Bind projection matrix
    glm::mat4 projectionMatrix = GetSceneCamera()->GetProjectionMatrix();
    int loc_projection_matrix = glGetUniformLocation(shader->program, "Projection");
    glUniformMatrix4fv(loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

    // TODO(student): Set any other shader uniforms that you need
    glUniform1i(glGetUniformLocation(shader->program, "mix_textures"), 0);
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
        // TODO(student): Do these:
        // - activate texture location 1
        // - bind the texture2 ID
        // - send the uniform value

        glActiveTexture(GL_TEXTURE1);

        glBindTexture(GL_TEXTURE_2D, texture2->GetTextureID());

        glUniform1i(glGetUniformLocation(shader->program, "texture_2"), 1);
    }

    // Draw the object
    glBindVertexArray(mesh->GetBuffers()->m_VAO);
    glDrawElements(mesh->GetDrawMode(), static_cast<int>(mesh->indices.size()), GL_UNSIGNED_INT, 0);
}


Texture2D* Tema3::CreateRandomTexture(unsigned int width, unsigned int height)
{
    GLuint textureID = 0;
    unsigned int channels = 3;
    unsigned int size = width * height * channels;
    unsigned char* data = new unsigned char[size];

    // TODO(student): Generate random texture data
    for (size_t i = 0; i < size; ++i)
    {
        data[i] = rand() % (UINT8_MAX + 1);
    }

    // TODO(student): Generate and bind the new texture ID
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    if (GLEW_EXT_texture_filter_anisotropic) {
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, 4);
    }
    // TODO(student): Set the texture parameters (MIN_FILTER, MAG_FILTER and WRAPPING MODE) using glTexParameteri
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glPixelStorei(GL_PACK_ALIGNMENT, 1);
    CheckOpenGLError();

    // Use glTexImage2D to set the texture data
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

    // TODO(student): Generate texture mip-maps
    glGenerateMipmap(GL_TEXTURE_2D);

    CheckOpenGLError();

    // Save the texture into a wrapper Texture2D class for using easier later during rendering phase
    Texture2D* texture = new Texture2D();
    texture->Init(textureID, width, height, channels);

    SAFE_FREE_ARRAY(data);
    return texture;
}



void Tema3::RenderMesh2Dd(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix, const glm::vec4& color)
{
    if (!mesh || !shader || !shader->program)
        return;

    glUseProgram(shader->program);

    int location = glGetUniformLocation(shader->GetProgramID(), "Model");

    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(modelMatrix));

    int location2 = glGetUniformLocation(shader->GetProgramID(), "View");
    glm::mat4 viewMatrix = GetSceneCamera()->GetViewMatrix();
    glUniformMatrix4fv(location2, 1, GL_FALSE, glm::value_ptr(viewMatrix));

    int location3 = glGetUniformLocation(shader->GetProgramID(), "Projection");
    glm::mat4 projectionMatrix = GetSceneCamera()->GetProjectionMatrix();
    glUniformMatrix4fv(location3, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

    int col = glGetUniformLocation(shader->GetProgramID(), "Color");
    glUniform4fv(col, 1, glm::value_ptr(color));

    int type = glGetUniformLocation(shader->program, "type_of_light");
    glUniform1i(type, typeOfLight);

    glBindVertexArray(mesh->GetBuffers()->m_VAO);
    glDrawElements(mesh->GetDrawMode(), static_cast<int>(mesh->indices.size()), GL_UNSIGNED_INT, 0);


}



void Tema3::RenderSimpleMesh2(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix, const glm::vec3& color)
{
    if (!mesh || !shader || !shader->GetProgramID())
        return;

    // Render an object using the specified shader and the specified position
    glUseProgram(shader->program);


    int object_color = glGetUniformLocation(shader->program, "object_color");
    glUniform3f(object_color, color.r, color.g, color.b);

    int light_position = glGetUniformLocation(shader->program, "light_position");
    glUniform3f(light_position, floorlightPosition.x, floorlightPosition.y, floorlightPosition.z);

    int light_direction = glGetUniformLocation(shader->program, "light_direction");
    glUniform3f(light_direction, lightDirection.x, lightDirection.y, lightDirection.z);


    int spotlightC = glGetUniformLocation(shader->program, "spotlightColor");
    glUniform3f(spotlightC, spotlightColor.r, spotlightColor.g, spotlightColor.b);

    int spotlightpos = glGetUniformLocation(shader->program, "spotlightPosition");
    glUniform3f(spotlightpos, spotlightPosition.x, spotlightPosition.y, spotlightPosition.z);

    int spotlightDir = glGetUniformLocation(shader->program, "spotlightDirection");

    glm::vec3 eyePosition = GetSceneCamera()->m_transform->GetWorldPosition();
    int eye_position = glGetUniformLocation(shader->program, "eye_position");
    glUniform3f(eye_position, eyePosition.x, eyePosition.y, eyePosition.z);

    // Set material property uniforms (shininess, kd, ks, object color) 
    int material_shininess = glGetUniformLocation(shader->program, "material_shininess");
    glUniform1i(material_shininess, materialShininess);

    int material_kd = glGetUniformLocation(shader->program, "material_kd");
    glUniform1f(material_kd, materialKd);

    int material_ks = glGetUniformLocation(shader->program, "material_ks");
    glUniform1f(material_ks, materialKs);

    int type_of_light = glGetUniformLocation(shader->program, "type_of_light");
    glUniform1i(type_of_light, typeOfLight);

    int scene = glGetUniformLocation(shader->program, "scene_type");
    glUniform1i(scene, sceneType);


    // TODO(student): Get shader location for uniform mat4 "Model"
    int location = glGetUniformLocation(shader->GetProgramID(), "Model");

    // TODO(student): Set shader uniform "Model" to modelMatrix
    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(modelMatrix));
    // TODO(student): Get shader location for uniform mat4 "View"
    int location_view = glGetUniformLocation(shader->GetProgramID(), "View");
    // TODO(student): Set shader uniform "View" to viewMatrix
    glm::mat4 viewMatrix = GetSceneCamera()->GetViewMatrix();
    glUniformMatrix4fv(location_view, 1, GL_FALSE, glm::value_ptr(viewMatrix));
    // TODO(student): Get shader location for uniform mat4 "Projection"
    int location_projection = glGetUniformLocation(shader->GetProgramID(), "Projection");
    // TODO(student): Set shader uniform "Projection" to projectionMatrix
    glm::mat4 projectionMatrix = GetSceneCamera()->GetProjectionMatrix();
    glUniformMatrix4fv(location_projection, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

    // Draw the object
    glBindVertexArray(mesh->GetBuffers()->m_VAO);
    glDrawElements(mesh->GetDrawMode(), static_cast<int>(mesh->indices.size()), GL_UNSIGNED_INT, 0);
}



void Tema3::RenderSimpleMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix, const glm::vec3& color,const glm::vec3 lightColor[9], const glm::vec3 lightPosition[9], Texture2D* texture1)
{
    if (!mesh || !shader || !shader->GetProgramID())
        return;

    // Render an object using the specified shader and the specified position
    glUseProgram(shader->program);

    int time1 = glGetUniformLocation(shader->program, "time");
    glUniform1f(time1, time);

    int spotlightC = glGetUniformLocation(shader->program, "spotlightColor");
    glUniform3f(spotlightC, spotlightColor.r, spotlightColor.g, spotlightColor.b);

    int spotlightpos = glGetUniformLocation(shader->program, "spotlightPosition");
    glUniform3f(spotlightpos, spotlightPosition.x, spotlightPosition.y, spotlightPosition.z);

    int spotlightC1 = glGetUniformLocation(shader->program, "spotlightColor1");
    glUniform3f(spotlightC1, spotlightColor1.r, spotlightColor1.g, spotlightColor1.b);

    int spotlightpos1 = glGetUniformLocation(shader->program, "spotlightPosition1");
    glUniform3f(spotlightpos1, spotlightPosition1.x, spotlightPosition1.y, spotlightPosition1.z);

    int spotlightC2 = glGetUniformLocation(shader->program, "spotlightColor2");
    glUniform3f(spotlightC2, spotlightColor2.r, spotlightColor2.g, spotlightColor2.b);

    int spotlightpos2 = glGetUniformLocation(shader->program, "spotlightPosition2");
    glUniform3f(spotlightpos2, spotlightPosition2.x, spotlightPosition2.y, spotlightPosition2.z);

    int spotlightC3 = glGetUniformLocation(shader->program, "spotlightColor3");
    glUniform3f(spotlightC3, spotlightColor3.r, spotlightColor3.g, spotlightColor3.b);

    int spotlightpos3 = glGetUniformLocation(shader->program, "spotlightPosition3");
    glUniform3f(spotlightpos3, spotlightPosition3.x, spotlightPosition3.y, spotlightPosition3.z);

    int spotlightDir = glGetUniformLocation(shader->program, "spotlightDirection");
    glUniform3f(spotlightDir, spotlightDirection.x, spotlightDirection.y, spotlightDirection.z);

    // Set shader uniforms for light properties
    int light_position = glGetUniformLocation(shader->program, "light_position0");
   glUniform3f(light_position, lightPosition[0].x, lightPosition[0].y, lightPosition[0].z);

    light_position = glGetUniformLocation(shader->program, "light_position1");
   glUniform3f(light_position, lightPosition[1].x, lightPosition[1].y, lightPosition[1].z);

    light_position = glGetUniformLocation(shader->program, "light_position2");
   glUniform3f(light_position, lightPosition[2].x, lightPosition[2].y, lightPosition[2].z);

    light_position = glGetUniformLocation(shader->program, "light_position3");
   glUniform3f(light_position, lightPosition[3].x, lightPosition[3].y, lightPosition[3].z);

    light_position = glGetUniformLocation(shader->program, "light_position4");
   glUniform3f(light_position, lightPosition[4].x, lightPosition[4].y, lightPosition[4].z);

    light_position = glGetUniformLocation(shader->program, "light_position5");
   glUniform3f(light_position, lightPosition[5].x, lightPosition[5].y, lightPosition[5].z);

    light_position = glGetUniformLocation(shader->program, "light_position6");
   glUniform3f(light_position, lightPosition[6].x, lightPosition[6].y, lightPosition[6].z);

    light_position = glGetUniformLocation(shader->program, "light_position7");
   glUniform3f(light_position, lightPosition[7].x, lightPosition[7].y, lightPosition[7].z);

    light_position = glGetUniformLocation(shader->program, "light_position8");
   glUniform3f(light_position, lightPosition[8].x, lightPosition[8].y, lightPosition[8].z);
    //glUniform3fv(light_position,9, glm::value_ptr( lightPosition[0]));

    int light_color = glGetUniformLocation(shader->program, "light_color");
    glUniform3f(light_color, lightColor[0].x, lightColor[0].y, lightColor[0].z);
   // glUniform3fv(light_position, 9, glm::value_ptr(lightColor[0]));

   
     light_color = glGetUniformLocation(shader->program, "light_color1");
    glUniform3f(light_color, lightColor[1].x, lightColor[1].y, lightColor[1].z);

     light_color = glGetUniformLocation(shader->program, "light_color2");
    glUniform3f(light_color, lightColor[2].x, lightColor[2].y, lightColor[2].z);

     light_color = glGetUniformLocation(shader->program, "light_color3");
    glUniform3f(light_color, lightColor[3].x, lightColor[3].y, lightColor[3].z);

     light_color = glGetUniformLocation(shader->program, "light_color4");
    glUniform3f(light_color, lightColor[4].x, lightColor[4].y, lightColor[4].z);

     light_color = glGetUniformLocation(shader->program, "light_color5");
    glUniform3f(light_color, lightColor[5].x, lightColor[5].y, lightColor[5].z);

     light_color = glGetUniformLocation(shader->program, "light_color6");
    glUniform3f(light_color, lightColor[6].x, lightColor[6].y, lightColor[6].z);

     light_color = glGetUniformLocation(shader->program, "light_color7");
    glUniform3f(light_color, lightColor[7].x, lightColor[7].y, lightColor[7].z);

    light_color = glGetUniformLocation(shader->program, "light_color8");
    glUniform3f(light_color, lightColor[8].x, lightColor[8].y, lightColor[8].z);
    
    int light_direction = glGetUniformLocation(shader->program, "light_direction");
    glUniform3f(light_direction, lightDirection.x, lightDirection.y, lightDirection.z);

    // Set eye position (camera position) uniform
    glm::vec3 eyePosition = GetSceneCamera()->m_transform->GetWorldPosition();
    int eye_position = glGetUniformLocation(shader->program, "eye_position");
    glUniform3f(eye_position, eyePosition.x, eyePosition.y, eyePosition.z);

    // Set material property uniforms (shininess, kd, ks, object color) 
    int material_shininess = glGetUniformLocation(shader->program, "material_shininess");
    glUniform1i(material_shininess, materialShininess);

    int material_kd = glGetUniformLocation(shader->program, "material_kd");
    glUniform1f(material_kd, materialKd);

    int material_ks = glGetUniformLocation(shader->program, "material_ks");
    glUniform1f(material_ks, materialKs);

    int scene = glGetUniformLocation(shader->program, "scene_type");
    glUniform1i(scene, sceneType);

    // TODO(student): Set any other shader uniforms that you need
    int type_of_light = glGetUniformLocation(shader->program, "type_of_light");
    glUniform1i(type_of_light, typeOfLight);

    // Bind model matrix
    GLint loc_model_matrix = glGetUniformLocation(shader->program, "Model");
    glUniformMatrix4fv(loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));

    // Bind view matrix
    glm::mat4 viewMatrix = GetSceneCamera()->GetViewMatrix();
    int loc_view_matrix = glGetUniformLocation(shader->program, "View");
    glUniformMatrix4fv(loc_view_matrix, 1, GL_FALSE, glm::value_ptr(viewMatrix));

    // Bind projection matrix
    glm::mat4 projectionMatrix = GetSceneCamera()->GetProjectionMatrix();
    int loc_projection_matrix = glGetUniformLocation(shader->program, "Projection");
    glUniformMatrix4fv(loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

    // Draw the object
    glBindVertexArray(mesh->GetBuffers()->m_VAO);
    glDrawElements(mesh->GetDrawMode(), static_cast<int>(mesh->indices.size()), GL_UNSIGNED_INT, 0);
}



/*
 *  These are callback functions. To find more about callbacks and
 *  how they behave, see `input_controller.h`.
 */


void Tema3::OnInputUpdate(float deltaTime, int mods)
{
    
}

void Tema3::MoveDancer(float deltaTime, int &direction, glm::vec3 *cubePosition, int &step) {
    float speed = 0.5;
   
    if (direction == 1) {
        if (cubePosition->x - deltaTime*speed > 0 && step >0) {
            cubePosition->x -= deltaTime * speed;
            step-= deltaTime;
        }
        else {
            step = (rand() % 100) + 10;
            direction = (rand() % 4) + 1;
        }
    }else
    if (direction == 2) {

        if (cubePosition->x + deltaTime * speed < 7  && step >0) {
            cubePosition->x += deltaTime * speed;
            step-= deltaTime;

        }
        else {
            direction = (rand() % 4) + 1;
            step = (rand() % 100) + 10;
        }
    }else
    if (direction == 3) {

        if (cubePosition->z - deltaTime * speed > 0 && step > 0) {
            cubePosition->z -= deltaTime * speed;
            step-= deltaTime;

        } else{
            direction = (rand() % 4) + 1;
            step = (rand() % 100) + 10;

        }
    }else
    if (direction == 4) {

        if (cubePosition->z + deltaTime * speed < 7 && step >0) {
            cubePosition->z += deltaTime * speed;
            step-= deltaTime;

        }
        else {
            direction = (rand() % 4) + 1;
            step = (rand() % 100) + 10;
        }
    }



}



void Tema3::OnKeyPress(int key, int mods)
{
    // Add key press event

    // TODO(student): Set keys that you might need
    if (key == GLFW_KEY_F)
    {
        typeOfLight = ~typeOfLight;
    }

    if( key ==GLFW_KEY_1) {
        if (sceneType == 1 || sceneType == 2) {
            sceneType++;
        }
        else {
            sceneType = 1;
        }
    }

}


void Tema3::OnKeyRelease(int key, int mods)
{
    // Add key release event
}


void Tema3::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
    // Add mouse move event
}


void Tema3::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button press event
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
