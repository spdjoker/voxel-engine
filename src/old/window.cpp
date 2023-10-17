#include "Window.hpp"

#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

Window::Window(void* window) : glfwWindow(window) {}
Window::~Window() {
  if (glfwWindow) {
    glfwDestroyWindow((GLFWwindow*)glfwWindow);
  }
}

Window* Window::Create(const char *title, int width, int height, bool resizable) {
  if (!glfwInit()) {
    std::cout << "\e[31mError: GLFW failed to initialize.\e[0m\n";
    return nullptr;
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  
  if (resizable) {
    glfwWindowHint(GLFW_RESIZABLE, GLFW_RESIZABLE);
  }

  GLFWwindow* window = glfwCreateWindow(width, height, title, NULL, NULL);
  if (!window) {
    std::cout << "\e[31mError: Failed to create a window.\e[0m\n";
    return nullptr;
  }

  // Assign callbacks
  
  glfwMakeContextCurrent(window);
  if (glewInit() != GLEW_OK) {
    std::cout << "\e[31mError: GLEW is not OK.\e[0m\n";
    glfwDestroyWindow(window);
    return nullptr;
  }

  return new Window(window);
}

void Window::PollEvents() { glfwPollEvents(); }
void Window::SwapBuffers() { glfwSwapBuffers((GLFWwindow*)glfwWindow); }
bool Window::closing() const { return glfwWindowShouldClose((GLFWwindow*)glfwWindow); }
