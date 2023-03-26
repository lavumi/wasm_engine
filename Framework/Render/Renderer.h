#pragma once

#include "../precompiled.h"

namespace VumiEngine {
    class Shader;

    class Camera;

    class Renderer {
    private:
        void makeShader();

        SDL_Window *window = NULL;
        SDL_GLContext context;

        Shader *shader;
        Camera *camera;

    public:
        Renderer(/* args */);

        ~Renderer();

        void Init();

        void Update(float deltaTime);

        void InitRender() const;

        void FinishRender();

        void SetCamera(Camera *camera);

        GLuint GetShader();

        GLfloat rotation_angle;
        GLuint length_of_attributes;
        GLuint vbo;

        const char *vertexSource;
        const char *fragmentSource;

        bool background_is_black = true;

        void toggleFullscreen();
    };

    static void checkGL_error(std::string text) {
        GLenum error;

        error = glGetError();

        if (error != GL_NO_ERROR) {
            std::cout << "--------" << text << " not working"
                      << "--------" << std::endl;

            if (error == GL_INVALID_OPERATION) {
                std::cout << "INVALID OPERATION" << std::endl;
            }

            if (error == GL_INVALID_VALUE) {
                std::cout << "NO VALUE" << std::endl;
            }

            if (error == GL_OUT_OF_MEMORY) {
                std::cout << "NO MEMORY" << std::endl;
            }

            if (error == GL_STACK_OVERFLOW) {
                std::cout << "NO OVERFLOW" << std::endl;
            }

            if (error == GL_INVALID_FRAMEBUFFER_OPERATION) {
                std::cout << "invalid framebuffer <-" << std::endl;
            }

            if (error == GL_OUT_OF_MEMORY) {
                std::cout << "Out of Memory" << std::endl;
            }
            std::cout << "--------------------------------------------" << std::endl;
        } else {
        }
    }
}