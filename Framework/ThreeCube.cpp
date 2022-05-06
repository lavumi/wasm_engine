#include "precompiled.h"
#include "./Render/Shader.h"
#include "Texture.h"
#include "ThreeCube.h"

static const GLfloat g_vertex_buffer_data[] = {

    //left side
        -1.0f,-1.0f,-1.0f, // triangle 1 : begin
        -1.0f,-1.0f, 1.0f,
        -1.0f, 1.0f, 1.0f, // triangle 1 : end

        -1.0f,-1.0f,-1.0f,
        -1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f,-1.0f,



        //front
        1.0f, 1.0f,-1.0f, // triangle 2 : begin
        -1.0f,-1.0f,-1.0f,
        -1.0f, 1.0f,-1.0f, // triangle 2 : end

        1.0f, 1.0f,-1.0f,
        1.0f,-1.0f,-1.0f,
        -1.0f,-1.0f,-1.0f,



        //down
        1.0f,-1.0f, 1.0f,
        -1.0f,-1.0f,-1.0f,
        1.0f,-1.0f,-1.0f,

        1.0f,-1.0f, 1.0f,
        -1.0f,-1.0f, 1.0f,
        -1.0f,-1.0f,-1.0f,



        //back
        -1.0f, 1.0f, 1.0f,
        -1.0f,-1.0f, 1.0f,
        1.0f,-1.0f, 1.0f,

        1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f, 1.0f,
        1.0f,-1.0f, 1.0f,



        //right
        1.0f, 1.0f, 1.0f,
        1.0f,-1.0f,-1.0f,
        1.0f, 1.0f,-1.0f,

        1.0f,-1.0f,-1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f,-1.0f, 1.0f,



        //top
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f,-1.0f,
        -1.0f, 1.0f,-1.0f,

        1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f,-1.0f,
        -1.0f, 1.0f, 1.0f,


};
static const GLfloat g_color_buffer_data[] = {
        0.583f,  0.771f,  0.014f,
        0.583f,  0.771f,  0.014f,
        0.583f,  0.771f,  0.014f,
        0.583f,  0.771f,  0.014f,
        0.583f,  0.771f,  0.014f,
        0.583f,  0.771f,  0.014f,
        

        0.597f,  0.770f,  0.761f,
        0.597f,  0.770f,  0.761f,
        0.597f,  0.770f,  0.761f,
        0.597f,  0.770f,  0.761f,
        0.597f,  0.770f,  0.761f,
        0.597f,  0.770f,  0.761f,
       

        0.014f,  0.184f,  0.576f,
        0.014f,  0.184f,  0.576f,
        0.014f,  0.184f,  0.576f,
        0.014f,  0.184f,  0.576f,
        0.014f,  0.184f,  0.576f,
        0.014f,  0.184f,  0.576f,
        

        0.997f,  0.513f,  0.064f,
       0.997f,  0.513f,  0.064f,
       0.997f,  0.513f,  0.064f,
       0.997f,  0.513f,  0.064f,
       0.997f,  0.513f,  0.064f,
       0.997f,  0.513f,  0.064f,

        0.055f,  0.953f,  0.042f,
        0.055f,  0.953f,  0.042f,
        0.055f,  0.953f,  0.042f,
        0.055f,  0.953f,  0.042f,
        0.055f,  0.953f,  0.042f,
        0.055f,  0.953f,  0.042f,
        
        0.517f,  0.713f,  0.338f,
        0.517f,  0.713f,  0.338f,
        0.517f,  0.713f,  0.338f,
        0.517f,  0.713f,  0.338f,
        0.517f,  0.713f,  0.338f,
        0.517f,  0.713f,  0.338f,
};


ThreeCube::ThreeCube(/* args */)
{
	worldMatrix = glm::mat4(1.0f);
	texture = new Texture();
}

ThreeCube::~ThreeCube()
{
	glDeleteBuffers(sizeof(g_vertex_buffer_data), &vertexBuffer);
	glDeleteBuffers(sizeof(g_color_buffer_data), &colorBuffer);
}

void ThreeCube::Init()
{
}

void ThreeCube::makeBuffer()
{
}

void ThreeCube::setBuffer(GLuint shaderProgram)
{

	this->shader = shaderProgram;

	glGenVertexArrays(1, &_vao);
	glBindVertexArray(_vao);

	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

    glGenBuffers(1, &colorBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_color_buffer_data), g_color_buffer_data, GL_STATIC_DRAW);


	GLuint vertexPosition = glGetAttribLocation(shader, "vertexPosition");
	GLuint vertexColor = glGetAttribLocation(shader, "vertexColor");
	GLuint texCoord = glGetAttribLocation(shader, "aTexCoord");

	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer); //버퍼를 GL_ARRAY_BUFFER 에 바인드
	glVertexAttribPointer(
		vertexPosition, // attribute. Vertex 속성의 위치
		3,						   // 크기
		GL_FLOAT,				   // 데이터 타입
		GL_FALSE,				   // 정규화
		0,						   // stride 속성 세트 사이의 공백
		(void *)0				   // 시작 위치
	);
	glEnableVertexAttribArray(vertexPosition); //버텍스 버퍼를 활성화
	// 2nd attribute buffer : colors

	glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
	glVertexAttribPointer(
		vertexColor,
		3,
		GL_FLOAT,
		GL_FALSE,
		0,
		(void *)0);
	glEnableVertexAttribArray(vertexColor);

//	glBindBuffer(GL_ARRAY_BUFFER, texcoordbuffer);
//	glVertexAttribPointer(
//		texCoord,
//		2,
//		GL_FLOAT,
//		GL_FALSE,
//		0,
//		(void *)0);
//	glEnableVertexAttribArray(texCoord);
//
//	texture->LoadTexture("cubetexture.png");

	// glActiveTexture(GL_TEXTURE0); // activate the texture unit first before binding texture
	// glBindTexture(GL_TEXTURE_2D, *texture);
    glBindVertexArray(0);
}

void ThreeCube::Update(float deltaTime)
{
	worldMatrix = glm::rotate(
		worldMatrix,
		glm::radians(0.7f),
		glm::vec3(0.0f, 1.0f, 0.0f));
}

void ThreeCube::Render()
{
	glUseProgram(shader);

	glBindVertexArray(_vao);

	GLuint modelID = glGetUniformLocation(shader, "Model");
	glUniformMatrix4fv(modelID, 1, GL_FALSE, (GLfloat *)&worldMatrix);


	texture->BindTexture();
    glDrawArrays(GL_TRIANGLES, 0, 12*3);

    glBindVertexArray(0);
}