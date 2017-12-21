#ifndef CORNERPIECE_H
#define CORNERPIECE_H
#pragma once

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/freeglut.h>
#include <vector>
#include "mathclass/include/mathclass.h"

#include "Piece.h"

class CornerPiece : public Piece
{
public:

  // Corner location //
  const static int UFL = 0;
  const static int UFR = 1;
  const static int UBR = 2;
  const static int UBL = 3;
  const static int DFL = 4;
  const static int DFR = 5;
  const static int DBR = 6;
  const static int DBL = 7;
  //

  int loc;
  int c1;
  int c2;
  int c3;

  CornerPiece(int loc, int c1, int c2, int c3, float size);
  void draw();

  void locRefresh(int index);
};

#endif
