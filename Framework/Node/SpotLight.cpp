//
// Created by Lavumi on 2023/03/28.
//
#include "../precompiled.h"
#include "SpotLight.h"

using namespace VumiEngine;

static glm::vec3 point[] = {
       glm::vec3(-3,-8,0),
       glm::vec3(3,-8,0),
       glm::vec3(0.2,8,0),
       glm::vec3(-0.2,8,0)
};

static const GLfloat g_vertex_buffer_data[] = {
        point[2].x,point[2].y, point[2].z,
        point[0].x,point[0].y, point[0].z,
        point[3].x,point[3].y, point[3].z,
        point[2].x,point[2].y, point[2].z,
        point[1].x,point[1].y, point[1].z,
        point[0].x,point[0].y, point[0].z,
};

static const GLfloat g_texCoord_buffer_data[] = {
        0.0f, 0.0f, //좌상
        1.0f, 1.0f, //우하
        1.0f, 0.0f, //우상
        0.0f, 0.0f, //좌상
        0.0f, 1.0f, //좌하
        1.0f, 1.0f, //우하
};


SpotLight::SpotLight() {
    worldMatrix = glm::translate( glm::mat4(1.0f) , glm::vec3(0,8,0));
    modelMatrix = glm::translate( glm::mat4(1.0f) , glm::vec3(0,-8,0));//glm::mat4(1.0f);

    setBuffer();
    lightColor = glm::vec4(0.1,0.3,1,0.3);

}

SpotLight::~SpotLight() {
    glDeleteBuffers(sizeof(g_vertex_buffer_data), &vertexBuffer);
//    glDeleteBuffers(sizeof(g_texCoord_buffer_data), &texCoordBuffer);
    delete shader;
}



void SpotLight::Update(float deltaTime) {

//    swingDelta += deltaTime * swingSpeed;
//    if (abs(swingDelta) > swingAngle ){
//        swingSpeed *= -1;
//        swingDelta = 0;
//    }
//
//    glm::vec3 axis = glm::vec3(0,0,1);
//    glm::mat4 rotMatrix = glm::rotate(glm::mat4(1.0f), swingSpeed * deltaTime, axis);
//    modelMatrix = rotMatrix * modelMatrix;
}

void SpotLight::setBuffer() {

    shader = new Shader();
    shader->MakeShader("spotlight");
    shaderProgram = shader->shader_program;


    glGenVertexArrays(1, &_vao);
    glBindVertexArray(_vao);

    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);


//    glGenBuffers(1, &texCoordBuffer);
//    glBindBuffer(GL_ARRAY_BUFFER, texCoordBuffer);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(g_texCoord_buffer_data), g_texCoord_buffer_data, GL_STATIC_DRAW);

    GLuint vertexPosition = glGetAttribLocation(shaderProgram, "vertexPosition");
//    GLuint texCoord = glGetAttribLocation(shaderProgram, "aTexCoord");


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

//    glBindBuffer(GL_ARRAY_BUFFER, texCoordBuffer);
//    glVertexAttribPointer(
//            texCoord,
//            2,
//            GL_FLOAT,
//            GL_FALSE,
//            0,
//            (void *) nullptr);
//    glEnableVertexAttribArray(texCoord);

    glBindVertexArray(0);
}





void SpotLight::Render() {
    Node::Render();

//    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//    glBlendFuncSeparate(GL_ONE, GL_ONE,GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glBlendFunc(GL_ONE, GL_ONE);
//    glBlendFuncSeparate(GL_ONE, GL_,GL_ONE, GL_ZERO);
//    glBlendEquation(GL_FUNC_ADD);



    glUseProgram(shaderProgram);
    glBindVertexArray(_vao);

    GLint modelID = glGetUniformLocation(shaderProgram, "Model");
    glm::mat4 finalMat = worldMatrix *  modelMatrix;
    glUniformMatrix4fv(modelID, 1, GL_FALSE, (GLfloat *) &finalMat);


    glm::mat4 VP = Director::GetDirector().GetCameraVP();
    GLint VPID = glGetUniformLocation(shaderProgram, "VP");
    glUniformMatrix4fv(VPID, 1, GL_FALSE, (GLfloat *) &VP);

    GLint ColorId = glGetUniformLocation(shaderProgram, "LightColor");
    glUniform4fv(ColorId, 1, (GLfloat *) &lightColor);


    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);

//    std::cout << "Spotlight Render" << std::endl;
}

void SpotLight::SetColor(glm::vec4 color) {
    lightColor = color;
}

glm::vec4 SpotLight::GetColor() {
    return lightColor;
}

void SpotLight::SetPosition( glm::vec3 position ){
    worldMatrix = glm::translate( glm::mat4(1.0f) , position);
}

void SpotLight::SetAngle(GLfloat angle) {
    glm::mat4 rotMatrix = glm::rotate(glm::mat4(1.0f), angle , glm::vec3(0,0,1));
    modelMatrix = rotMatrix * glm::translate( glm::mat4(1.0f) , glm::vec3(0,-8,0));
    direction = angle;
}


GLfloat SpotLight::GetAngle() {
    return direction;
}