#ifndef JKR_INPUT_HPP
#define JKR_INPUT_HPP

#include <vector>
#include "input_enums.hpp"
#include "jkr/types/vector2i.hpp"

class Input {
  std::vector<char> states;
  KeyCode last;

  Vector2i mousePosition;
  Vector2i mouseDelta;

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
  void setMousePosition(int xpos, int ypos);

  // Mouse Related Events
  bool onMouseButton(MouseButton key) const;
  bool onMouseButtonUp(MouseButton key) const;
  bool onMouseButtonDown(MouseButton key) const;
  bool onMouseMove() const;
  
  // Getters
  Vector2i getMousePosition() const;
  Vector2i getMouseDelta() const;
};

#endif
