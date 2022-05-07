#include "precompiled.h"
#include "Render/Camera.h" 
#include "Director.h"
#include "ThreeCube.h"



Director::Director(/* args */)
{


    InputHandler::getInstance();
    renderer = new Renderer();
    camera = new Camera();

    testCube = new ThreeCube();
    renderer->SetCamera(camera);
    renderer->Init(testCube);
    


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



    // InputHandler::getInstance()->SetKeyboardDownEvent(122 , [&]{
    //     testCube->ToggleRotate();
    // });//L
    InputHandler::getInstance()->SetKeyboardUpEvent(122, [&]{

    });//R

    InputHandler::getInstance()->SetKeyboardUpEvent(102 , [&]{
        renderer->toggleFullscreen();
    });//L


    InputHandler::getInstance()->myfxMouseLeftUp = [&]{
        testCube->ToggleRotate(false);
    };

    InputHandler::getInstance()->myfxMouseLeftDown = [&]{
        testCube->ToggleRotate(true);
    };

    InputHandler::getInstance()->mouseMoveEvent = [&](int inputX, int inputY){
      //  std::cout << "rotation " << inputX << "     " << inputY << std::endl;
       testCube->SetRotate((float)inputX * 0.05f, glm::vec3(0,5,0));
       testCube->SetRotate((float)inputY * 0.05f, glm::vec3(-5,0,0));
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