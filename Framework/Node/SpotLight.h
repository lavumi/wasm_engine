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
//        GLuint texCoordBuffer{};
//        VumiEngine::Texture *texture{};


        glm::vec4 lightColor;
        float swingAngle = PI  * 0.2;
        float swingDelta = 0.0f;
        float swingSpeed = 0.3f;
    public:


        SpotLight(GLfloat startAngle = 0 , bool direction = true);
        ~SpotLight();

        void Update(float deltaTime);
        void setBuffer();
        void Render();

        void SetPosition(glm::vec3 position);
        void SetColor(glm::vec4 color);
    };
}



#endif //WASM_SPOTLIGHT_H
