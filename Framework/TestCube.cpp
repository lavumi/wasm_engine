#include "precompiled.h"
#include "./Render/Shader.h"
#include "Texture.h"
#include "TestCube.h"

static const GLfloat g_vertex_buffer_data[] = {
	-1.0f,
	-1.0f,
	-1.0f,
	-1.0f,
	-1.0f,
	1.0f,
	-1.0f,
	1.0f,
	1.0f,
	-1.0f,
	-1.0f,
	-1.0f,
	-1.0f,
	1.0f,
	1.0f,
	-1.0f,
	1.0f,
	-1.0f,

	1.0f,
	1.0f,
	1.0f,
	1.0f,
	-1.0f,
	-1.0f,
	1.0f,
	1.0f,
	-1.0f,
	1.0f,
	-1.0f,
	-1.0f,
	1.0f,
	1.0f,
	1.0f,
	1.0f,
	-1.0f,
	1.0f,

	1.0f,
	1.0f,
	-1.0f,
	-1.0f,
	-1.0f,
	-1.0f,
	-1.0f,
	1.0f,
	-1.0f,
	1.0f,
	1.0f,
	-1.0f,
	1.0f,
	-1.0f,
	-1.0f,
	-1.0f,
	-1.0f,
	-1.0f,

	1.0f,
	1.0f,
	1.0f,
	1.0f,
	1.0f,
	-1.0f,
	-1.0f,
	1.0f,
	-1.0f,
	1.0f,
	1.0f,
	1.0f,
	-1.0f,
	1.0f,
	-1.0f,
	-1.0f,
	1.0f,
	1.0f,

	1.0f,
	-1.0f,
	1.0f,
	-1.0f,
	-1.0f,
	-1.0f,
	1.0f,
	-1.0f,
	-1.0f,
	1.0f,
	-1.0f,
	1.0f,
	-1.0f,
	-1.0f,
	1.0f,
	-1.0f,
	-1.0f,
	-1.0f,

	1.0f,
	1.0f,
	1.0f,
	-1.0f,
	1.0f,
	1.0f,
	1.0f,
	-1.0f,
	1.0f,
	-1.0f,
	1.0f,
	1.0f,
	-1.0f,
	-1.0f,
	1.0f,
	1.0f,
	-1.0f,
	1.0f,

};

// One color for each vertex. They were generated randomly.
static const GLfloat g_color_buffer_data[] = {
	// Front face
	-1.0, -1.0, 1.0,
	1.0, -1.0, 1.0,
	1.0, 1.0, 1.0,
	-1.0, 1.0, 1.0,

	// Back face
	-1.0, -1.0, -1.0,
	-1.0, 1.0, -1.0,
	1.0, 1.0, -1.0,
	1.0, -1.0, -1.0,

	// Top face
	-1.0, 1.0, -1.0,
	-1.0, 1.0, 1.0,
	1.0, 1.0, 1.0,
	1.0, 1.0, -1.0,

	// Bottom face
	-1.0, -1.0, -1.0,
	1.0, -1.0, -1.0,
	1.0, -1.0, 1.0,
	-1.0, -1.0, 1.0,

	// Right face
	1.0, -1.0, -1.0,
	1.0, 1.0, -1.0,
	1.0, 1.0, 1.0,
	1.0, -1.0, 1.0,

	// Left face
	-1.0, -1.0, -1.0,
	-1.0, -1.0, 1.0,
	-1.0, 1.0, 1.0,
	-1.0, 1.0, -1.0};

static const GLfloat g_index_buffer_data[] = {
	0.0f,
	0.0f,
	1.0f,
	0.0f,
	1.0f,
	1.0f,
	0.0f,
	0.0f,
	1.0f,
	1.0f,
	0.0f,
	1.0f,

	0.0f,
	0.0f,
	1.0f,
	0.0f,
	1.0f,
	1.0f,
	0.0f,
	0.0f,
	1.0f,
	1.0f,
	0.0f,
	1.0f,

	0.0f,
	0.0f,
	1.0f,
	0.0f,
	1.0f,
	1.0f,
	0.0f,
	0.0f,
	1.0f,
	1.0f,
	0.0f,
	1.0f,

	0.0f,
	0.0f,
	1.0f,
	0.0f,
	1.0f,
	1.0f,
	0.0f,
	0.0f,
	1.0f,
	1.0f,
	0.0f,
	1.0f,

	0.0f,
	0.0f,
	1.0f,
	0.0f,
	1.0f,
	1.0f,
	0.0f,
	0.0f,
	1.0f,
	1.0f,
	0.0f,
	1.0f,

	0.0f,
	0.0f,
	1.0f,
	0.0f,
	1.0f,
	1.0f,
	0.0f,
	0.0f,
	1.0f,
	1.0f,
	0.0f,
	1.0f,
};

TestCube::TestCube(/* args */)
{
	worldMatrix = glm::mat4(1.0f);
	texture = new Texture();
}

TestCube::~TestCube()
{
	glDeleteBuffers(sizeof(g_vertex_buffer_data), &vertexbuffer);
	glDeleteBuffers(sizeof(g_color_buffer_data), &colorbuffer);
}

void TestCube::Init()
{
}

void TestCube::makeBuffer()
{
}

void TestCube::setBuffer(GLuint shaderProgram)
{

	this->shader = shaderProgram;

	glGenVertexArrays(1, &_vao);
	glBindVertexArray(_vao);

	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

	glGenBuffers(1, &colorbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_color_buffer_data), g_color_buffer_data, GL_STATIC_DRAW);

	glGenBuffers(1, &texcoordbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, texcoordbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_index_buffer_data), g_index_buffer_data, GL_STATIC_DRAW);

	GLuint vertexPosition_modelspace = glGetAttribLocation(shader, "vertexPosition_modelspace");
	GLuint vertexColor = glGetAttribLocation(shader, "vertexColor");
	GLuint texCoord = glGetAttribLocation(shader, "aTexCoord");

	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer); //버퍼를 GL_ARRAY_BUFFER 에 바인드
	glVertexAttribPointer(
		vertexPosition_modelspace, // attribute. Vertex 속성의 위치
		3,						   // 크기
		GL_FLOAT,				   // 데이터 타입
		GL_FALSE,				   // 정규화
		0,						   // stride 속성 세트 사이의 공백
		(void *)0				   // 시작 위치
	);
	glEnableVertexAttribArray(vertexPosition_modelspace); //버텍스 버퍼를 활성화
	// 2nd attribute buffer : colors

	glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
	glVertexAttribPointer(
		vertexColor,
		3,
		GL_FLOAT,
		GL_FALSE,
		0,
		(void *)0);
	glEnableVertexAttribArray(vertexColor);

	glBindBuffer(GL_ARRAY_BUFFER, texcoordbuffer);
	glVertexAttribPointer(
		texCoord,
		2,
		GL_FLOAT,
		GL_FALSE,
		0,
		(void *)0);
	glEnableVertexAttribArray(texCoord);

	texture->LoadTexture("cubetexture.png");

	// glActiveTexture(GL_TEXTURE0); // activate the texture unit first before binding texture
	// glBindTexture(GL_TEXTURE_2D, *texture);
}

void TestCube::Update(float deltaTime)
{
	worldMatrix = glm::rotate(
		worldMatrix,
		glm::radians(0.7f),
		glm::vec3(0.0f, 1.0f, 0.0f));
}

void TestCube::Render()
{
	glUseProgram(shader);

	glBindVertexArray(_vao);

	GLuint ModelID = glGetUniformLocation(shader, "Model");
	glUniformMatrix4fv(ModelID, 1, GL_FALSE, (GLfloat *)&worldMatrix);
	texture->BindTexture();
	glDrawArrays(GL_TRIANGLES, 0, 6 * 2 * 3);
}