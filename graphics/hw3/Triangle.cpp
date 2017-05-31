#include "Triangle.h"

Triangle :: Triangle (
  jhm::position p1,
  jhm::position p2,
  jhm::position p3,
  jhm::vector v1,
  jhm::vector v2,
  jhm::vector v3
)
{
  this->p1 = p1;
  this->p2 = p2;
  this->p3 = p3;
  this->v1 = v1;
  this->v2 = v2;
  this->v3 = v3;
}
