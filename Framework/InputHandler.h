#pragma once
#include <functional>
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
  void HandleEvent( SDL_Event event );

  std::function<void()> myfxClickLeft;
  std::function<void()> mykeyboardDown[322];
  std::function<void()> mykeyboardUp[322];

private :

  bool KEYS[322]; 
};







