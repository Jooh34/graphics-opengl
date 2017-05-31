#ifndef CROSSSECTION_H
#define CROSSSECTION_H
#pragma once

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/freeglut.h>
#include <vector>
#include "mathclass/include/mathclass.h"

using namespace std;

class CrossSection
{
public:
  int numControlPoint;
  vector<jhm::position> controlPointVec;
  float scale;
	float angle;
  float axis[3];
  float position[3];

  CrossSection();
  CrossSection(vector<jhm::position> controlPointVec,
    int numControlPoint,
  	float scale,
  	float angle,
  	float axis[3],
  	float position[3]
  );
};

#endif
