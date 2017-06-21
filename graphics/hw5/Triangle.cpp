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

  this->pv = a;
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

jhm::position Triangle :: addPos(jhm::position a, jhm::position b) {
  return jhm::position(a[0]+b[0], a[1]+b[1], a[2]+b[2]);
}

bool Triangle :: hasIntersection(jhm::position ori, jhm::vector dir, jhm::position &intersection)
{
  // printf("v1 : (%lf,%lf,%lf)\n", p[0][0], p[0][1], p[0][2]);
  // printf("v2 : (%lf,%lf,%lf)\n", p[1][0], p[1][1], p[1][2]);
  // printf("v3 : (%lf,%lf,%lf)\n", p[2][0], p[2][1], p[2][2]);
  // printf("ori : (%lf,%lf,%lf) dir : (%lf,%lf,%lf)\n", ori[0],ori[1],ori[2], dir[0],dir[1],dir[2]);
  jhm::vector e1,e2,h,s,q;
  float a,f,u,v;

  e1 = p[1]-p[0];
  e2 = p[2]-p[0];

  h = dir*e2;
  a = e1%h;
  if (abs(a) <EPSILON) return false;

  f = 1/a;
  s = ori-p[0];
  u = f * (s%h);

  if (u < 0.0 || u > 1.0) return false;

  q = s*e1;
  v = f*(dir%q);

  if (v < 0.0f || v + u > 1.0) return false;

  float t = f* (e2%q);

  if(t>EPSILON) {
    jhm::position temp = addPos(addPos(p[0]*(1-u-v), p[1]*u), p[2]*v);
    intersection = temp;
    return true;
  }
  else return false;
}
