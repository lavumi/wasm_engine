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
	1.0f ,
	- 1.0f,
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
	1.0f,
	0.0f,
	0.0f,
	1.0f,
	0.0f,
	0.0f,
	1.0f,
	0.0f,
	0.0f,
	1.0f,
	0.0f,
	0.0f,
	1.0f,
	0.0f,
	0.0f,
	1.0f,
	0.0f,
	0.0f,

	0.0f,
	1.0f,
	0.0f,
	0.0f,
	1.0f,
	0.0f,
	0.0f,
	1.0f,
	0.0f,
	0.0f,
	1.0f,
	0.0f,
	0.0f,
	1.0f,
	0.0f,
	0.0f,
	1.0f,
	0.0f,

	0.0f,
	1.0f,
	1.0f,
	0.0f,
	1.0f,
	1.0f,
	0.0f,
	1.0f,
	1.0f,
	0.0f,
	1.0f,
	1.0f,
	0.0f,
	1.0f,
	1.0f,
	0.0f,
	1.0f,
	1.0f,

	1.0f,
	0.0f,
	1.0f,
	1.0f,
	0.0f,
	1.0f,
	1.0f,
	0.0f,
	1.0f,
	1.0f,
	0.0f,
	1.0f,
	1.0f,
	0.0f,
	1.0f,
	1.0f,
	0.0f,
	1.0f,

	1.0f,
	1.0f,
	0.0f,
	1.0f,
	1.0f,
	0.0f,
	1.0f,
	1.0f,
	0.0f,
	1.0f,
	1.0f,
	0.0f,
	1.0f,
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
	1.0f,

	0.0f,
	1.0f,
	1.0f,

	0.0f,
	1.0f,
	1.0f,

	0.0f,
	1.0f,
	1.0f,

	0.0f,
	1.0f,
	1.0f,
};

TestCube::TestCube(/* args */)
{
}

TestCube::~TestCube()
{
}

void TestCube::makeBuffer()
{

	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

	glGenBuffers(1, &colorbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_color_buffer_data), g_color_buffer_data, GL_STATIC_DRAW);
}

void TestCube::setBuffer(GLuint shaderProgram)
{

	GLuint vertexPosition_modelspace = glGetAttribLocation(shaderProgram, "vertexPosition_modelspace");
	checkGL_error("vertexPosition_modelspace");
	GLuint vertexColor = glGetAttribLocation(shaderProgram, "vertexColor");

	checkGL_error("vertexColor");
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glEnableVertexAttribArray(vertexPosition_modelspace);
	checkGL_error("glEnableVertexAttribArray");

	checkGL_error("glBindBuffer");
	glVertexAttribPointer(
		vertexPosition_modelspace, // attribute. No particular reason for 0, but must match the layout in the shader.
		3,						   // size
		GL_FLOAT,				   // type
		GL_FALSE,				   // normalized?
		0,						   // stride
		(void *)0				   // array buffer offset
	);
	checkGL_error("glVertexAttribPointer");

	// 2nd attribute buffer : colors
	glEnableVertexAttribArray(vertexColor);
	glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
	glVertexAttribPointer(
		vertexColor, // attribute. No particular reason for 1, but must match the layout in the shader.
		3,			 // size
		GL_FLOAT,	 // type
		GL_FALSE,	 // normalized?
		0,			 // stride
		(void *)0	 // array buffer offset
	);
}