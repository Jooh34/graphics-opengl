#ifndef POLYGON_H
#define POLYGON_H
#pragma once

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/freeglut.h>
#include <vector>
#include "mathclass/include/mathclass.h"
#include "Object.h"
#include "Triangle.h"
#include <stdio.h>
#include "Texture.h"

#define EPS 0.01f

class Polygon : public Object
{
public:
  jhm::position p1;
  jhm::position p2;
  jhm::position p3;

  jhm::vector N;
  
  Polygon();
	Polygon(jhm::position p1, jhm::position p2, jhm::position p3, jhm::vector ka, jhm::vector kd, jhm::vector ks, float kn,
     float reflectivity, float transparency, float n, Texture* texture = NULL);
  jhm::position addPos(jhm::position a, jhm::position b);
	bool intersect(jhm::position ori, jhm::vector dir, jhm::position &pHit, jhm::vector &pv);
  jhm::vector getTextureColor(jhm::position pHit);
};

#endif
