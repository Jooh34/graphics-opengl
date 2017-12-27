#include "TransformManager.h"

float angle;
float axis[3];
float position[3];

vector<jhm::position> TransformManager :: scailing(float scale, vector<jhm::position> curve) {
	vector<jhm::position> curve_scailed;

	for(int i=0; i<curve.size(); i++) {
		jhm::position pos = jhm::position(curve.at(i)[0]*scale,
		curve.at(i)[1]*scale,
		curve.at(i)[2]*scale);

		curve_scailed.push_back(pos);
	}
	return curve_scailed;
}

vector<jhm::position> TransformManager :: multQuater(float angle, float axis[3], vector<jhm::position> curve) {
	vector<jhm::position> curve_rotated;

	for(int i = 0; i<curve.size(); i++) {
		jhm::position pos = curve.at(i);

		jhm::quater q(cos(0.5*angle),
		axis[0]*sin(0.5*angle),
		axis[1]*sin(0.5*angle),
		axis[2]*sin(0.5*angle));

		jhm::position new_pos = rotate(q, pos);
		curve_rotated.push_back(new_pos);
	}
	return curve_rotated;
}

vector<jhm::position> TransformManager :: translation(float position[3], vector<jhm::position> curve) {
	vector<jhm::position> curve_translated;

	for(int i=0; i<curve.size(); i++) {
		jhm::position pos = jhm::position(curve.at(i)[0] + position[0],
		curve.at(i)[1] + position[1],
		curve.at(i)[2] + position[2]);

		curve_translated.push_back(pos);
	}
	return curve_translated;
}
