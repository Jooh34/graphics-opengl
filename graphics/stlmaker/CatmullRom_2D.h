#ifndef CATMULLROM_2D_H
#define CATMULLROM_2D_H

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/freeglut.h>
#include <vector>
#include "mathclass/include/mathclass.h"
#include "CrossSection.h"

class CatmullRom_2D
{
public:
  int nPoint;
  float alpha;

  CatmullRom_2D (int nPoint, float alpha);
  vector<jhm::position> getCatmullRomCrossSection(CrossSection crossSection);
  jhm::position addPos(jhm::position p1, jhm::position p2);
  float tj(float ti, jhm::position Pi, jhm::position Pj);
  void catmullRomSpline(jhm::position P0, jhm::position P1, jhm::position P2,
  	jhm::position P3, vector<jhm::position> &curve);
};

#endif
