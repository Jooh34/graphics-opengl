#include "Object.h"

Object :: Object(){}
Object :: Object(jhm::vector ka, jhm::vector kd, jhm::vector ks, float kn,
  float reflectivity, float transparency, float n, Texture* texture)
{
  this->ka = ka;
  this->kd = kd;
  this->ks = ks;
  this->kn = kn;
  this->reflectivity = reflectivity;
  this->transparency = transparency;
  this->n = n;
  this->texture = texture;
}
