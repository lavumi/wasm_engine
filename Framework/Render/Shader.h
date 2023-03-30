#pragma once

namespace VumiEngine {
    class Shader {
    private:


    public:
        GLuint shader_program;

        Shader(/* args */);

        ~Shader();

        void MakeShader(std::string shaderName);

    };
}



