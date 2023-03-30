#include <fstream>
#include <sstream>

#include "../precompiled.h"
#include "Shader.h"

using namespace VumiEngine;

Shader::Shader() {

}

Shader::~Shader() {
    glDeleteShader(shader_program);
}


void Shader::MakeShader(std::string shaderName) {

    std::string vertPath = "Resources/Shader/" + shaderName + ".vert";
    std::string fragPath = "Resources/Shader/" + shaderName + ".frag";

    std::string VertexShaderCode;
    std::ifstream VertexShaderStream(SDL_GetBasePath() + vertPath, std::ios::in);
    if(VertexShaderStream.is_open()){
        std::stringstream sstr;
        sstr << VertexShaderStream.rdbuf();
        VertexShaderCode = sstr.str();
        VertexShaderStream.close();
    }else{
        printf("Impossible to open %s Are you in the right directory ? Don't forget to read the FAQ !\n" , (SDL_GetBasePath() + vertPath).c_str());
        return;
    }

    // Read the Fragment Shader code from the file
    std::string FragmentShaderCode;
    std::ifstream FragmentShaderStream(SDL_GetBasePath() + fragPath, std::ios::in);
    if(FragmentShaderStream.is_open()){
        std::stringstream sstr;
        sstr << FragmentShaderStream.rdbuf();
        FragmentShaderCode = sstr.str();
        FragmentShaderStream.close();
    }


//    std::cout << "Make Shader Called" << std::endl;
    GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    char const * vertexSource = VertexShaderCode.c_str();
    glShaderSource(vertex_shader, 1, &vertexSource, nullptr);
    glCompileShader(vertex_shader);
    GLint vertex_shader_status;
    glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &vertex_shader_status);

    char vertexLogBuffer[512];
    glGetShaderInfoLog(vertex_shader, 512, nullptr, vertexLogBuffer);
    std::cout << "vertex_shader_status: " << vertex_shader_status << " " << vertexLogBuffer << std::endl;

    GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    char const * fragmentSource = FragmentShaderCode.c_str();
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
    if ( InfoLogLength > 0 && Result != GL_TRUE){
        std::vector<char> ProgramErrorMessage(InfoLogLength+1);
        glGetProgramInfoLog(shader_program, InfoLogLength, NULL, &ProgramErrorMessage[0]);
        printf("%s\n", &ProgramErrorMessage[0]);
    }

    glDetachShader(shader_program, vertex_shader);
    glDetachShader(shader_program, fragment_shader);

    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);

}
