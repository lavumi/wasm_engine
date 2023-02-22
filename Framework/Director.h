#pragma once
class ThreeCube;

namespace VumiEngine {
    class Renderer;
    class Scene;
    class Camera;
    class Director
    {
    private:
        /* data */
        Renderer* renderer;
        Camera* camera;

        Scene *currentScene;
    public:
        Director(/* args */);
        ~Director();

        void Update(float deltaTime) const;
        void Render() const;

        void AddScene( Scene* scene );

        ThreeCube *testCube;
    };
}



