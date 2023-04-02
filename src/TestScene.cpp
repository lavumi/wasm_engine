//
// Created by Lavumi on 2023/02/22.
//

#include "../Framework/precompiled.h"
#include <random>
#include "TestScene.h"


void TestScene::Init() {



    light = new VumiEngine::SpotLight();
    light->SetAngle(-PI * 0.108f);
    light->SetPosition(glm::vec3(4,8,0));
    light->SetColor(glm::vec4(0.9f,0,0,0.5f));
    this->AddChild(light,1);


    light2 = new VumiEngine::SpotLight();
    light2->SetAngle(PI * 0.108f);
    light2->SetPosition(glm::vec3(-4,8,0));
    light2->SetColor(glm::vec4(0.9f) - glm::vec4(0.9f,0,0,0.5f));
    this->AddChild(light2,1);


    spriteAni = new VumiEngine::SpriteAnimation("Resources/helltaker_atlas.png" , 12 , 0.0515f);
    this->AddChild(spriteAni , 0 );


    currentAction = 0;

}
void TestScene::action0(float deltaTime) {
    if ( timeSpent > 3.0f){
        currentAction = RANDOM(0,6);
    }
}


void TestScene::action1(float deltaTime) {

    auto lightAngle = light->GetAngle();
    if ( actionFlag == false ){
        if ( lightAngle < PI * 0.0f){
            light->SetAngle( lightAngle + deltaTime * PI  * 0.2f);
            light2->SetAngle( -lightAngle - deltaTime * PI  * 0.2f);
        }
        else {
            light->SetAngle(PI * 0.0f);
            light2->SetAngle(-PI * 0.0f);
            int rnd = RANDOM(0,9);
            spriteAni->ChangeCharacter(rnd);
            actionFlag = true;
        }
    }
    else {
        if ( lightAngle > -PI * 0.108f){
            light2->SetAngle( -lightAngle + deltaTime * PI  * 0.2f);
            light->SetAngle( lightAngle - deltaTime * PI  * 0.2f);
        }
        else {
            light2->SetAngle(PI * 0.108f);
            light->SetAngle(-PI * 0.108f);
            currentAction = 0;
            actionFlag = false;
        }
    }

}


void TestScene::action2(float deltaTime) {
    if ( actionFlag == false ){

        lightPower -= deltaTime * 0.5f;
        light->SetBright(lightPower);
        light2->SetBright(lightPower);

        if ( lightPower <= 0.0f){

            float r = RANDOM(0.0f, .9f);
            float g = RANDOM(0.0f, .9f);
            float b = RANDOM(0.0f, .9f);
            auto lightColor = glm::vec4(r, g, b, 1.0f);

            light->SetColor( lightColor );
            light2->SetColor( (glm::vec4(0.9f) - lightColor));


            int rnd = RANDOM(0,9);
            spriteAni->ChangeCharacter(rnd%9);
            actionFlag = true;
        }
    }
    else {

        lightPower += deltaTime * 0.2f;
        light->SetBright(lightPower);
        light2->SetBright(lightPower);
        if ( lightPower >= 1.0f){
            currentAction = 0;
            actionFlag = false;
        }
    }


}


void TestScene::action3(float deltaTime) {

    if ( timeSpent > 3.0f){
        currentAction = 0;
    }
    else if (timeSpent > 1.5f){
        light2->SetBright( 1.0f);
    }
    else if ( timeSpent > 1.0f){
        light->SetBright(  1.0f);
    }
    else if ( timeSpent > 0.5f){
        light2->SetBright(0.0f);

        float r = RANDOM(0.0f, .9f);
        float g = RANDOM(0.0f, .9f);
        float b = RANDOM(0.0f, .9f);

        auto lightColor = glm::vec4(r, g, b, 1.0f);
        light->SetColor( lightColor );
        light2->SetColor( (glm::vec4(0.9f) - lightColor));

        int rnd = RANDOM(0,9);
        spriteAni->ChangeCharacter(rnd%9);
    }
    else {
        light->SetBright(0.0f);
    }
}

void TestScene::action4(float deltaTime) {

}


void TestScene::Render() {
    Node::Render();
}

void TestScene::Update(float deltaTime) {
    Node::Update(deltaTime);
    timeSpent += deltaTime;
    switch (currentAction) {
        case 1:
            action1(deltaTime);
            break;
        case 2:
            action2(deltaTime);
            break;
        case 3:
            action3(deltaTime);
            break;
        default:
            action0(deltaTime);
            break;
    }

    if ( timeSpent > 3.0f){
        timeSpent = 0.0f;
    }
}