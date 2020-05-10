
#include "Shader.h"

Shader::Shader(/* args */)
{
    vertexSource = R"glsl(
#version 330 core

// Input vertex data, different for all executions of this shader.
layout(location = 0) in vec3 vertexPosition_modelspace;
layout(location = 1) in vec3 vertexColor;

// Output data ; will be interpolated for each fragment.
out vec3 fragmentColor;
// Values that stay constant for the whole mesh.
uniform mat4 MVP;

void main(){	

	// Output position of the vertex, in clip space : MVP * position
	gl_Position =  MVP * vec4(vertexPosition_modelspace,1);

	// The color of each vertex will be interpolated
	// to produce the color of each fragment
	fragmentColor = vertexColor;
}
)glsl";

    fragmentSource = R"glsl(
#version 330 core

// Interpolated values from the vertex shaders
in vec3 fragmentColor;

// Ouput data
out vec3 color;

void main(){

	// Output color = color specified in the vertex shader, 
	// interpolated between all 3 surrounding vertices
	color = fragmentColor;

}
)glsl";
  //  makeShader();
}

Shader::~Shader()
{
    glDeleteShader(shader_program);
}


void Shader::makeShader(){
    GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, &vertexSource, NULL);
    glCompileShader(vertex_shader);
    GLint vertex_shader_status;
    glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &vertex_shader_status);

    // char vertexLogBuffer[512];
    // glGetShaderInfoLog(vertex_shader, 512, NULL, vertexLogBuffer);
    // std::cout << "vertex_shader_status: " << vertex_shader_status << " " << vertexLogBuffer << std::endl;

    GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, &fragmentSource, NULL);
    glCompileShader(fragment_shader);
    GLint fragment_shader_status;
    glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &fragment_shader_status);

    // char fragmentLogBuffer[512];
    // glGetShaderInfoLog(fragment_shader, 512, NULL, fragmentLogBuffer);
    // std::cout << "fragment_shader_status: " << fragment_shader_status << " " << fragmentLogBuffer << std::endl;

    shader_program = glCreateProgram();
    glAttachShader(shader_program, vertex_shader);
    glAttachShader(shader_program, fragment_shader);
    glLinkProgram(shader_program);


    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);




}


void Shader::setShader(){
    glUseProgram(shader_program);

    //bind shader data



    GLuint MatrixID = glGetUniformLocation(shader_program, "MVP");
    float MVP[4][4] = {
        {1.0f,0,0,0},
        {0,1.0f,0,0},
        {0,0,1.0f,0},
        {0,0,0,1.0f}
    };
    glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);


    // GLint pos_attrib = glGetAttribLocation(shader_program, "position");
    // GLint color_attrib = glGetAttribLocation(shader_program, "color");
    // glVertexAttribPointer(pos_attrib, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), 0);
    // glEnableVertexAttribArray(pos_attrib);

    // glVertexAttribPointer(color_attrib, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (GLvoid *)(2 * sizeof(float)));
    // glEnableVertexAttribArray(color_attrib);
}