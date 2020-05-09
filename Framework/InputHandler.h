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



  void HandleEvent( SDL_Event event );

  std::function<void()> myfxClickLeft;

private :


};




