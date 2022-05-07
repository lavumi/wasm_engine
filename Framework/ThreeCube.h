#pragma once

class Shader;
class Texture;
class ThreeCube : public Node
{
private:
    /* data */

    glm::mat4 worldMatrix[27];

    GLuint shader;
    GLuint _vao;
    GLuint vertexBuffer;
    GLuint colorBuffer;

    GLuint texCoordBuffer;

    Texture* texture;


    bool canRotate = false;
public:
    ThreeCube(/* args */);
    ~ThreeCube();


    void Init();
    void Update(float deltaTime);



    void setBuffer(GLuint shaderProgram);
    void makeBuffer();


    void ToggleRotate( bool isRotate);
    void SetRotate(float amount, glm::vec3 axis);
    void Render();
};
 