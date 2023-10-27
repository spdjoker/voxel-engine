#ifndef JKR_INPUT_HPP
#define JKR_INPUT_HPP

#include <vector>
#include "input_enums.hpp"
#include "jkr/types/vector2.hpp"

class Input {
  std::vector<char> states;
  KeyCode last;

  Vector2f mousePosition;
  Vector2f mouseDelta;

public:
  Input();

  void clear();
  
  // Keyboard Update Methods
  void setKeyPressed(int key);
  void setKeyReleased(int key);

  // Key Related Events
  bool onKey(KeyCode key) const;
  bool onKeyUp(KeyCode key) const;
  bool onKeyDown(KeyCode key) const;
  bool onKeyRepeat(KeyCode key) const;
  
  // Mouse Update Methods
  void setMouseButtonPressed(int key);
  void setMouseButtonReleased(int key);
  void setMousePosition(float xpos, float ypos);

  // Mouse Related Events
  bool onMouseButton(MouseButton key) const;
  bool onMouseButtonUp(MouseButton key) const;
  bool onMouseButtonDown(MouseButton key) const;
  bool onMouseMove() const;
  
  // Getters
  Vector2f getMousePosition() const;
  Vector2f getMouseDelta() const;
};

#endif
