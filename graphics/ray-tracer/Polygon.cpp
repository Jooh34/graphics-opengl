#include "Polygon.h"

Polygon :: Polygon(){}

Polygon :: Polygon(jhm::position p1, jhm::position p2, jhm::position p3, jhm::vector ka, jhm::vector kd, jhm::vector ks, float kn,
   float reflectivity, float transparency, float n, Texture* texture)
 : Object(ka, kd, ks, kn, reflectivity, transparency, n, texture)
{
	this->p1 = p1;
	this->p2 = p2;
  this->p3 = p3;

  N = ((p2-p1)*(p3-p1)).normalize();
}

jhm::position Polygon :: addPos(jhm::position a, jhm::position b) {
  return jhm::position(a[0]+b[0], a[1]+b[1], a[2]+b[2]);
}

bool Polygon :: intersect(jhm::position ori, jhm::vector dir, jhm::position &pHit, jhm::vector &pv) {
  jhm::vector e1,e2,h,s,q;
  float a,f,u,v;

  e1 = p2-p1;
  e2 = p3-p1;

  h = dir*e2;
  a = e1%h;
  if (abs(a) <EPSILON) return false;

  f = 1/a;
  s = ori-p1;
  u = f * (s%h);

  if (u < 0.0 || u > 1.0) return false;

  q = s*e1;
  v = f*(dir%q);

  if (v < 0.0f || v + u > 1.0) return false;

  float t = f* (e2%q);

  if(t>EPSILON) {
    jhm::position temp = addPos(addPos(p1*(1-u-v), p2*u), p3*v);
    pHit = temp;
    if(N%dir > 0) pv = -N;
    else pv = N;
    return true;
  }
  else return false;
}

jhm::vector Polygon :: getTextureColor(jhm::position pHit) {
  jhm::vector w_vec = p1-p2;
  jhm::vector h_vec = p3-p2;

  jhm::vector P = pHit-p2;
  float l = P.length();

  float cos_w = (P%w_vec)/(l*w_vec.length());
  float cos_h = (P%h_vec)/(l*h_vec.length());

  float u = (l * cos_w) / w_vec.length();
  float v = (l * cos_h) / h_vec.length();

  return texture->getTextureColor(u,v);
}
