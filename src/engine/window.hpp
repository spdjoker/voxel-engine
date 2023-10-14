#ifndef JKR_WINDOW_HPP
#define JKR_WINDOW_HPP

class Window {
  void* glfwWindow;

  Window(void* window); 

public:
  ~Window();
  
  void PollEvents();
  void SwapBuffers();
  bool closing() const;

  static Window* Create(const char* title, int width, int height, bool resizable = true);
};

#endif // !JKR_WINDOW_HPP
