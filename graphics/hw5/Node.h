#ifndef NODE_H
#define NODE_H
#pragma once

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/freeglut.h>
#include <vector>
#include "mathclass/include/mathclass.h"
#include "Triangle.h"
#include <stdio.h>

class Node
{
public:
  Node* left;
  std::vector<Triangle> middle;
  Node* right;

  std::vector<Triangle> triangles;

  Node(std::vector<Triangle> triangles);
  Triangle findBiggestTriangle();
  void split();
  void discriminate(
    Triangle spliter,
    Triangle triangle,
    std::vector<Triangle> &l,
    std::vector<Triangle> &r
  );

  void traversal(jhm::position eye);
  void findFirstIntersection(jhm::position ori, jhm::vector vec, Triangle &triangle, jhm::position &intersection, jhm::vector &pv, bool &find);
};

#endif
