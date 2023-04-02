#pragma once



namespace VumiEngine {
    class Renderer;
    class ThreeCube;
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
        void Run();
        void Update(float deltaTime) const;
        void Render() const;
        void AddScene(Scene *scene);
        glm::mat4 GetCameraVP();
    };
}



