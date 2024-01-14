#ifndef JKR_TYPES_VECTOR_2_INT_HPP
#define JKR_TYPES_VECTOR_2_INT_HPP

class Vector2i {
  int data[2];
public:
  Vector2i();
  Vector2i(int x, int y);
  Vector2i(const Vector2i& other);

  int getX() const;
  void setX(int value);

  int getY() const;
  void setY(int value);
  
  void set(int x, int y);

  double magnitude() const;
  int sqrMagnitude() const;
  
  Vector2i& operator=(const Vector2i& other);
  bool operator==(const Vector2i& other) const;
  bool operator!=(const Vector2i& other) const;

  void print() const;

  static Vector2i Zero;
  static Vector2i One;
  static Vector2i Up;
  static Vector2i Down;
  static Vector2i Left;
  static Vector2i Right;
};

#endif
