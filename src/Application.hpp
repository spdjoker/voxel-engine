#ifndef JKR_APPLICATION_HPP
#define JKR_APPLICATION_HPP

class GLFWwindow;

struct Application {
  Application();
  ~Application();

  int init(const char* title, int width, int height, bool resizable);
  void poll();
  void update();
  void render();
  void clean();

  bool running() const;

private:
  bool isRunning;
  GLFWwindow* window;
};

#endif // !JKR_APPLICATION_HPP
