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
    InputHandler::getInstance()->mykeyboardDown[97] = [&]{
        camera->SetMoveLeft( true );
    };//L
    InputHandler::getInstance()->mykeyboardDown[100]= [&]{
        camera->SetMoveRight( true );
    };//R
        InputHandler::getInstance()->mykeyboardUp[97] = [&]{
        camera->SetMoveLeft( false );
    };//L
    InputHandler::getInstance()->mykeyboardUp[100]= [&]{
        camera->SetMoveRight( false );
    };//R

        //left
    InputHandler::getInstance()->mykeyboardDown[119] = [&]{
        camera->SetMoveFront( true );
    };//L
    InputHandler::getInstance()->mykeyboardDown[115]= [&]{
        camera->SetMoveBack( true );
    };//R
        InputHandler::getInstance()->mykeyboardUp[119] = [&]{
        camera->SetMoveFront( false );
    };//L
    InputHandler::getInstance()->mykeyboardUp[115]= [&]{
        camera->SetMoveBack( false );
    };//R

    std::cout << "Init Director " << std::endl;
    //InputHandler::getInstance()->mykeyboardInput[119];//U
    //InputHandler::getInstance()->mykeyboardInput[115];//D
}

Director::~Director()
{
    delete renderer;
}


void Director::Update(float deltaTime){
    renderer->Update(deltaTime);
    camera->Update(deltaTime);
}


void Director::Render(){
    renderer->Render();
}