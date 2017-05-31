#include "BSpline_2D.h"

BSpline_2D :: BSpline_2D(CrossSection crossSection, int nPoint)
{
  this->crossSection = crossSection;
  this->nPoint = nPoint;
}

vector<jhm::position> BSpline_2D :: getBSplineCrossSection() {
	vector<jhm::position> curve;
	for(int i=0; i<crossSection.numControlPoint; i++) {
		BSpline(crossSection.controlPointVec.at(i),
		crossSection.controlPointVec.at((i+1)%crossSection.numControlPoint),
		crossSection.controlPointVec.at((i+2)%crossSection.numControlPoint),
		crossSection.controlPointVec.at((i+3)%crossSection.numControlPoint),
		curve);
  }
  return curve;
}

void BSpline_2D :: BSpline(jhm::position P0,
	jhm::position P1,
	jhm::position P2,
	jhm::position P3,
	vector<jhm::position> &curve)
{
	for(int i=0; i<nPoint; i++) {

		float t = (float)i/(nPoint-1);
		float it = 1.0f-t;

		float B0 = it*it*it/6.0f;
		float B1 = (3*t*t*t - 6*t*t +4)/6.0f;
		float B2 = (-3*t*t*t +3*t*t + 3*t + 1)/6.0f;
		float B3 =  t*t*t/6.0f;

		jhm::position p = jhm::position(0,0,0);
		p[0] = B0*P0[0] + B1*P1[0] + B2*P2[0] + B3*P3[0];
		p[1] = B0*P0[1] + B1*P1[1] + B2*P2[1] + B3*P3[1];

		curve.push_back(p);
	}
}
