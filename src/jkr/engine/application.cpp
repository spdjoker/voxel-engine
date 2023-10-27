#include "application.hpp"
#include "fmt/core.h"

#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

void Application::keyboardCallback(GLFWwindow* window, int key, int /*scancode*/, int action, int /*mods*/) {
  if (action == GLFW_PRESS) {
    ((Application*)glfwGetWindowUserPointer(window))->m_input.setKeyPressed(key);
    return;
  }
  if (action == GLFW_RELEASE) {
    ((Application*)glfwGetWindowUserPointer(window))->m_input.setKeyReleased(key);
    return;
  }
}

void Application::mouseButtonCallback(GLFWwindow* window, int button, int action, int /*mods*/) {
  
  if (action == GLFW_PRESS) {
    ((Application*)glfwGetWindowUserPointer(window))->m_input.setMouseButtonPressed(button);
    return;
  }
  if (action == GLFW_RELEASE) {
    ((Application*)glfwGetWindowUserPointer(window))->m_input.setMouseButtonReleased(button);
    return;
  }
}

void Application::mousePositionCallback(GLFWwindow* window, double xpos, double ypos) {
  ((Application*)glfwGetWindowUserPointer(window))->m_input.setMousePosition(xpos, ypos);
}

Application::Application() : window(nullptr), m_input(), isRunning(false), m_windowSize() {}
Application::~Application() {}

int Application::initGLFW() {
  if (window) {
    std::cout << "\e[31mError: Tried initializing a window that already exists.\e[0m\n";
    return 1;
  }

  if (!glfwInit()) {
    std::cout << "\e[31mError: GLFW failed to initialize.\e[0m\n";
    return 1;
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
  return 0;
}

int Application::configure(int width, int height) {
  if (!window) {
    std::cout << "\e[31mError: Failed to create a window.\e[0m\n";
    return 1;
  }

  // Assign callbacks
  glfwSetWindowUserPointer(window, this);
  glfwSetKeyCallback(window, keyboardCallback);
  glfwSetMouseButtonCallback(window, mouseButtonCallback);
  glfwSetCursorPosCallback(window, mousePositionCallback);
  
  glfwMakeContextCurrent(window);
  if (glewInit() != GLEW_OK) {
    std::cout << "\e[31mError: GLEW is not OK.\e[0m\n";
    glfwDestroyWindow(window);
    return 1;
  }

  m_windowSize = {width, height};
  isRunning = true;
  lastFrameTime = glfwGetTime();

  glEnable(GL_CULL_FACE);
  glCullFace(GL_BACK);

  return 0;
}

int Application::init(const char* title, int width, int height) {
  int error = initGLFW();
  if (error) {
    return error;
  }

  window = glfwCreateWindow(width, height, title, NULL, NULL);
  return configure(width, height);
}

int Application::init(const char* title) {
  int error = initGLFW();
  if (error) {
    return error;
  }

  GLFWmonitor* primaryMonitor = glfwGetPrimaryMonitor();
  if (!primaryMonitor) {
    fmt::println("\e[31mError: Failed to find primary monitor to open application in fullscreen.");
    glfwTerminate();
    return 1;
  }
  const GLFWvidmode* videoMode = glfwGetVideoMode(primaryMonitor);
  if (!videoMode) {
    fmt::println("\e[31mError: Failed to obtain videomode of primary monitor.");
    glfwTerminate();
    return 1;
  }

  window = glfwCreateWindow(videoMode->width, videoMode->height, title, primaryMonitor, NULL);
  return configure(videoMode->width, videoMode->height);
}

void Application::poll() {
  m_input.clear();
  glfwPollEvents();

  float currFrameTime = glfwGetTime();
  m_deltaTime = currFrameTime - lastFrameTime;
  lastFrameTime = currFrameTime;

  if (glfwWindowShouldClose(window)) {
    isRunning = false;
  }
}

void Application::clear() {
  glClear(GL_COLOR_BUFFER_BIT);
}

void Application::render() {
  glfwSwapBuffers(window);
}

void Application::clean() {
  if (window) {
    glfwDestroyWindow(window);
  }
}

void Application::quit() {
  glfwSetWindowShouldClose(window, GLFW_TRUE);
}

const Vector2i& Application::windowSize() const { return m_windowSize; }
const Input& Application::input() const { return m_input; }

float Application::deltaTime() const { return m_deltaTime; }
bool Application::running() const { return isRunning; }
