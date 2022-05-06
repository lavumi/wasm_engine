#pragma once

class Shader;
class Texture;
class ThreeCube : public Node
{
private:
    /* data */

    glm::mat4 worldMatrix;

    GLuint shader;
    GLuint _vao;
        GLuint vertexBuffer;
    GLuint colorBuffer;

    GLuint texCoordBuffer;

    Texture* texture;

public:
    ThreeCube(/* args */);
    ~ThreeCube();


    void Init();
        void Update(float deltaTime);



    void setBuffer(GLuint shaderProgram);
    void makeBuffer();

    void Render();
};
 