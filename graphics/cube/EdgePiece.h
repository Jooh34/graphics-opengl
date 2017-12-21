#ifndef EDGEPIECE_H
#define EDGEPIECE_H
#pragma once

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/freeglut.h>
#include <vector>
#include "mathclass/include/mathclass.h"

#include "Piece.h"

class EdgePiece : public Piece
{
public:

  // Edge Location //
  const static int UF = 0;
  const static int UR = 1;
  const static int UB = 2;
  const static int UL = 3;
  const static int FR = 4;
  const static int BR = 5;
  const static int BL = 6;
  const static int FL = 7;
  const static int DF = 8;
  const static int DR = 9;
  const static int DB = 10;
  const static int DL = 11;
  //

  int loc;
  int c1;
  int c2;

  EdgePiece(int loc, int c1, int c2, float size);
  void draw();

  void locRefresh(int index);
};

#endif
