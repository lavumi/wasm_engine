#include "precompiled.h"
#include "Render/Camera.h" 
#include "Director.h"
#include "ThreeCube.h"

using namespace VumiEngine;
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
        // camera->SetMoveFront( true );
        // testCube->Roll(1,1);
    });//L

    InputHandler::getInstance()->SetKeyboardUpEvent(119 , [&]{
        // camera->SetMoveFront( false );
    });//L


    InputHandler::getInstance()->SetKeyboardDownEvent(115, [&]{
        // camera->SetMoveBack( true );
        // testCube->Roll(2,1);
    });//R
    InputHandler::getInstance()->SetKeyboardUpEvent(115, [&]{
        // camera->SetMoveBack( false );
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


void Director::Update(float deltaTime) const{
    renderer->Update(deltaTime);
    if ( currentScene != nullptr)
        currentScene->Update( deltaTime );

    testCube->Update(deltaTime);
    camera->Update(deltaTime);
}


void Director::Render() const{
    renderer->InitRender();
    if ( currentScene != nullptr)
        currentScene->Render();

    testCube->Render();
    renderer->FinishRender();
}

void Director::AddScene(Scene* scene) {
    this->currentScene = scene;
}
