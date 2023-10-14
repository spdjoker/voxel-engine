#include "application.hpp"
#include "engine/input.hpp"

#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

void keyboardCallback(GLFWwindow* window, int key, int /*scancode*/, int action, int /*mods*/) {
  Input* input = (Input*)glfwGetWindowUserPointer(window);
  
  if (action == GLFW_PRESS) {
    input->setKeyPressed(key);
    return;
  }
  if (action == GLFW_RELEASE) {
    input->setKeyReleased(key);
    return;
  }
}

void mouseButtonCallback(GLFWwindow* window, int button, int action, int /*mods*/) {
  Input* input = (Input*)glfwGetWindowUserPointer(window);
  
  if (action == GLFW_PRESS) {
    input->setMouseButtonPressed(button);
    return;
  }
  if (action == GLFW_RELEASE) {
    input->setMouseButtonReleased(button);
    return;
  }
}

void mousePositionCallback(GLFWwindow* window, double xpos, double ypos) {
  ((Input*)glfwGetWindowUserPointer(window))->setMousePosition(xpos, ypos);
}

Application::Application() : isRunning(false), window(nullptr), m_input() {}
Application::~Application() {}

int Application::init(const char* title, int width, int height, bool resizable) {
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
  
  if (!resizable) {
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
  }

  window = glfwCreateWindow(width, height, title, NULL, NULL);
  if (!window) {
    std::cout << "\e[31mError: Failed to create a window.\e[0m\n";
    return 1;
  }

  // Assign callbacks
  glfwSetWindowUserPointer(window, &m_input);
  glfwSetKeyCallback(window, keyboardCallback);
  glfwSetMouseButtonCallback(window, mouseButtonCallback);
  glfwSetCursorPosCallback(window, mousePositionCallback);
  
  glfwMakeContextCurrent(window);
  if (glewInit() != GLEW_OK) {
    std::cout << "\e[31mError: GLEW is not OK.\e[0m\n";
    glfwDestroyWindow(window);
    return 1;
  }
  
  isRunning = true;

  return 0;
}

void Application::poll() {
  m_input.clear();
  glfwPollEvents();

  if (glfwWindowShouldClose(window)) {
    isRunning = false;
  }
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

const Input& Application::input() const { return m_input; }
bool Application::running() const { return isRunning; }
