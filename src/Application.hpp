#ifndef JKR_APPLICATION_HPP
#define JKR_APPLICATION_HPP

#include "engine/input.hpp"

class GLFWwindow;

class Application {
  bool isRunning;
  GLFWwindow* window;
  Input m_input;

public:

  Application();
  ~Application();

  int init(const char* title, int width, int height, bool resizable);
  void poll();
  void update();
  void render();
  void clean();

  void quit();
  
  const Input& input() const;
  bool running() const;
};

#endif // !JKR_APPLICATION_HPP
