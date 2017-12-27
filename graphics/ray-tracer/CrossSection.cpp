#include "CrossSection.h"

using namespace std;

CrossSection :: CrossSection(){}

CrossSection :: CrossSection(vector<jhm::position> controlPointVec,
	int numControlPoint,
	float scale,
	float angle,
	float axis[3],
	float position[3]
) {
	this-> controlPointVec = controlPointVec;
	this-> numControlPoint = numControlPoint;
	this-> scale = scale;
	this-> angle = angle;
	for(int i = 0; i<3; i++) {
		this-> axis[i] = axis[i];
	}
	for(int i = 0; i<3; i++) {
		this-> position[i] = position[i];
	}
};
