#include "CatmullRom_2D.h"

CatmullRom_2D :: CatmullRom_2D (int nPoint, float alpha)
{
  this->nPoint = nPoint;
  this->alpha = alpha;
}

vector<jhm::position> CatmullRom_2D :: getCatmullRomCrossSection(CrossSection crossSection)
{
	vector<jhm::position> curve;
	for(int i=0; i<crossSection.numControlPoint; i++) {
		catmullRomSpline(crossSection.controlPointVec.at(i),
		crossSection.controlPointVec.at((i+1)%crossSection.numControlPoint),
		crossSection.controlPointVec.at((i+2)%crossSection.numControlPoint),
		crossSection.controlPointVec.at((i+3)%crossSection.numControlPoint),
		curve);
  }

  return curve;
}

jhm::position CatmullRom_2D :: addPos(jhm::position p1, jhm::position p2) {
	return jhm::position(p1[0]+p2[0], p1[1]+p2[1], p1[2]+p2[2]);
}

float CatmullRom_2D :: tj(float ti, jhm::position Pi, jhm::position Pj) {
	return pow(pow(pow(Pj[0]-Pi[0], 2.0) + pow(Pj[1]-Pi[1], 2.0) + pow(Pj[2]-Pi[2],2.0), 0.5), alpha) + ti;
}

void CatmullRom_2D :: catmullRomSpline(jhm::position P0, jhm::position P1, jhm::position P2,
	jhm::position P3, vector<jhm::position> &curve) {

	float t0 = 0;
	float t1 = tj(t0, P0, P1);
	float t2 = tj(t1, P1, P2);
	float t3 = tj(t2, P2, P3);

	float t = t1;

	for (int i = 0; i < nPoint; i++) {

		jhm::position A1 = addPos(P0*((t1-t)/(t1-t0)), P1*((t-t0)/(t1-t0)));
	  jhm::position A2 = addPos(P1*((t2-t)/(t2-t1)), P2*((t-t1)/(t2-t1)));
	  jhm::position A3 = addPos(P2*((t3-t)/(t3-t2)), P3*((t-t2)/(t3-t2)));

		jhm::position B1 = addPos(A1*((t2-t)/(t2-t0)), A2*((t-t0)/(t2-t0)));
	  jhm::position B2 = addPos(A2*((t3-t)/(t3-t1)), A3*((t-t1)/(t3-t1)));

	  jhm::position C  = addPos(B1*((t2-t)/(t2-t1)), B2*((t-t1)/(t2-t1)));

		curve.push_back(C);

		t = t + ((t2-t1)/nPoint);
	}
}
