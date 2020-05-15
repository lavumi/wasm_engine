#include "Shader.h"
#include "../TestCube.h"
#include "Camera.h"
#include "Renderer.h"



Renderer::Renderer(/* args */)
{

    shader = new Shader();
    testCube = new TestCube();
}

Renderer::~Renderer()
{
    SDL_GL_DeleteContext(context);
    SDL_Quit();
}



void Renderer::makeShader()
{
    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    shader->makeShader();
    shader->setShader();
    
    glm::mat4 VP        =  camera->GetVP();
    shader->SetUniformMatrix4fv("VP", (GLfloat*)&VP);
    testCube->makeBuffer();
    testCube->setBuffer( shader->shader_program);

// //버퍼 세팅
//     GLuint vao;
//     glGenVertexArrays(1, &vao);
//     glBindVertexArray(vao);

//     glGenBuffers(1, &vbo);
//     glBindBuffer(GL_ARRAY_BUFFER, vbo);
//     glBufferData(GL_ARRAY_BUFFER, sizeof(attributes), attributes, GL_DYNAMIC_DRAW);
}

void Renderer::Init()
{
    SDL_Init(SDL_INIT_EVERYTHING);

    #if __EMSCRIPTEN__
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
    #else
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
    #endif

    window = SDL_CreateWindow("Lavumi", 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL);
    context = SDL_GL_CreateContext(window);

    glewExperimental = GL_TRUE;
    glewInit();

	// Enable depth test
	glEnable(GL_DEPTH_TEST);
	// Accept fragment if it closer to the camera than the former one
	glDepthFunc(GL_LESS); 

	// Cull triangles which normal is not towards the camera
	glEnable(GL_CULL_FACE);

    const GLubyte *version;
    version = glGetString(GL_VERSION);
    std::cout << "version: " << version << std::endl;

    InputHandler::getInstance()->myfxClickLeft = [&]{
        background_is_black = !background_is_black;
    };

    makeShader();
}

void Renderer::Update(float deltaTime)
{
    shader->Update(deltaTime);
    // for (GLuint i = 0; i < length_of_attributes; i = i + 5)
    // {
    //     float x = attributes[i];
    //     float y = attributes[i + 1];

    //     attributes[i] = x * cos(rotation_angle) - y * sin(rotation_angle);
    //     attributes[i + 1] = y * cos(rotation_angle) + x * sin(rotation_angle);
    // }

    // glBufferData(GL_ARRAY_BUFFER, sizeof(attributes), attributes, GL_DYNAMIC_DRAW);

    glm::mat4 VP        =  camera->GetVP();
    shader->SetUniformMatrix4fv("VP", (GLfloat*)&VP);
}

void Renderer::SetCamera( Camera* pCamera ){
    this->camera = pCamera;
}

void Renderer::Render()
{
    // Clear the screen
    if (background_is_black)
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    else
        glClearColor(0.9f, 0.9f, 0.9f, 1.0f);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glDrawArrays(GL_TRIANGLES, 0, 12 * 3);
    SDL_GL_SwapWindow(window);
}

