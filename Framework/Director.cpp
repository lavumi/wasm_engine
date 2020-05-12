#include "precompiled.h"
#include "Render/Camera.h" 
#include "Director.h"


Director::Director(/* args */)
{


    InputHandler::getInstance();
    renderer = new Renderer();
    camera = new Camera();
    renderer->SetCamera(camera);
    renderer->Init();

    //left
    InputHandler::getInstance()->mykeyboardInput[97] = [&]{
        camera->SetMoveLeft( true );
                    std::cout << "CameraMovememt"<<  std::endl; 
    };//L
    InputHandler::getInstance()->mykeyboardInput[100]= [&]{
        camera->SetMoveLeft( false );
                            std::cout << "CameraMovememt"<<  std::endl; 
    };//R
    //InputHandler::getInstance()->mykeyboardInput[119];//U
    //InputHandler::getInstance()->mykeyboardInput[115];//D
}

Director::~Director()
{
    delete renderer;
}


void Director::Update(){
    renderer->Update();
    camera->Update();
}


void Director::Render(){
    renderer->Render();
}