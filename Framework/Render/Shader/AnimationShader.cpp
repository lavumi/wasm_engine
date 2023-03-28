//
// Created by Lavumi on 2023/03/28.
//
#include "../../precompiled.h"
#include "AnimationShader.h"


using namespace VumiEngine;

AnimationShader::AnimationShader() {
    vertexSource = R"glsl(
        #version 100
        // Input vertex data, different for all executions of this shaderProgram.
        attribute vec3 vertexPosition;
        attribute vec2 aTexCoord;

        // Output data ; will be interpolated for each fragment.
        varying mediump vec2 texCoord;

        // Values that stay constant for the whole mesh.
        uniform mat4 VP;
        uniform mat4 Model;
        uniform vec2 uvTarget;


        void main(){

            // Output position of the vertex, in clip space : MVP * position
            gl_Position =  VP * Model * vec4(vertexPosition,1);

            texCoord = aTexCoord + uvTarget;
        }
        )glsl";
    fragmentSource = R"glsl(
        #version 100
        // Interpolated values from the vertex shaders
        varying mediump vec2 texCoord;
        uniform sampler2D myTexture;

        void main(){

            // Output color = color specified in the vertex shaderProgram,
            // interpolated between all 3 surrounding vertices
            // gl_FragColor = vec4(fragmentColor,1);

            mediump vec4 sampled = texture2D(myTexture, texCoord);
            gl_FragColor =  sampled;//vec4(texCoord, 1,1);

        }
        )glsl";
}

AnimationShader::~AnimationShader() {
    glDeleteShader(shader_program);
}

void AnimationShader::MakeShader() {
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

    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);
}

