#include "../precompiled.h"

#include "../ThreeCube.h"
//#include "../TestCube.h"

using namespace VumiEngine;
Renderer::Renderer(/* args */)
{

    shader = new Shader();

    // testCube = new TestCube();
}

Renderer::~Renderer()
{
    SDL_GL_DeleteContext(context);
    SDL_Quit();
}



void Renderer::makeShader()
{


}

void Renderer::Init(ThreeCube* cube )
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

    shader->MakeShader();

    cube->setBuffer( shader->shader_program);
}

void Renderer::Update(float deltaTime)
{
    glm::mat4 VP        =  camera->GetVP();
    shader->SetUniformMatrix4fv("VP", (GLfloat*)&VP);
}

void Renderer::SetCamera( Camera* pCamera ){
    this->camera = pCamera;
}


void Renderer::toggleFullscreen(){
    Uint32 FullscreenFlag = SDL_WINDOW_FULLSCREEN;
    bool IsFullscreen = SDL_GetWindowFlags(window) & FullscreenFlag;
    SDL_SetWindowFullscreen(window, IsFullscreen ? 0 : FullscreenFlag);
    SDL_ShowCursor(IsFullscreen);
}

void Renderer::InitRender() const {
    // Clear the screen
    if (background_is_black)
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    else
        glClearColor(0.9f, 0.9f, 0.9f, 1.0f);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::FinishRender() {
    SDL_GL_SwapWindow(window);
}

