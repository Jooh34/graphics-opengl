#include "Sphere.h"

Sphere :: Sphere(jhm::position o, float r, jhm::vector ka, jhm::vector kd, jhm::vector ks, float kn, float reflectivity, float transparency, float n)
 : Object(ka, kd, ks, kn, reflectivity, transparency, n)
{
	this->o = o;
	this->r = r;
}

bool Sphere :: intersect(jhm::position ori, jhm::vector dir, jhm::position &pHit, jhm::vector &pv) {
	jhm::vector dP = o-ori;
	float b = -2 * (dP%dir);
	float c = dP.length()*dP.length() - r*r;
	float discriminator = b * b - 4 * c;
 	if (discriminator < 0)
		return false;

	else {
		float D1 = (-b + sqrt(discriminator))/2;
		float D2 = (-b - sqrt(discriminator))/2;

		if(D2 <= EPS) {
			if(D1 <= EPS) return false;
			else {
				pHit = ori + D1 * dir;
        pv = (pHit-o).normalize();
				return true;
			}
		}
		else {
			pHit = ori + D2 * dir;
      pv = (pHit-o).normalize();
			return true;
		}
	}
}
