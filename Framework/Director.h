#pragma once

class ThreeCube;

namespace VumiEngine {
    class Renderer;

    class Scene;

    class Camera;

    class Director {

    public:
        static Director &GetDirector() {
            static Director director;
            return director;
        }

    private:
        /* data */
        Renderer *renderer{};
        Camera *camera{};

        Scene *currentScene{};

        Director();

        ~Director();

    public:

        void Update(float deltaTime) const;

        void Render() const;

        void AddScene(Scene *scene);

//        ThreeCube *testCube;




        GLuint GetShaderProgram();
    };
}



