//
// Created by Lavumi on 2023/02/22.
//

#ifndef WASM_TESTSCENE_H
#define WASM_TESTSCENE_H


class TestScene : public VumiEngine::Scene{
public:
    void Init();
    void Render();
    void Update(float deltaTime);


private:
    VumiEngine::SpriteAnimation* spriteAni;
    VumiEngine::SpotLight* light;
    VumiEngine::SpotLight* light2;


    int currentAction;




    float timeSpent = 0.0f;
    bool actionFlag = false;
    void action0(float deltaTime);
    void action1(float deltaTime);

//    glm::vec4 lightColor = glm::vec4(0.9f,0,0,0.5f);
    GLfloat lightPower = 1.0f;
    void action2(float deltaTime);


    void action3(float deltaTime);
    void action4(float deltaTime);



};

#endif //WASM_TESTSCENE_H
