#ifndef OBJECT_H
#define OBJECT_H
#pragma once

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/freeglut.h>
#include <vector>
#include "mathclass/include/mathclass.h"

class Object
{
public:
  jhm::vector ka;
	jhm::vector kd;
	jhm::vector ks;
	float kn;
	float reflectivity;
	float transparency;
  float n;

	Object(jhm::vector ka, jhm::vector kd, jhm::vector ks, float kn, float reflectivity, float transparency, float n);

  virtual bool intersect(jhm::position ori, jhm::vector dir, jhm::position &pHit, jhm::vector &pv) = 0;
};

#endif
