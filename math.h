#ifndef MATH_H
#define MATH_H


struct Vector3f {
  float x;
  float y;
  float z;

  Vector3f(){}

  Vector3f(float _x,float _y,float _z){
    x = _x;
    y = _y;
    z = _z;
  }
  
};
#endif 
