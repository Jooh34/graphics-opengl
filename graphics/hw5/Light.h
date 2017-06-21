#ifndef LIGHT_H
#define LIGHT_H

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/freeglut.h>
#include <vector>
#include "mathclass/include/mathclass.h"

class Light
{
public:
  GLfloat AmbientLightValue[4];
	GLfloat DiffuseLightValue[4];
	GLfloat SpecularLightValue[4];
	GLfloat PositionLightValue[4];

  void initLight();
};

#endif
