#ifndef JKR_INPUT_ENUMS_HPP
#define JKR_INPUT_ENUMS_HPP

enum class MouseButton : int {
  BUTTON_1  = 0,
  BUTTON_2  = 1,
  BUTTON_3  = 2,
  BUTTON_4  = 3,
  BUTTON_5  = 4,
  BUTTON_6  = 5,
  BUTTON_7  = 6,
  BUTTON_8  = 7,

  LEFT      = BUTTON_1,
  RIGHT     = BUTTON_2,
  MIDDLE    = BUTTON_3,

  LAST      = BUTTON_8
};

enum class KeyCode : int {
  UNKNOWN         = -1,

  SPACE           = 32,
  APOSTROPHE      = 39,
  COMMA           = 44,
  MINUS           = 45,
  PERIOD          = 46,
  SLASH           = 47,

  NUM_0           = 48,
  NUM_1           = 49,
  NUM_2           = 50,
  NUM_3           = 51,
  NUM_4           = 52,
  NUM_5           = 53,
  NUM_6           = 54,
  NUM_7           = 55,
  NUM_8           = 56,
  NUM_9           = 57,

  SEMICOLON       = 59,

  A               = 65,
  B               = 66,
  C               = 67,
  D               = 68,
  E               = 69,
  F               = 70,
  G               = 71,
  H               = 72,
  I               = 73,
  J               = 74,
  K               = 75,
  L               = 76,
  M               = 77,
  N               = 78,
  O               = 79,
  P               = 80,
  Q               = 81,
  R               = 82,
  S               = 83,
  T               = 84,
  U               = 85,
  V               = 86,
  W               = 87,
  X               = 88,
  Y               = 89,
  Z               = 90,
  
  LEFT_BRACKET    = 91,
  BACKSLASH       = 92,
  RIGHT_BRACKET   = 93,
  GRAVE_ACCENT    = 96,

  WORLD_1         = 161,
  WORLD_2         = 162,

  ESCAPE          = 256,
  ENTER           = 257,
  TAB             = 258,
  BACKSPACE       = 259,
  INSERT          = 260,
  DELETE          = 261,
  RIGHT           = 262,
  LEFT            = 263,
  DOWN            = 264,
  UP              = 265,
  PAGE_UP         = 266,
  PAGE_DOWN       = 267,
  HOME            = 268,
  END             = 269,

  CAPS_LOCK       = 280,
  SCROLL_LOCK     = 281,
  NUM_LOCK        = 282,
  PRINT_SCREEN    = 283,
  PAUSE           = 284,

  F1              = 290,
  F2              = 291,
  F3              = 292,
  F4              = 293,
  F5              = 294,
  F6              = 295,
  F7              = 296,
  F8              = 297,
  F9              = 298,
  F10             = 299,
  F11             = 300,
  F12             = 301,
  F13             = 302,
  F14             = 303,
  F15             = 304,
  F16             = 305,
  F17             = 306,
  F18             = 307,
  F19             = 308,
  F20             = 309,
  F21             = 310,
  F22             = 311,
  F23             = 312,
  F24             = 313,
  F25             = 314,

  KEYPAD_0        = 320,
  KEYPAD_1        = 321,
  KEYPAD_2        = 322,
  KEYPAD_3        = 323,
  KEYPAD_4        = 324,
  KEYPAD_5        = 325,
  KEYPAD_6        = 326,
  KEYPAD_7        = 327,
  KEYPAD_8        = 328,
  KEYPAD_9        = 329,

  KEYPAD_DECIMAL  = 330,
  KEYPAD_DIVIDE   = 331,
  KEYPAD_MULTIPLY = 332,
  KEYPAD_SUBTRACT = 333,
  KEYPAD_ADD      = 334,
  KEYPAD_ENTER    = 335,
  KEYPAD_EQUAL    = 336,

  LEFT_SHIFT      = 340,
  LEFT_CONTROL    = 341,
  LEFT_ALT        = 342,
  LEFT_SUPER      = 343,
  RIGHT_SHIFT     = 344,
  RIGHT_CONTROL   = 345,
  RIGHT_ALT       = 346,
  RIGHT_SUPER     = 347,

  MENU            = 348,

  LAST            = MENU
};

#endif
