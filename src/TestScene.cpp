//
// Created by Lavumi on 2023/02/22.
//
#include "../Framework/precompiled.h"
#include "TestScene.h"


void TestScene::Init() {



    light = new VumiEngine::SpotLight(-PI * 0.0f, false );
    light->SetPosition(glm::vec3(4,8,0));
    light->SetColor(glm::vec4(1.0f,0,0,0.2f));
    this->AddChild(light,1);


    light2 = new VumiEngine::SpotLight(PI * 0.0f, true);
    light2->SetPosition(glm::vec3(-4,8,0));
    light2->SetColor(glm::vec4(0,1,1,0.2f));
    this->AddChild(light2,1);


    spriteAni = new VumiEngine::SpriteAnimation("Resources/helltaker_atlas.png" , 12 , 0.08333f);
    this->AddChild(spriteAni , 0 );


}


void TestScene::Render() {
    Node::Render();
}

void TestScene::Update(float deltaTime) {
    Node::Update(deltaTime);
}
