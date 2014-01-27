#include "Object.h"

Derivative Object::evaluate(double t, double dt, const Derivative &d) {
  State state;
  state.x = s.x + d.dx*dt;
  state.v = s.v + d.dv*dt;
  
  Derivative out;
  out.dx = state.v;
  out.dv = acceleration(state, t+dt);
  return out;
}

Vector2 Object::acceleration(const State &state, double t) {
  const double k = 10;
  const double b = 1;
  return state.x*-k + state.v*-b;
}

void Object::integrate(double t, double dt) {
  Derivative a = evaluate(t, 0.0, Derivative());
  Derivative b = evaluate(t, dt*0.5, a);
  Derivative c = evaluate(t, dt*0.5, b);
  Derivative d = evaluate(t, dt, c);
  
  const Vector2 dxdt = (a.dx + (b.dx + c.dx)*2.0 + d.dx) * (1.0/6.0);
  const Vector2 dvdt = (a.dv + (b.dv + c.dv)*2.0 + d.dv) * (1.0/6.0);
  
  s.x = s.x + dxdt * dt;
  s.v = s.v + dvdt * dt;
}
