#include "../precompiled.h"
#include "Camera.h"
#include "Shader.h"

Shader::Shader(/* args */)
{
    vertexSource = R"glsl(
        #version 100
// Input vertex data, different for all executions of this shader.
attribute vec3 vertexPosition_modelspace;
attribute vec3 vertexColor;

// Output data ; will be interpolated for each fragment.
varying mediump vec3 fragmentColor;
// Values that stay constant for the whole mesh.
uniform mat4 VP;
uniform mat4 Model;
void main(){	

	// Output position of the vertex, in clip space : MVP * position
	gl_Position =  VP * Model * vec4(vertexPosition_modelspace,1);

	// The color of each vertex will be interpolated
	// to produce the color of each fragment
	fragmentColor = vertexColor;
}
)glsl";

    fragmentSource = R"glsl(
                #version 100
// Interpolated values from the vertex shaders
varying mediump vec3 fragmentColor;

void main(){

	// Output color = color specified in the vertex shader, 
	// interpolated between all 3 surrounding vertices
	gl_FragColor = vec4(fragmentColor,1);

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

    char vertexLogBuffer[512];
    glGetShaderInfoLog(vertex_shader, 512, NULL, vertexLogBuffer);
    std::cout << "vertex_shader_status: " << vertex_shader_status << " " << vertexLogBuffer << std::endl;

    GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, &fragmentSource, NULL);
    glCompileShader(fragment_shader);
    GLint fragment_shader_status;
    glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &fragment_shader_status);

    char fragmentLogBuffer[512];
    glGetShaderInfoLog(fragment_shader, 512, NULL, fragmentLogBuffer);
    std::cout << "fragment_shader_status: " << fragment_shader_status << " " << fragmentLogBuffer << std::endl;

    shader_program = glCreateProgram();
    glAttachShader(shader_program, vertex_shader);
    glAttachShader(shader_program, fragment_shader);
    glLinkProgram(shader_program);


    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);




}



void Shader::setShader(){
    glUseProgram(shader_program);
}

void Shader::SetUniformMatrix4fv(std::string name, GLfloat* value ){
    GLuint MatrixID = glGetUniformLocation(shader_program, name.c_str());
    glUniformMatrix4fv(MatrixID, 1, GL_FALSE,value);
}
