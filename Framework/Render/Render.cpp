#include "Shader.h"
#include "../TestCube.h"
#include "Renderer.h"
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600


static float attributes[] = {
    0.0f,
    0.5f,
    1.0f,
    0.0f,
    0.0f,

    0.5f,
    -0.5f,
    0.0f,
    1.0f,
    0.0f,

    -0.5f,
    -0.5f,
    0.0f,
    0.0f,
    1.0f
};

Renderer::Renderer(/* args */)
{


    rotation_angle = -0.01;
    length_of_attributes = sizeof(attributes) / sizeof(attributes[0]);

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
    
    shader->makeShader();
    shader->setShader();
    testCube->makeBuffer();
    testCube->setBuffer();

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

    const GLubyte *version;
    version = glGetString(GL_VERSION);
    std::cout << "version: " << version << std::endl;

    InputHandler::getInstance()->myfxClickLeft = [&]{
        background_is_black = !background_is_black;
    };

    makeShader();
}

void Renderer::Update()
{
    // for (GLuint i = 0; i < length_of_attributes; i = i + 5)
    // {
    //     float x = attributes[i];
    //     float y = attributes[i + 1];

    //     attributes[i] = x * cos(rotation_angle) - y * sin(rotation_angle);
    //     attributes[i + 1] = y * cos(rotation_angle) + x * sin(rotation_angle);
    // }

    // glBufferData(GL_ARRAY_BUFFER, sizeof(attributes), attributes, GL_DYNAMIC_DRAW);
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

