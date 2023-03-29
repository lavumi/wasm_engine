//
// Created by Lavumi on 2023/03/28.
//
#include "../../precompiled.h"
#include "SpotLightShader.h"

using namespace VumiEngine;

SpotLightShader::SpotLightShader() {
    vertexSource = R"glsl(
        #version 100
        // Input vertex data, different for all executions of this shaderProgram.
        attribute vec3 vertexPosition;
        attribute vec2 aTexCoord;

        // Output data ; will be interpolated for each fragment.
        varying mediump vec2 texCoord;

        // Values that stay constant for the whole mesh.
        uniform mat4 Model;
        uniform mat4 VP;


        void main(){

            // Output position of the vertex, in clip space : MVP * position
            gl_Position =  VP * Model * vec4(vertexPosition,1);

            texCoord = aTexCoord;
        }
        )glsl";
    fragmentSource = R"glsl(
        #version 100
        // Interpolated values from the vertex shaders
        varying mediump vec2 texCoord;
        uniform mediump vec4 LightColor;
        uniform sampler2D Texture;


        void main(){
            mediump vec4 sampled = texture2D(Texture, texCoord);
            gl_FragColor = vec4(LightColor.rgb * (1.0-sampled.r) , sampled.r +LightColor.a );
        }
        )glsl";
}

SpotLightShader::~SpotLightShader() {
    glDeleteShader(shader_program);
}

void SpotLightShader::MakeShader() {
//    std::cout << "Make Shader Called" << std::endl;
    GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, &vertexSource, nullptr);
    glCompileShader(vertex_shader);
    GLint vertex_shader_status;
    glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &vertex_shader_status);

    char vertexLogBuffer[512];
    glGetShaderInfoLog(vertex_shader, 512, nullptr, vertexLogBuffer);
    std::cout << "vertex_shader_status: " << vertex_shader_status << " " << vertexLogBuffer << std::endl;

    GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, &fragmentSource, nullptr);
    glCompileShader(fragment_shader);
    GLint fragment_shader_status;
    glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &fragment_shader_status);

    char fragmentLogBuffer[512];
    glGetShaderInfoLog(fragment_shader, 512, nullptr, fragmentLogBuffer);
    std::cout << "fragment_shader_status: " << fragment_shader_status << " " << fragmentLogBuffer << std::endl;

    shader_program = glCreateProgram();
    glAttachShader(shader_program, vertex_shader);
    glAttachShader(shader_program, fragment_shader);

    glLinkProgram(shader_program);

    GLint Result = GL_FALSE;
    int InfoLogLength;

    glGetProgramiv(shader_program, GL_LINK_STATUS, &Result);
    glGetProgramiv(shader_program, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if ( InfoLogLength > 0 ){
        std::vector<char> ProgramErrorMessage(InfoLogLength+1);
        glGetProgramInfoLog(shader_program, InfoLogLength, NULL, &ProgramErrorMessage[0]);
        printf("%s\n", &ProgramErrorMessage[0]);
    }

    glDetachShader(shader_program, vertex_shader);
    glDetachShader(shader_program, fragment_shader);

    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);
}
