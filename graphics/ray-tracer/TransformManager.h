#ifndef TRANSFORMMANAGER_H
#define TRANSFORMMANAGER_H
#pragma once

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/freeglut.h>
#include <vector>
#include "mathclass/include/mathclass.h"

using namespace std;

class TransformManager
{
public:
  static vector<jhm::position> scailing(float scale, vector<jhm::position> curve);
  static vector<jhm::position> multQuater(float angle, float axis[3], vector<jhm::position> curve);
  static vector<jhm::position> translation(float position[3], vector<jhm::position> curve);
};

#endif
