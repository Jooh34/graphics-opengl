#include "Triangle.h"

Triangle :: Triangle (){}

Triangle :: Triangle (
  jhm::position p1,
  jhm::position p2,
  jhm::position p3,
  jhm::vector v1,
  jhm::vector v2,
  jhm::vector v3,
  GLfloat R,
  GLfloat G,
  GLfloat B,
  GLfloat alpha
)
{
  this->p[0] = p1;
  this->p[1] = p2;
  this->p[2] = p3;
  this->v[0] = v1;
  this->v[1] = v2;
  this->v[2] = v3;

  this->color[0] = R;
  this->color[1] = G;
  this->color[2] = B;
  this->color[3] = alpha;

  jhm::vector t1 = p[1]-p[0];
  jhm::vector t2 = p[2]-p[0];
  a = t1 * t2;
  a.normalize();
  b = -(a%p1);
}

float Triangle :: getArea() {
  jhm::vector temp = (p[1]-p[0]) * (p[2]-p[0]);
  return temp.length()/2;
}

float Triangle :: getPlane(jhm::position x) {
  return (a%x) + b;
}

void Triangle :: draw() {
  glBegin(GL_TRIANGLES);
  glColor4f(color[0], color[1], color[2], color[3]);

  glNormal3f(v[0][0], v[0][1], v[0][2]);
  glVertex3f(p[0][0], p[0][1], p[0][2]);

  glNormal3f(v[1][0], v[1][1], v[1][2]);
  glVertex3f(p[1][0], p[1][1], p[1][2]);

  glNormal3f(v[2][0], v[2][1], v[2][2]);
  glVertex3f(p[2][0], p[2][1], p[2][2]);

  glEnd();
}

float Triangle :: getDistance(jhm::position x) {
  float d = abs((a%x)+b / a.length());
  if(d ==0) d = 0.01; // approximate to 0
  return d;
}
