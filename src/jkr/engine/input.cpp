#include "input.hpp"
#include "GLFW/glfw3.h"
#include <iostream>

constexpr char SET_PRESSED = 1;
constexpr char SET_RELEASED = ~SET_PRESSED;
constexpr char STATE_BITS = 3;
constexpr char STATE_PRESSED = 1;
constexpr char STATE_RELEASED = 2;
constexpr char STATE_REPEATING = 0xFF;

Input::Input() : states((int)KeyCode::LAST + 1, 0) {}

void Input::clear() {
  for (unsigned int i = 0; i < states.size(); i++) {
    states[i] = (states[i] << 1) | (states[i] & 1);
  }
  mouseDelta.set(0,0);
}

void Input::setKeyPressed(int key) {
  states[key] = states[key] | SET_PRESSED;
  last = (KeyCode)key;
}

void Input::setKeyReleased(int key) {
  states[key] = states[key] & SET_RELEASED;
  if ((int)last == key) {
    last = KeyCode::UNKNOWN;
  }
}

void Input::setMouseButtonPressed(int button) {
  states[button] = states[button] | SET_PRESSED;
}

void Input::setMouseButtonReleased(int button) {
  states[button] = states[button] & SET_RELEASED;
}

void Input::setMousePosition(float xpos, float ypos) {
  mouseDelta.set(xpos - mousePosition.getX(), ypos - mousePosition.getY());
  mousePosition.set(xpos, ypos);
}

bool Input::onKey(KeyCode key) const {
  return states[(int)key] & STATE_PRESSED;
}

bool Input::onKeyUp(KeyCode key) const {
  return (states[(int)key] & STATE_BITS) == STATE_RELEASED;
}

bool Input::onKeyDown(KeyCode key) const {
  return (states[(int)key] & STATE_BITS) == STATE_PRESSED;
}

bool Input::onKeyRepeat(KeyCode key) const {
  return key == last && states[(int)key] == STATE_REPEATING;
}

bool Input::onMouseButton(MouseButton button) const {
  return states[(int)button] & STATE_PRESSED;
}

bool Input::onMouseButtonUp(MouseButton button) const {
  return (states[(int)button] & STATE_BITS) == STATE_RELEASED;
}

bool Input::onMouseButtonDown(MouseButton button) const {
  return (states[(int)button] & STATE_BITS) == STATE_PRESSED;
}

bool Input::onMouseMove() const {
  return mouseDelta.getX() != 0 || mouseDelta.getY() != 0;
}

Vector2f Input::getMousePosition() const {
  return mousePosition;
}

Vector2f Input::getMouseDelta() const {
  return mouseDelta;
}
