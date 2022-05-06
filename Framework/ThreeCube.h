#pragma once

class Shader;
class Texture;
class TestCube : public Node
{
private:
    /* data */

    glm::mat4 worldMatrix;

    GLuint shader;
    GLuint _vao;
        GLuint vertexbuffer;
    GLuint colorbuffer;
    GLuint texcoordbuffer;

    Texture* texture;

public:
    TestCube(/* args */);
    ~TestCube();


    void Init();
        void Update(float deltaTime);



    void setBuffer(GLuint shaderProgram);
    void makeBuffer();

    void Render();
};
 