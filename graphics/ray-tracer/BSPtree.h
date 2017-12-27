#ifndef BSPTREE_H
#define BSPTREE_H
#pragma once

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/freeglut.h>
#include <vector>
#include "mathclass/include/mathclass.h"
#include "Triangle.h"
#include "Node.h"

class BSPtree
{
public:
  std::vector<Triangle> triangles;
  Node* root;

  BSPtree();
  void add(Triangle t);
  void buildBSPtree();
  void traversal(jhm::position eye);
  void findFirstIntersection(jhm::position ori, jhm::vector vec, Triangle* &triangle, jhm::position* &intersection);
};

#endif
