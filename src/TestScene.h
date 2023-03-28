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
    VumiEngine::ThreeCube* cube;
    VumiEngine::Sprite* sprite;
    VumiEngine::SpriteAnimation* spriteAni;
};

#endif //WASM_TESTSCENE_H
