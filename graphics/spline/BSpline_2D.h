#ifndef BSPLINE_2D_H
#define BSPLINE_2D_H

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/freeglut.h>
#include <vector>
#include "mathclass/include/mathclass.h"
#include "CrossSection.h"

class BSpline_2D
{
public:
  CrossSection crossSection;
  int nPoint;

  BSpline_2D(CrossSection crossSection, int nPoint);
  vector<jhm::position> getBSplineCrossSection();
  void BSpline(jhm::position P0,
  	jhm::position P1,
  	jhm::position P2,
  	jhm::position P3,
  	vector<jhm::position> &curve);
};

#endif
