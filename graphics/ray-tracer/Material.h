#ifndef MATERIAL_H
#define MATERIAL_H
#pragma once

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/freeglut.h>
#include <vector>
#include "mathclass/include/mathclass.h"

class Material
{
public:
  static void onEmerald();
  static void onRuby();
  static void onGold();
  static void onBronze();
  static void onPearl();
  static void onGreenPlastic();
  static void on(
    float ambient[],
    float diffuse[],
    float specular[],
    float shininess
  );
};

#endif
