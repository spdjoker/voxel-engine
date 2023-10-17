#ifndef JKR_APPLICATION_HPP
#define JKR_APPLICATION_HPP

#include "engine/input.hpp"
#include "types/vector2i.hpp"

class GLFWwindow;

class Application {
  GLFWwindow* window;
  Input m_input;
  bool isRunning;
  float lastFrameTime;
  float m_deltaTime;

  Vector2i m_windowSize;

  int initGLFW();
  int configure(int width, int height);

  static void keyboardCallback(GLFWwindow* window, int key, int /*scancode*/, int action, int /*mods*/); 
  static void mouseButtonCallback(GLFWwindow* window, int button, int action, int /*mods*/);
  static void mousePositionCallback(GLFWwindow* window, double xpos, double ypos);

public:
  static const unsigned int COLOR_BUFFER_BIT;

  Application();
  ~Application();

  int init(const char* title, int width, int height);
  int init(const char* title);
  void poll();
  void update();
  void render();
  void clear();
  void clean();

  void quit();

  const Vector2i& windowSize() const;
  const Input& input() const;

  float deltaTime() const;
  bool running() const;
};

#endif // !JKR_APPLICATION_HPP
