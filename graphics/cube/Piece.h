#ifndef PIECE_H
#define PIECE_H
#pragma once

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/freeglut.h>
#include <vector>
#include <cmath>
#include "mathclass/include/mathclass.h"

class Piece
{
public:

  // const vars for color
  const static int M = 0;
  const static int W = 1;
  const static int Y = 2;
  const static int B = 3;
  const static int R = 4;
  const static int G = 5;
  const static int O = 6;

  std::vector<jhm::position> vtx_list;
  float size;

  int rot_nine;

  Piece(float size);
  void setColor(int c);
  void getVertexList(float x, float y, float z, float size);
  void rotateVertexList_U();
  void rotateVertexList_Ui();
  void rotateVertexList_R();
  void rotateVertexList_Ri();
  void draw();

  void rotate_X();
  void rotate_Xi();
  void rotate_Y();
  void rotate_Yi();
  void rotate_Z();
  void rotate_Zi();

  virtual void locRefresh(int index) = 0;
};

#endif
