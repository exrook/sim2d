#ifndef _OBJECT_H_
#define _OBJECT_H_

#include "State.h"
#include "Derivative.h"

class Object {
  State s;
  Derivative evaluate(double t, double dt, const Derivative &d);
  Vector2 acceleration(const State &state, double t);
  public:
    Object(State sd): s(sd) {};
    void integrate(double t, double dt);
    Vector2 x() {return s.x;};
    Vector2 v() {return s.v;};
};

#endif
