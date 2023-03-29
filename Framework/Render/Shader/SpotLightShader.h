//
// Created by Lavumi on 2023/03/28.
//

#ifndef WASM_SPOTLIGHTSHADER_H
#define WASM_SPOTLIGHTSHADER_H

namespace VumiEngine {
    class SpotLightShader {
    private:
        /* data */

        const char *vertexSource;
        const char *fragmentSource;

    public:
        GLuint shader_program;

        SpotLightShader(/* args */);

        ~SpotLightShader();

        void MakeShader();
    };

} // VumiEngine

#endif //WASM_SPOTLIGHTSHADER_H
