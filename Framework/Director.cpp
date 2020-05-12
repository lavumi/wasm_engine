#include "precompiled.h"
#include "Render/Camera.h" 
#include "Director.h"


Director::Director(/* args */)
{
    renderer = new Renderer();
    camera = new Camera();
    renderer->SetCamera(camera);
    renderer->Init();
}

Director::~Director()
{
    delete renderer;
}


void Director::Update(){
    renderer->Update();
    
}


void Director::Render(){
    renderer->Render();
}