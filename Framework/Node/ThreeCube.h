#pragma once

class ThreeCube : public VumiEngine::Node {
private:
    /* data */


    glm::mat4 rpyMatrix[27]{};
    glm::mat4 worldMatrix{};
    glm::mat4 modelMatrix[27]{};

    GLuint shader{};
    GLuint _vao{};
    GLuint vertexBuffer{};
//    GLuint colorBuffer{};

    GLuint texCoordBuffer{};

    VumiEngine::Texture *texture;

    float timeSpend = 0.0f;
    int rpyRnd = -1;
    bool canRotate = false;

    void _finishRpy(int rpyIndex);

public:
    ThreeCube(/* args */);

    ~ThreeCube();

    void Update(float deltaTime);

    void RunCube(int index, float angle);

    void setBuffer(GLuint shaderProgram);

    void ToggleRotate(bool isRotate);

    void SetRotate(float amount, glm::vec3 axis);

    void Render();
};
 