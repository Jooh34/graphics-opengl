#ifndef OBJPARSER_H
#define OBJPARSER_H
#pragma once

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/freeglut.h>
#include <vector>
#include "mathclass/include/mathclass.h"
#include <fstream>
#include <sstream>
#include "Triangle.h"
#include "BSPtree.h"

using namespace std;

class ObjParser {
public:
  ObjParser(const char* filename, jhm::vector translation, float scale, BSPtree &tree);
};

#endif
