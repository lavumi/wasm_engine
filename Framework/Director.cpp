#include "precompiled.h"
#include "Render/Camera.h"
#include "Director.h"
#include "Node/ThreeCube.h"

using namespace VumiEngine;

Director::Director(/* args */) {
    InputHandler::GetInputHandler();
    renderer = new Renderer();
    camera = new Camera();

    renderer->Init();

    //left
    InputHandler::GetInputHandler().SetKeyboardDownEvent(97, [&] {
        camera->SetMoveLeft(true);
    });
    InputHandler::GetInputHandler().SetKeyboardDownEvent(100, [&] {
        camera->SetMoveRight(true);
    });
    InputHandler::GetInputHandler().SetKeyboardUpEvent(97, [&] {
        camera->SetMoveLeft(false);
    });
    InputHandler::GetInputHandler().SetKeyboardUpEvent(100, [&] {
        camera->SetMoveRight(false);
    });


    //left
    InputHandler::GetInputHandler().SetKeyboardDownEvent(119, [&] {
        // camera->SetMoveFront( true );
        // testCube->Roll(1,1);
    });//L

    InputHandler::GetInputHandler().SetKeyboardUpEvent(119, [&] {
        // camera->SetMoveFront( false );
    });//L


    InputHandler::GetInputHandler().SetKeyboardDownEvent(115, [&] {
        // camera->SetMoveBack( true );
        // testCube->Roll(2,1);
    });//R
    InputHandler::GetInputHandler().SetKeyboardUpEvent(115, [&] {
        // camera->SetMoveBack( false );
    });//R



    // InputHandler::getInstance()->SetKeyboardDownEvent(122 , [&]{
    //     testCube->ToggleRotate();
    // });//L
    InputHandler::GetInputHandler().SetKeyboardUpEvent(122, [&] {

    });//R

    InputHandler::GetInputHandler().SetKeyboardUpEvent(102, [&] {
        renderer->toggleFullscreen();
    });//L


    InputHandler::GetInputHandler().myfxMouseLeftUp = [&]{
//        testCube->ToggleRotate(false);
    };

    InputHandler::GetInputHandler().myfxMouseLeftDown = [&]{
//        testCube->ToggleRotate(true);
    };

    InputHandler::GetInputHandler().mouseMoveEvent = [&](int inputX, int inputY){
      //  std::cout << "rotation " << inputX << "     " << inputY << std::endl;
//       testCube->SetRotate((float)inputX * 0.05f, glm::vec3(0,5,0));
//       testCube->SetRotate((float)inputY * 0.05f, glm::vec3(-5,0,0));
    };


}

Director::~Director() {
    delete renderer;
}

void Director::Update(float deltaTime) const {
    renderer->Update(deltaTime);
    if (currentScene != nullptr)
        currentScene->Update(deltaTime);

//    testCube->Update(deltaTime);
    camera->Update(deltaTime);
}

void Director::Render() const {
    renderer->InitRender();
    if (currentScene != nullptr)
        currentScene->Render();

    renderer->FinishRender();
}

void Director::AddScene(Scene *scene) {
    this->currentScene = scene;
}

glm::mat4 Director::GetCameraVP() {
    return this->camera->GetVP();
}

