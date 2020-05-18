#include "../precompiled.h"
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
    shader->makeShader();
    testCube->setBuffer( shader->shader_program);

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



    SDL_DisplayMode DM;
    SDL_GetCurrentDisplayMode(0, &DM);
    auto Width = DM.w;
    auto Height = DM.h;

    std::cout << "Native WindowSize " << Width << ", " << Height << std::endl;

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
    //shader->Update(deltaTime);


    glm::mat4 VP        =  camera->GetVP();
    shader->SetUniformMatrix4fv("VP", (GLfloat*)&VP);

    testCube->Update(deltaTime);
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

{
    testCube->Render();
}

    SDL_GL_SwapWindow(window);
}

void Renderer::toggleFullscreen(){
    Uint32 FullscreenFlag = SDL_WINDOW_FULLSCREEN;
    bool IsFullscreen = SDL_GetWindowFlags(window) & FullscreenFlag;
    SDL_SetWindowFullscreen(window, IsFullscreen ? 0 : FullscreenFlag);
    SDL_ShowCursor(IsFullscreen);
}