#pragma once 
#include "../precompiled.h"

namespace VumiEngine{
    class Camera;
    class Shader
    {
    private:
        /* data */

        const char *vertexSource ;
        const char *fragmentSource ;

        const char *textureVertexSource ;
        const char *textureFragmentSource ;

    public:
        GLuint shader_program;
        Shader(/* args */);
        ~Shader();

        void MakeShader();
        void SetUniformMatrix4fv(const std::string& name, GLfloat* value ) const;
    };
}



