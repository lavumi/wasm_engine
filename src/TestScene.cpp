//
// Created by Lavumi on 2023/02/22.
//
#include "../Framework/precompiled.h"
#include "TestScene.h"


void TestScene::Init() {
//    Node::Init();


//    cube = new ThreeCube();
//    this->AddChild(cube , 0);
//
//    VumiEngine::InputHandler::GetInputHandler().myfxMouseLeftUp = [&]{
//        cube->ToggleRotate(false);
//    };
//
//
//    VumiEngine::InputHandler::GetInputHandler().myfxMouseLeftDown = [&]{
//        cube->ToggleRotate(true);
//    };
//
//    VumiEngine::InputHandler::GetInputHandler().mouseMoveEvent = [&](int inputX, int inputY){
//        cube->SetRotate((float)inputX * 0.05f, glm::vec3(0,5,0));
//        cube->SetRotate((float)inputY * 0.05f, glm::vec3(-5,0,0));
//    };

    sprite = new Sprite("Resources/atlas.png");
    this->AddChild(sprite , 0 );
}

void TestScene::Render() {
    Node::Render();
}

void TestScene::Update(float deltaTime) {
    Node::Update(deltaTime);
}
