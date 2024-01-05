#ifndef JKR_INPUT_HPP
#define JKR_INPUT_HPP

#include <vector>
#include "jkr/types/common.hpp"
#include "input_enums.hpp"

class Input {
  std::vector<char> states;
  KeyCode last;

  ivec2 mousePosition;
  vec2 mouseDelta;

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
  vec2 getMousePosition() const;
  vec2 getMouseDelta() const;
};

#endif
