#ifndef TEXTURE_H
#define TEXTURE_H
#pragma once

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/freeglut.h>
#include <vector>
#include "mathclass/include/mathclass.h"
#include <stdio.h>
#include <stdlib.h>

using namespace std;

class Texture
{
public:
  int w;
  int h;

  Texture(const char* filename);
};

#endif
