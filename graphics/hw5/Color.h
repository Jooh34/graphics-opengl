#ifndef COLOR_H
#define COLOR_H
#pragma once

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/freeglut.h>
#include <vector>
#include "mathclass/include/mathclass.h"

class Color
{
public:
  float R;
  float G;
  float B;

  Color();
  Color(float R, float G, float B);
  Color operator+(const Color& c);

};

#endif
