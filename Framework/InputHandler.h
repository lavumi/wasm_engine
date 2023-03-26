#pragma once

namespace VumiEngine {
    class InputHandler {

    private:
        static InputHandler *instance;

        InputHandler();

        ~InputHandler();

    public:
        static InputHandler *getInstance() {
            if (instance == nullptr)
                instance = new InputHandler();
            return instance;
        }

        static void Delete();

        void Update(float deltaTime);

        void HandleEvent(SDL_Event event);

        void HandleEvent(int pKeyCode, bool pressed);

        void HandleMouseInput(SDL_MouseMotionEvent mouseMotion) const;

        void HandleMouseInput(int deltaX, int deltaY) const;

        std::function<void()> myfxMouseLeftDown;
        std::function<void()> myfxMouseLeftUp;

        bool SetKeyboardDownEvent(int, const std::function<void()>&);

        bool SetKeyboardUpEvent(int, std::function<void()>);


        std::function<void(int, int)> mouseMoveEvent;

    private:
        typedef std::map<int, std::function<void()>> KeyboardInput;
        KeyboardInput mykeyboardDown;
        KeyboardInput mykeyboardUp;


        /*************************************
         * Javascript keycode to SDL keycode *
         *************************************/
        int keycode[128] = {0};

        void setKeyCode();

        static int sanitizeInput(int keycode);
    };
}