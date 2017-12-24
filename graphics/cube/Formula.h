#ifndef FORMULA_H
#define FORMULA_H
#pragma once

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/freeglut.h>
#include <vector>
#include <cmath>
#include "mathclass/include/mathclass.h"

using namespace std;

class Formula
{
public:
  const static int U = 0;
  const static int Ui = 1;
  const static int F = 2;
  const static int Fi = 3;
  const static int R = 4;
  const static int Ri = 5;
  const static int B = 6;
  const static int Bi = 7;
  const static int L = 8;
  const static int Li = 9;
  const static int D = 10;
  const static int Di = 11;

  static const int cubeincube[18];
  static const int cubeincubeincube[20];
  static const int exchangedpeak[19];
  static const int spiralpattern[18];
  static const int cross[20];


  static const int* showManual(int &size);
};

#endif
