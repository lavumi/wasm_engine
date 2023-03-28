//
// Created by Lavumi on 2023/03/26.
//
#include "../precompiled.h"
#include "Sprite.h"
using namespace VumiEngine;
static const GLfloat g_vertex_buffer_data[] = {
        1.0f, 1.0f, 0.0f, // triangle 2 : begin
        -1.0f, -1.0f, 0.0f,
        -1.0f, 1.0f, 0.0f,  // triangle 2 : end

        1.0f, 1.0f, 0.0f,
        1.0f, -1.0f, 0.0f,
        -1.0f, -1.0f, 0.0f,
};

static const GLfloat g_texCoord_buffer_data[] = {
        0.0f, 0.0f, //좌상
        1.0f, 1.0f, //우하
        1.0f, 0.0f, //우상
        0.0f, 0.0f, //좌상
        0.0f, 1.0f, //좌하
        1.0f, 1.0f, //우하
};

Sprite::Sprite(std::string imgPath) {
    worldMatrix = glm::mat4(1.0f);
    modelMatrix = glm::mat4(1.0f);


    setBuffer(Director::GetDirector().GetShaderProgram());
    texture = new Texture();
    texture->LoadTexture(imgPath);
    texture->BindTexture();
}

Sprite::~Sprite() {
    glDeleteBuffers(sizeof(g_vertex_buffer_data), &vertexBuffer);
    glDeleteBuffers(sizeof(g_texCoord_buffer_data), &texCoordBuffer);
}

void Sprite::Update(float deltaTime) {

}

void Sprite::setBuffer(GLuint shaderProgram) {

    shader = shaderProgram;

    GLuint vertexPosition = glGetAttribLocation(shader, "vertexPosition");
    GLuint texCoord = glGetAttribLocation(shader, "aTexCoord");


    glGenVertexArrays(1, &_vao);
    glBindVertexArray(_vao);

    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);


    glGenBuffers(1, &texCoordBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, texCoordBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_texCoord_buffer_data), g_texCoord_buffer_data, GL_STATIC_DRAW);


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

    glBindBuffer(GL_ARRAY_BUFFER, texCoordBuffer);
    glVertexAttribPointer(
            texCoord,
            2,
            GL_FLOAT,
            GL_FALSE,
            0,
            (void *) nullptr);
    glEnableVertexAttribArray(texCoord);



    // glActiveTexture(GL_TEXTURE0); // activate the texture unit first before binding texture
    // glBindTexture(GL_TEXTURE_2D, *texture);
    glBindVertexArray(0);
}

void Sprite::Render() {
    Node::Render();

    glUseProgram(shader);
    glBindVertexArray(_vao);
    GLint modelID = glGetUniformLocation(shader, "Model");

    glm::mat4 finalMat = worldMatrix *  modelMatrix;
    glUniformMatrix4fv(modelID, 1, GL_FALSE, (GLfloat *) &finalMat);
    glDrawArrays(GL_TRIANGLES, 0, 12 * 3);


    glBindVertexArray(0);
}
