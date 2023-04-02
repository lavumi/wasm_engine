//
// Created by Lavumi on 2023/02/22.
//
#include "../Framework/precompiled.h"
#include "TestScene.h"


void TestScene::Init() {



    light = new VumiEngine::SpotLight();
    light->SetAngle(-PI * 0.13f);
    light->SetPosition(glm::vec3(4,8,0));
    light->SetColor(glm::vec4(0.9f,0,0,0.5f));
    this->AddChild(light,1);


    light2 = new VumiEngine::SpotLight();
    light2->SetAngle(PI * 0.13f);
    light2->SetPosition(glm::vec3(-4,8,0));
    light2->SetColor(glm::vec4(0,0.9,0.9,0.5f));
    this->AddChild(light2,1);


    spriteAni = new VumiEngine::SpriteAnimation("Resources/helltaker_atlas.png" , 12 , 0.0515f);
    this->AddChild(spriteAni , 0 );


    currentAction = 0;
}
void TestScene::action0(float deltaTime) {
    timeSpent += deltaTime;

    if ( timeSpent > 3.0f){
        int rnd = std::rand();
        if ( rnd % 5 >= 4 ){
            currentAction = 1;
        }
    }
}


void TestScene::action1(float deltaTime) {
    auto lightAngle = light->GetAngle();
//    std::cout << "angle : " << lightAngle <<std::endl;
    if ( lightAngle < PI * 0.13f){
        light->SetAngle( lightAngle + deltaTime * PI  * 0.2f);
        light2->SetAngle( -lightAngle - deltaTime * PI  * 0.2f);
    }
    else {
        light->SetAngle(PI * 0.13f);
        light2->SetAngle(-PI * 0.13f);
        int rnd = std::rand();
        spriteAni->ChangeCharacter(rnd%9);
        currentAction = 2;
    }
}


void TestScene::action2(float deltaTime) {
    auto lightAngle = light->GetAngle();
//    std::cout << "angle : " << lightAngle <<std::endl;
    if ( lightAngle > -PI * 0.13f){
        light2->SetAngle( -lightAngle + deltaTime * PI  * 0.2f);
        light->SetAngle( lightAngle - deltaTime * PI  * 0.2f);
    }
    else {
        light2->SetAngle(PI * 0.13f);
        light->SetAngle(-PI * 0.13f);
        currentAction = -1;
    }
}


void TestScene::Render() {
    Node::Render();
}

void TestScene::Update(float deltaTime) {
    Node::Update(deltaTime);

    switch (currentAction) {
        case 0:
            action0(deltaTime);
            break;
        case 1:
            action1(deltaTime);
            break;
        case 2:
            action2(deltaTime);
            break;
        default:
            break;
    }
}