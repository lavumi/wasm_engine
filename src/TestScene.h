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
    void action0(float deltaTime);
    void action1(float deltaTime);
    void action2(float deltaTime);
};

#endif //WASM_TESTSCENE_H
