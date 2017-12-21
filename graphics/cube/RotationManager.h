#ifndef ROTATIONMANAGER_H
#define ROTATIONMANAGER_H

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/freeglut.h>
#include <vector>
#include "mathclass/include/mathclass.h"

#include "EdgePiece.h"
#include "CornerPiece.h"
#include "CenterPiece.h"

using namespace std;

class RotationManager
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

  // Rotation Dir //
  const static int U_ = 0;
  const static int U_i = 1;
  const static int F_ = 2;
  const static int F_i = 3;
  const static int R_ = 4;
  const static int R_i = 5;
  const static int B_ = 6;
  const static int B_i = 7;
  const static int L_ = 8;
  const static int L_i = 9;
  const static int D_ = 10;
  const static int D_i = 11;

  vector<EdgePiece>& EP_list;
  vector<CornerPiece>& CP_list;
  vector<CenterPiece>& TP_list;

  int timer;
  bool rotating;
  int dir;

  RotationManager(vector<EdgePiece>& EP_list, vector<CornerPiece>& CP_list, vector<CenterPiece>& TP_list);
  void setRotate(int dir);
  void rotate();
  void rotate_U();
  void rotate_Ui();
  void rotate_D();
  void rotate_Di();
  void rotate_R();
  void rotate_Ri();
  void rotate_L();
  void rotate_Li();
  void rotate_F();
  void rotate_Fi();
  void rotate_B();
  void rotate_Bi();
};

#endif
