//
// Created by Lavumi on 2023/03/26.
//

#ifndef WASM_SPRITE_H
#define WASM_SPRITE_H

namespace VumiEngine{
    class Sprite : public VumiEngine::Node{

        glm::mat4 worldMatrix{};
        glm::mat4 modelMatrix{};

        GLuint shader{};
        GLuint _vao{};
        GLuint vertexBuffer{};
        GLuint colorBuffer{};

        GLuint texCoordBuffer{};

        VumiEngine::Texture *texture{};


    public:
        Sprite(std::string path);
        ~Sprite();

        void Update(float deltaTime);
        void setBuffer(GLuint shaderProgram);
        void Render();
    };
}



#endif //WASM_SPRITE_H
