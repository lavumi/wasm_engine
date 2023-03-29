//
// Created by Lavumi on 2023/03/28.
//

#ifndef WASM_SPOTLIGHT_H
#define WASM_SPOTLIGHT_H

namespace VumiEngine{
    class SpotLight : public VumiEngine::Node{

        glm::mat4 worldMatrix{};
        glm::mat4 modelMatrix{};



        SpotLightShader* shader{};
        GLuint shaderProgram{};


        GLuint _vao{};
        GLuint vertexBuffer{};
        GLuint texCoordBuffer{};
        VumiEngine::Texture *texture{};



        float swingAngle = PI  * 0.2;
        float swingDelta = 0.0f;
        float swingSpeed = 0.3f;
    public:
        glm::vec2 lightDir{};

        SpotLight();
        ~SpotLight();

        void Update(float deltaTime);
        void setBuffer();
        void Render();
    };
}



#endif //WASM_SPOTLIGHT_H
