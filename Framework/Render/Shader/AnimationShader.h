//
// Created by Lavumi on 2023/03/28.
//

#ifndef WASM_ANIMATIONSHADER_H
#define WASM_ANIMATIONSHADER_H


namespace VumiEngine {
    class AnimationShader {
    private:
        /* data */

        const char *vertexSource;
        const char *fragmentSource;

    public:
        GLuint shader_program;

        AnimationShader(/* args */);

        ~AnimationShader();

        void MakeShader();

//        void SetUniformMatrix4fv(const std::string &name, GLfloat *value) const;
    };
}





#endif //WASM_ANIMATIONSHADER_H
