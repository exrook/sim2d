#include <iostream>
#include <csetjmp>
#include "lua.hpp"
#include "Object.h"

void config();


jmp_buf env;
int val;
double cfg[6] = {30,0.1,100,0,200,0};

int main(int argc, char** argv) {
  config();
  Object mine{{{cfg[2],cfg[3]},{cfg[4],cfg[5]}}};
  double rounds=cfg[0],step=cfg[1];

  //std::cout << 0 << ": (" << mine.x().x << ", " << mine.x().y << ")" << std::endl;
  std::cout << 0 << "," << mine.x().x << "," << mine.x().y << std::endl;
  for (double i=0+step; i<rounds*step; i+=step) {
    mine.integrate(i,step);
    //std::cout << i << ": (" << mine.x().x << ", " << mine.x().y << ")" << std::endl;
    std::cout << i << "," << mine.x().x << "," << mine.x().y << std::endl;
  }
  return 0;
}

int error(lua_State *L) {
  longjmp(env, val);
}

void config() {
  lua_State *L = luaL_newstate();
  val = setjmp(env);
  if(val) {
    lua_close(L);
    return;
  }
  lua_atpanic(L, error);
  lua_newtable(L);
  lua_setglobal(L, "config");
  luaL_dofile(L, "config.lua");
  lua_settop(L,0);
  lua_getglobal(L, "config");
  lua_getfield(L,1,"rounds");
  lua_getfield(L,1,"step");
  lua_getfield(L,1,"x");
  lua_getfield(L,1,"y");
  lua_getfield(L,1,"vx");
  lua_getfield(L,1,"vy");
  
  for(int i=2;i<=7;i++)
    cfg[i-2] = (double)lua_tonumber(L,i);
  lua_close(L);
  return;
}
