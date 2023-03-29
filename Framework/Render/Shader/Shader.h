#pragma once

namespace VumiEngine {
    class Shader {
    private:
        /* data */

        const char *vertexSource;
        const char *fragmentSource;

    public:
        GLuint shader_program;

        Shader(/* args */);

        ~Shader();

        void MakeShader();

    };
}



