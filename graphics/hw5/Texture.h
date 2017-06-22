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
#include "EasyBMP.h"

using namespace std;

class Texture
{
public:
  int width;
  int height;

  BMP bmp;

  Texture(const char* filename);
  ~Texture();
  jhm::vector getTextureColor(float u, float v);
};

#endif
