#include "Application.hpp"

#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

Application::Application() : isRunning(false), window(nullptr) {}
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
  glfwPollEvents();

  if (glfwWindowShouldClose(window)) {
    isRunning = false;
  }
}

void Application::update() {
}

void Application::render() {
  glfwSwapBuffers(window);
}

void Application::clean() {
  std::cout << "Cleaned\n";
  if (window) {
    glfwDestroyWindow(window);
  }
}

bool Application::running() const { return isRunning; }
