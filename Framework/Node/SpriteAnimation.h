//
// Created by Lavumi on 2023/03/28.
//

#ifndef WASM_SPRITEANIMATION_H
#define WASM_SPRITEANIMATION_H

namespace VumiEngine {

    class SpriteAnimation  : public VumiEngine::Node{

        glm::mat4 worldMatrix{};
        glm::mat4 modelMatrix{};


        Shader* animationShader;
        GLuint shaderProgram{};


        GLuint _vao{};
        GLuint vertexBuffer{};
        GLuint texCoordBuffer{};
        VumiEngine::Texture *texture{};
        GLfloat g_texCoord_buffer_data[12];

        int animationStep = 0;
        int characterType = 0;
        int maxFrameIndex;
        float interval;
        float timeStamp;


    public:
        SpriteAnimation(const std::string& imgPath,int maxFrameIndex, float interval);
        ~SpriteAnimation();

        void Update(float deltaTime);
        void setBuffer();
        void Render();

        void ChangeCharacter(int index);
    };

} // VumiEngine

#endif //WASM_SPRITEANIMATION_H
