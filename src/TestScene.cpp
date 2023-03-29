//
// Created by Lavumi on 2023/02/22.
//
#include "../Framework/precompiled.h"
#include "TestScene.h"


void TestScene::Init() {

    spriteAni = new VumiEngine::SpriteAnimation("Resources/helltaker_atlas.png" , 12 , 0.08333f);
    this->AddChild(spriteAni , 0 );
    light = new VumiEngine::SpotLight();
    this->AddChild(light,1);



}


void TestScene::Render() {
    Node::Render();
}

void TestScene::Update(float deltaTime) {
    Node::Update(deltaTime);
}
