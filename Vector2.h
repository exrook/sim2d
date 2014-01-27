#ifndef _Vector2_H_
#define _Vector2_H_

struct Vector2 {
  double x,y;
  
  Vector2 operator+(const Vector2 &v2) const {
    Vector2 out;
    out.x = x + v2.x;
    out.y = y + v2.y;
    return out;
  }
  Vector2 operator*(double s2) const {
    Vector2 out;
    out.x = x*s2;
    out.y = y*s2;
    return out;
  }
};

#endif
