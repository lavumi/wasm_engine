//
// Created by Lavumi on 2023/03/28.
//

#ifndef WASM_SPOTLIGHT_H
#define WASM_SPOTLIGHT_H

namespace VumiEngine{
    class SpotLight : public VumiEngine::Node{

        glm::mat4 worldMatrix{};
        glm::mat4 modelMatrix{};



        Shader* shader{};
        GLuint shaderProgram{};


        GLuint _vao{};
        GLuint vertexBuffer{};


        glm::vec4 lightColor;
        GLfloat bright = 1.0f;
        GLfloat direction = 0;
    public:


        SpotLight();
        ~SpotLight();

        void Update(float deltaTime);
        void setBuffer();
        void Render();

        void SetPosition(glm::vec3 position);
        void SetAngle(GLfloat angle);
        GLfloat GetAngle();

        void SetColor(glm::vec4 color);
        glm::vec4 GetColor();

        void SetBright(GLfloat bright);
        GLfloat GetBright();
    };
}



#endif //WASM_SPOTLIGHT_H
