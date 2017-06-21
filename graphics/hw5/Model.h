#ifndef MODEL_H
#define MODEL_H
#pragma once

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/freeglut.h>
#include <vector>
#include "mathclass/include/mathclass.h"
#include <fstream>
#include <sstream>
#include "CrossSection.h"
#include "BSpline_2D.h"
#include "CatmullRom_2D.h"
#include "TransformManager.h"
#include "Triangle.h"
#include "BSPtree.h"
#include "Object.h"

class Model : public Object
{
public:
  int curveType;
  // 0.Bspline
  // 1.Catmull_Rom
  int numCrossSection;
  int numControlPoint;
  vector<CrossSection> crossSectionVec;

  int nPoint;
  float alpha;

  BSPtree tree;

  Model(std::string fileName, int nPoint, int alpha, jhm::vector ka, jhm::vector kd, jhm::vector ks, float kn, float reflectivity, float transparency, float n);
  void setNumPoint(int nPoint);
  void setAlpha(float alpha);

  vector<jhm::position> getCrossSection(int c_i);
  vector<vector<jhm::position> > getAllCrossSection();
  vector<jhm::position> reflectCrossSection(
  	vector<jhm::position> C1,
  	vector<jhm::position> C2
  );

  void fillCrossSection(int c_i,
    GLfloat R, GLfloat G, GLfloat B, GLfloat alpha);
  void drawAllCrossSection(float lineWidth,
    GLfloat R, GLfloat G, GLfloat B);
  void drawSurfaceBetweenCrossSection (
    vector<jhm::position> C1,
  	vector<jhm::position> C2,
  	vector<jhm::position> C3,
  	vector<jhm::position> C4,
  	GLfloat R,
  	GLfloat G,
  	GLfloat B,
    GLfloat alpha);
  void drawSurface(GLfloat R, GLfloat G, GLfloat B, GLfloat alpha);
  void drawSurface_stripe(
    GLfloat R1, GLfloat G1, GLfloat B1, GLfloat alpha1,
  	GLfloat R2, GLfloat G2, GLfloat B2, GLfloat alpha2
  );

  void stack_Surface(
    GLfloat R,
    GLfloat G,
    GLfloat B,
    GLfloat alpha
  );
  void stack_Surface_stripe(
    GLfloat R1, GLfloat G1, GLfloat B1, GLfloat alpha1,
  	GLfloat R2, GLfloat G2, GLfloat B2, GLfloat alpha2
  );

  void stack_SurfaceBetweenCrossSection (
    vector<jhm::position> C1,
  	vector<jhm::position> C2,
  	vector<jhm::position> C3,
  	vector<jhm::position> C4,
  	GLfloat R,
  	GLfloat G,
  	GLfloat B,
    GLfloat alpha
  );

  void draw_BSPdepthOrder(jhm::position eye);
  bool intersect(jhm::position ori, jhm::vector dir, jhm::position &pHit, jhm::vector &pv);
};

#endif
