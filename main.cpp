#include "./Framework/precompiled.h"
#include "./src/TestScene.h"


using namespace VumiEngine;
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
int WinMain()
#else
int main()
#endif
{
    Director::GetDirector();


    //이게 맞나...
    auto * testScene = new TestScene();
    testScene->Init();


    Director::GetDirector().AddScene(testScene);
    Director::GetDirector().Run();
    return 0;
}