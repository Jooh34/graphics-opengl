#ifndef TRIANGLE_H
#define TRIANGLE_H
#pragma once

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/freeglut.h>
#include <vector>
#include "mathclass/include/mathclass.h"

class Triangle
{
public:
  jhm::position p[3];
  jhm::vector v[3];
  float color[4];

  jhm::vector a;
  float b;

  Triangle();
  Triangle(
    jhm::position p1,
    jhm::position p2,
    jhm::position p3,
    jhm::vector v1,
    jhm::vector v2,
    jhm::vector v3,
    GLfloat R,
    GLfloat G,
    GLfloat B,
    GLfloat alpha
  );

  float getArea();
  float getPlane(jhm::position x);
  void draw();
  float getDistance(jhm::position x);
};

#endif
