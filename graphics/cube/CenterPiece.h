#ifndef CENTERPIECE_H
#define CENTERPIECE_H
#pragma once

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/freeglut.h>
#include <vector>
#include "mathclass/include/mathclass.h"

#include "Piece.h"

class CenterPiece : public Piece
{
public:

  // Center location //
  const static int U = 0;
  const static int F = 1;
  const static int R = 2;
  const static int L = 3;
  const static int B = 4;
  const static int D = 5;
  //

  int loc;
  int c1;

  CenterPiece(int loc, int c1, float size);
  void draw();

  void locRefresh(int index);
};

#endif
