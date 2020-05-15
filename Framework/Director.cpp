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
    InputHandler::getInstance()->SetKeyboardDownEvent(97, [&]{
        camera->SetMoveLeft( true );
    });
        InputHandler::getInstance()->SetKeyboardDownEvent(100, [&]{
        camera->SetMoveRight( true );
    });
        InputHandler::getInstance()->SetKeyboardUpEvent(97, [&]{
        camera->SetMoveLeft( false );
    });
        InputHandler::getInstance()->SetKeyboardUpEvent(100, [&]{
        camera->SetMoveRight( false );
    });


        //left
    InputHandler::getInstance()->SetKeyboardDownEvent(119 , [&]{
        camera->SetMoveFront( true );
    });//L
    InputHandler::getInstance()->SetKeyboardDownEvent(115, [&]{
        camera->SetMoveBack( true );
    });//R
        InputHandler::getInstance()->SetKeyboardUpEvent(119 , [&]{
        camera->SetMoveFront( false );
    });//L
    InputHandler::getInstance()->SetKeyboardUpEvent(115, [&]{
        camera->SetMoveBack( false );
    });//R


    InputHandler::getInstance()->SetKeyboardUpEvent(102 , [&]{
        renderer->toggleFullscreen();
    });//L




    InputHandler::getInstance()->mouseMoveEvent = [&](int inputX, int inputY){
      //  std::cout << "rotation " << inputX << "     " << inputY << std::endl;
        camera->SetRotate((float)inputX * 0.05f, glm::vec3(0,-1,0));
        camera->SetRotate((float)inputY * 0.05f, glm::vec3(1,0,0));
    };
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