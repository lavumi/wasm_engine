//
// Created by Lavumi on 2023/03/28.
//
#include "../precompiled.h"
#include "SpriteAnimation.h"
#include <cstdlib>


using namespace VumiEngine;

static const GLfloat g_vertex_buffer_data[] = {
        1.0f, 1.0f, 0.0f, // triangle 2 : begin
        -1.0f, -1.0f, 0.0f,
        -1.0f, 1.0f, 0.0f,  // triangle 2 : end

        1.0f, 1.0f, 0.0f,
        1.0f, -1.0f, 0.0f,
        -1.0f, -1.0f, 0.0f,
};
//
//static const GLfloat g_texCoord_buffer_data_temp[] = {
//        0.0f, 0.0f, //좌상
//        1.0f, 1.0f, //우하
//        1.0f, 0.0f, //우상
//        0.0f, 0.0f, //좌상
//        0.0f, 1.0f, //좌하
//        1.0f, 1.0f, //우하
//};

namespace VumiEngine {
    SpriteAnimation::SpriteAnimation(const std::string& imgPath,int pMaxFrameIndex, float pInterval) {
        worldMatrix = glm::mat4(1.0f);
        modelMatrix = glm::mat4(1.0f);



        GLfloat coordLB = 0.0f;
        GLfloat coordRB = 0.083333333f;
        GLfloat coordLT = 0.0f;
        GLfloat coordRT = 0.1111111111f;

        g_texCoord_buffer_data[0] = coordLB;
        g_texCoord_buffer_data[1] = coordLT;

        g_texCoord_buffer_data[2] = coordRB;
        g_texCoord_buffer_data[3] = coordRT;

        g_texCoord_buffer_data[4] = coordRB;
        g_texCoord_buffer_data[5] =coordLT;

        g_texCoord_buffer_data[6] = coordLB;
        g_texCoord_buffer_data[7] = coordLT;

        g_texCoord_buffer_data[8] = coordLB;
        g_texCoord_buffer_data[9] = coordRT;

        g_texCoord_buffer_data[10] = coordRB;
        g_texCoord_buffer_data[11] = coordRT;

        setBuffer();

        texture = new Texture();
        texture->LoadTexture(imgPath);

        maxFrameIndex = pMaxFrameIndex;
        interval = pInterval;
    }

    SpriteAnimation::~SpriteAnimation() {
        glDeleteBuffers(sizeof(g_vertex_buffer_data), &vertexBuffer);
        glDeleteBuffers(sizeof(g_texCoord_buffer_data), &texCoordBuffer);
    }

    void SpriteAnimation::Update(float deltaTime) {

        timeStamp += deltaTime;
        if ( timeStamp > interval ){
            timeStamp = 0;
            animationStep++;
            if ( animationStep >= maxFrameIndex ){
                animationStep = 0;
                if ( rand()%5 == 0){
                    characterType = rand() % 9;
                }
            }
        }

    }

    void SpriteAnimation::setBuffer() {
        animationShader = new AnimationShader();
        animationShader->MakeShader();

        shaderProgram = animationShader->shader_program;

        glGenVertexArrays(1, &_vao);
        glBindVertexArray(_vao);

        glGenBuffers(1, &vertexBuffer);
        glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
        glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

        glGenBuffers(1, &texCoordBuffer);
        glBindBuffer(GL_ARRAY_BUFFER, texCoordBuffer);
        glBufferData(GL_ARRAY_BUFFER, sizeof(g_texCoord_buffer_data), g_texCoord_buffer_data, GL_STATIC_DRAW);


        GLuint vertexPosition = glGetAttribLocation(shaderProgram, "vertexPosition");
        GLuint texCoord = glGetAttribLocation(shaderProgram, "aTexCoord");


        glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer); //버퍼를 GL_ARRAY_BUFFER 에 바인드
        glVertexAttribPointer(
                vertexPosition, // attribute. Vertex 속성의 위치
                3,                           // 크기
                GL_FLOAT,                   // 데이터 타입
                GL_FALSE,                   // 정규화
                0,                           // stride 속성 세트 사이의 공백
                (void *) nullptr                   // 시작 위치
        );
        glEnableVertexAttribArray(vertexPosition); //버텍스 버퍼를 활성화
        // 2nd attribute buffer : colors

        glBindBuffer(GL_ARRAY_BUFFER, texCoordBuffer);
        glVertexAttribPointer(
                texCoord,
                2,
                GL_FLOAT,
                GL_FALSE,
                0,
                (void *) nullptr);
        glEnableVertexAttribArray(texCoord);

        glBindVertexArray(0);
    }

    void SpriteAnimation::Render() {
        Node::Render();

        if ( texture == nullptr ) return;
        texture->BindTexture();


        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


        glUseProgram(shaderProgram);
        glBindVertexArray(_vao);


        GLint modelID = glGetUniformLocation(shaderProgram, "Model");
        glm::mat4 finalMat = worldMatrix *  modelMatrix;
        glUniformMatrix4fv(modelID, 1, GL_FALSE, (GLfloat *) &finalMat);

        glm::mat4 VP = Director::GetDirector().GetCameraVP();
        GLint VPID = glGetUniformLocation(shaderProgram, "VP");
        glUniformMatrix4fv(VPID, 1, GL_FALSE, (GLfloat *) &VP);

        GLint uvTargetID = glGetUniformLocation(shaderProgram, "uvTarget");
        glm::vec2 uvTarget = glm::vec2(0.083333333f * (float)animationStep , 0.11111111f * (float)characterType);
        glUniform2fv(uvTargetID, 1, (GLfloat *) &uvTarget);

        glDrawArrays(GL_TRIANGLES, 0, 6);
//
        glBindVertexArray(0);
    }
} // VumiEngine