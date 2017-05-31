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
  jhm::position p1;
  jhm::position p2;
  jhm::position p3;
  jhm::vector v1;
  jhm::vector v2;
  jhm::vector v3;

  Triangle(
    jhm::position p1,
    jhm::position p2,
    jhm::position p3,
    jhm::vector v1,
    jhm::vector v2,
    jhm::vector v3
  )
};

#endif
