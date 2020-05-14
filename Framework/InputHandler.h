#pragma once

class InputHandler
{

private:
  static InputHandler *instance;
  InputHandler();
  ~InputHandler();

public:
  static InputHandler *getInstance()
  {
    if (instance == nullptr)
      instance = new InputHandler();
    return instance;
  }
  static void Delete();

  void Update(float deltaTime);
  void HandleEvent(SDL_Event event);
  void HandleEvent(int keycode, bool pressed);

  std::function<void()> myfxClickLeft;

  bool SetKeyboardDownEvent(int, std::function<void()>);
  bool SetKeyboardUpEvent(int, std::function<void()>);

private:
  typedef std::map<int, std::function<void()>> KeyboardInput;
  KeyboardInput mykeyboardDown;
  KeyboardInput mykeyboardUp;

  /*************************************
   * Javascript keycode to SDL keycode *
   *************************************/
  int keycode[128] = {0};
  void setkeycode();
};
