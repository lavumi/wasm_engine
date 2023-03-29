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
//    VumiEngine::ThreeCube* cube;
//    VumiEngine::Sprite* sprite;
//    VumiEngine::Sprite* sprite2;
    VumiEngine::SpriteAnimation* spriteAni;
    VumiEngine::SpotLight* light;
    VumiEngine::SpotLight* light2;
};

#endif //WASM_TESTSCENE_H
