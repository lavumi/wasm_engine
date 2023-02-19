#include "precompiled.h"
#include "./Render/Shader.h"
#include "Render/Texture.h"
#include "TestCube.h"

static const GLfloat g_vertex_buffer_data[] = {
        -1.0f,-1.0f,-1.0f,-1.0f,-1.0f,1.0f,
        -1.0f,1.0f,1.0f,-1.0f,-1.0f,-1.0f,
        -1.0f,1.0f,1.0f,-1.0f,1.0f,-1.0f,

        1.0f,1.0f,1.0f,1.0f,-1.0f,-1.0f,
        1.0f,1.0f,-1.0f,1.0f,-1.0f,-1.0f,
        1.0f,1.0f,1.0f,1.0f,-1.0f,1.0f,

        1.0f,1.0f,-1.0f,-1.0f,-1.0f,-1.0f,
        -1.0f,1.0f,-1.0f,1.0f,1.0f,-1.0f,
        1.0f,-1.0f,-1.0f,-1.0f,-1.0f,-1.0f,

        1.0f,1.0f,1.0f,1.0f,1.0f,-1.0f,
        -1.0f,1.0f,-1.0f,1.0f,1.0f,1.0f,
        -1.0f,1.0f,-1.0f,-1.0f,1.0f,1.0f,

        1.0f,-1.0f,1.0f,-1.0f,-1.0f,-1.0f,
        1.0f,-1.0f,-1.0f,1.0f,-1.0f,1.0f,
        -1.0f,-1.0f,1.0f,-1.0f,-1.0f,-1.0f,

        1.0f,1.0f,1.0f,-1.0f,1.0f,1.0f,
        1.0f,-1.0f,1.0f,-1.0f,1.0f,1.0f,
        -1.0f,-1.0f,1.0f,1.0f,-1.0f,1.0f,
                                               };

static const GLfloat g_index_buffer_data[] = {
        0.0f,0.0f,1.0f,0.0f,1.0f,1.0f,
        0.0f,0.0f,1.0f,1.0f,0.0f,1.0f,
        0.0f,0.0f,1.0f,0.0f,1.0f,1.0f,
        0.0f,0.0f,1.0f,1.0f,0.0f,1.0f,


        0.0f,0.0f,1.0f,1.0f,0.0f,1.0f,
        0.0f,0.0f,1.0f,0.0f,1.0f,1.0f,
        0.0f,0.0f,1.0f,0.0f,1.0f,1.0f,
        0.0f,0.0f,1.0f,1.0f,0.0f,1.0f,


        0.0f,0.0f,1.0f,1.0f,0.0f,1.0f,
        0.0f,0.0f,1.0f,0.0f,1.0f,1.0f,
        0.0f,0.0f,1.0f,0.0f,1.0f,1.0f,
        0.0f,0.0f,1.0f,1.0f,0.0f,1.0f,
};

// One color for each vertex. They were generated randomly.
static const GLfloat g_color_buffer_data[] = {
    0.583f,  0.771f,  0.014f,
    0.609f,  0.115f,  0.436f,
    0.327f,  0.483f,  0.844f,
    0.822f,  0.569f,  0.201f,
    0.435f,  0.602f,  0.223f,
    0.310f,  0.747f,  0.185f,
    0.597f,  0.770f,  0.761f,
    0.559f,  0.436f,  0.730f,
    0.359f,  0.583f,  0.152f,
    0.483f,  0.596f,  0.789f,
    0.559f,  0.861f,  0.639f,
    0.195f,  0.548f,  0.859f,
    0.014f,  0.184f,  0.576f,
    0.771f,  0.328f,  0.970f,
    0.406f,  0.615f,  0.116f,
    0.676f,  0.977f,  0.133f,
    0.971f,  0.572f,  0.833f,
    0.140f,  0.616f,  0.489f,
    0.997f,  0.513f,  0.064f,
    0.945f,  0.719f,  0.592f,
    0.543f,  0.021f,  0.978f,
    0.279f,  0.317f,  0.505f,
    0.167f,  0.620f,  0.077f,
    0.347f,  0.857f,  0.137f,
    0.055f,  0.953f,  0.042f,
    0.714f,  0.505f,  0.345f,
    0.783f,  0.290f,  0.734f,
    0.722f,  0.645f,  0.174f,
    0.302f,  0.455f,  0.848f,
    0.225f,  0.587f,  0.040f,
    0.517f,  0.713f,  0.338f,
    0.053f,  0.959f,  0.120f,
    0.393f,  0.621f,  0.362f,
    0.673f,  0.211f,  0.457f,
    0.820f,  0.883f,  0.371f,
    0.982f,  0.099f,  0.879f
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
    glDeleteBuffers(sizeof(g_index_buffer_data), &texcoordbuffer);
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

	GLuint vertexPosition_modelspace = glGetAttribLocation(shader, "vertexPosition");
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