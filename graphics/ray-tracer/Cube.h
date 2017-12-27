#ifndef CUBE_H
#define CUBE_H

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/freeglut.h>
#include <vector>
#include "mathclass/include/mathclass.h"
#include "Material.h"

class Cube
{
public:
  static void draw(float x, float y, float z);
};

#endif
