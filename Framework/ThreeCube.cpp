#include "precompiled.h"
#include "./Render/Texture.h"
#include "ThreeCube.h"
using namespace VumiEngine;
//region [ Model Data ]
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
        1.0f,-1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,

        -1.0f, 1.0f, 1.0f,
        -1.0f,-1.0f, 1.0f,
        1.0f,-1.0f, 1.0f,



        //right
        1.0f, 1.0f, 1.0f,
        1.0f,-1.0f,-1.0f,
        1.0f, 1.0f,-1.0f,

        1.0f, 1.0f, 1.0f,
        1.0f,-1.0f, 1.0f,
        1.0f,-1.0f,-1.0f,



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


static const GLfloat g_texCoord_buffer_data[] = {

        //0, 0 to 0.33333,0.5
        0.0f,       0.0f,
        0.0f,       0.5f,
        0.33333f,   0.5f,
        0.0f,       0.0f,
        0.33333f,   0.5f,
        0.33333f,   0.0f,
        


        //0.33333 , 0 to 0.66666,0.5
        0.33333f,       0.0f, //좌상
        0.66666f,   0.5f, //우하
        0.66666f,   0.0f, //우상
        0.33333f,       0.0f, //좌상
        0.33333f,       0.5f, //좌하
        0.66666f,   0.5f, //우하
       

         //0.66666 , 0 to 1.0,0.5
        0.66666f,   0.0f, //좌상
        1.0f,       0.5f, //우하
        1.0f,       0.0f, //우상
        0.66666f,   0.0f, //좌상
        0.66666f,   0.5f, //좌하
        1.0f,       0.5f, //우하
        


        //0,0.5 to 0.33333 ,1.0
        0.0f,       0.5f, //좌상
        0.33333f,   1.0f, //우하
        0.33333f,   0.5f, //우상
        0.0f,       0.5f, //좌상
        0.0f,       1.0f, //좌하
        0.33333f,   1.0f, //우하


        // 0.33333 , 0.5 to 0.66666 , 1.0
        0.33333f,   0.5f, //좌상
        0.66666f,   1.0f, //우하
        0.66666f,   0.5f, //우상
        0.33333f,   0.5f, //좌상
        0.33333f,   1.0f, //좌하
        0.66666f,   1.0f, //우하
        
        // 0.66666 , 0.5 to 1.0 , 1.0
        0.66666f,   0.5f,
        0.66666f,   1.0f,
        1.0f,       1.0f,
        0.66666f,   0.5f,
        1.0f,       1.0f,
        1.0f,       0.5f,
};

static uint pitch[3][9] = {
    {0, 1, 2, 9, 10, 11, 18, 19, 20},
    {3, 4, 5, 12, 13, 14, 21, 22, 23},
    {6, 7, 8, 15, 16, 17, 24, 25, 26}
};


static uint roll[3][9] = {
    {0,1,2,3,4,5,6,7,8},
    {9,10,11,12,13,14,15,16,17},
    {18,19,20,21,22,23,24,25,26}
};

static uint yaw[3][9] = {
    {0,3, 6, 9, 12, 15, 18, 21, 24},
    {1,4, 7, 10, 13, 16, 19, 22, 25},
    {2,5, 8, 11, 14, 17, 20, 23, 26}
};



/**
 * @brief inits
 * 
 * 
 *  24  15  6    25  16  7      26  17  8
 *  21  12  3    22  13  4      23  14  5
 *  18  9   0    19  10  1      20  11  2
 */

//endregion

ThreeCube::ThreeCube(/* args */)
{

    for( int x = 0 ; x < 3 ; x ++ ){
        for( int y = 0 ; y < 3 ; y ++ ){
            for( int z = 0 ; z < 3 ; z ++ ){
               modelMatrix[x*9 + y * 3 + z] = glm::translate(glm::mat4(1.0f), glm::vec3( (x-1) * 2.05f , (y-1.0f) * 2.05f , (z-1.0f)*2.05f ));
               rpyMatrix[x*9 + y * 3 + z] = glm::mat4(1.0f);
            }
        }
    }

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


    glGenBuffers(1, &texCoordBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, texCoordBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_texCoord_buffer_data), g_texCoord_buffer_data, GL_STATIC_DRAW);

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

	glBindBuffer(GL_ARRAY_BUFFER, texCoordBuffer);
	glVertexAttribPointer(
		texCoord,
		2,
		GL_FLOAT,
		GL_FALSE,
		0,
		(void *)0);
	glEnableVertexAttribArray(texCoord);


    texture->LoadTexture("Resources/atlas.png");
    texture->BindTexture();
	// glActiveTexture(GL_TEXTURE0); // activate the texture unit first before binding texture
	// glBindTexture(GL_TEXTURE_2D, *texture);
    glBindVertexArray(0);
}

void ThreeCube::_finishRpy( int rpyIndex ){
    for( int i = 0 ; i < 27 ; i ++ ){
        modelMatrix[i] = rpyMatrix[i] * modelMatrix[i];
        rpyMatrix[i] = glm::mat4(1.0f);




    }

    uint* targetArr = nullptr;
    if ( rpyIndex > 5 ){
        targetArr = roll[rpyIndex%3];
    }
    else if ( rpyIndex > 2){
        targetArr = pitch[rpyIndex%3];
    }
    else {
        targetArr = yaw[rpyIndex%3];
    }



    // 0->6
    // 2->0
    // 6->8
    // 8->2


    // 1->3
    // 3->7
    // 5->1
    // 7->5



    /**
     * @brief 
     * 
     *  8   5   2
     *  7   4   1
     *  6   3   0
     *  
     * 
     *  6   7   8
     *  3   4   5   
     *  0   1   2
     */


    glm::mat4 temp = modelMatrix[targetArr[0]];
    modelMatrix[targetArr[0]] = modelMatrix[targetArr[2]];
    modelMatrix[targetArr[2]] = modelMatrix[targetArr[8]];
    modelMatrix[targetArr[8]] = modelMatrix[targetArr[6]];
    modelMatrix[targetArr[6]] = temp;
    
    temp = modelMatrix[targetArr[1]];
    modelMatrix[targetArr[1]] = modelMatrix[targetArr[5]];
    modelMatrix[targetArr[5]] = modelMatrix[targetArr[7]];
    modelMatrix[targetArr[7]] = modelMatrix[targetArr[3]];
    modelMatrix[targetArr[3]] = temp;

}

void ThreeCube::RunCube(int index, float angle){

    float radian = glm::radians(angle*90.0f);
    float w = glm::cos(radian / 2);
    float v = glm::sin(radian / 2);

    uint* targetArr = nullptr;
    glm::vec3 axis;


    if ( index > 5){
        axis = glm::vec3(1,0,0);
        targetArr = roll[index%3];
    }
    else if ( index > 2 ){
        axis = glm::vec3(0,-1,0);
        targetArr = pitch[index%3];
    }
    else {
        axis = glm::vec3(0,0,1);
        targetArr = yaw[index%3];
    }

    glm::vec3 qv = axis * v;
    glm::quat quaternion(w, qv);
    glm::mat4 quatTransform = glm::mat4_cast(quaternion);

    for( int i = 0 ; i < 9 ; i ++ ){
        int targetIndex = targetArr[i];
        rpyMatrix[targetIndex] = quatTransform;
    }
}

int testSequence[3] = {3, 6, 7};
int testCounter = 0;

void ThreeCube::Update(float deltaTime){

    timeSpend += deltaTime;

    if ( testCounter > 3)
    return;

    if ( timeSpend > 1.0f ){
        // rpyRnd = testSequence[Counter++];
        rpyRnd = rand() % 9; 
        timeSpend = 0.0f;
        return;
    }


    if ( rpyRnd == -1 )
        return;


    RunCube(rpyRnd, timeSpend / 0.7f );

    if ( timeSpend >= 0.7f ){
        RunCube(rpyRnd, 1.0f );
        _finishRpy(rpyRnd);
        rpyRnd = -1;
    }


}


void ThreeCube::ToggleRotate(bool isRotate){
    canRotate = isRotate;
}

void ThreeCube::SetRotate(float amount, glm::vec3 axis)
{
    if ( canRotate == false ) return;
    glm::mat4 rotMatrix = glm::rotate(glm::mat4(1.0f), amount * 0.03f, axis);
    worldMatrix = rotMatrix * worldMatrix;
}


//Compile command : "D:\exarion\vendor\emscripten\SDK\emscripten\1.35.0\emcc" Source.cpp -s USE_SDL=2 -s FULL_ES2=1 -o test.html -O3 
// -s ALLOW_MEMORY_GROWTH=1 -s USE_SDL_IMAGE=2 -s USE_SDL_TTF=2 -s SDL2_IMAGE_FORMATS="['jpg']" -Werror -s WARN_ON_UNDEFINED_SYMBOLS=1 -s SIMD=1 -s NO_EXIT_RUNTIME=1 -s AGGRESSIVE_VARIABLE_ELIMINATION=1 -s SEPARATE_ASM=1
//  -s EXPORTED_FUNCTIONS="['_main', '_mainLoop']" 
// -std=c++11 -Werror -s WARN_ON_UNDEFINED_SYMBOLS=1 -s SIMD=1 -s NO_EXIT_RUNTIME=1 -s AGGRESSIVE_VARIABLE_ELIMINATION=1 -s SEPARATE_ASM=1 -I"D:\exarion\vendor\glm"
	

void ThreeCube::Render()
{
	glUseProgram(shader);

	glBindVertexArray(_vao);

	GLuint modelID = glGetUniformLocation(shader, "Model");
	

    //todo drawcall 27짜리 쓰레기 코드
    for( int i = 0 ; i < 27 ; i ++ )
    {
        glm::mat4 finalMat = worldMatrix * rpyMatrix[i] * modelMatrix[i];
        glUniformMatrix4fv(modelID, 1, GL_FALSE, (GLfloat *)&finalMat);

        glDrawArrays(GL_TRIANGLES, 0, 12*3 );
    }

    glBindVertexArray(0);
}