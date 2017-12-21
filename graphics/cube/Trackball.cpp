#include "Trackball.h"
#include <cmath>


Trackball :: Trackball(){}

Trackball :: Trackball(float radius, float ratio_wv)
{
  this->TRACKBALL_RADIUS = radius;
  this->RATIO_WV = ratio_wv;
}

void Trackball :: getAxisAngle(int a[2], int b[2], float axis[3], float &angle)
{
	float v_1[3]; float v_2[3];
	getVectorOnTrackball(a[0],a[1],glutGet(GLUT_WINDOW_WIDTH),glutGet(GLUT_WINDOW_HEIGHT),v_1);
	getVectorOnTrackball(b[0],b[1],glutGet(GLUT_WINDOW_WIDTH),glutGet(GLUT_WINDOW_HEIGHT),v_2);

	crossProduct(v_1, v_2, axis);

	float cosine = dotProduct(v_1,v_2)/(normalize(v_1) * normalize(v_2));

  angle = atan2(cosine,1-cosine*cosine);
}

void Trackball :: getVectorOnTrackball(int x, int y, int w, int h, float v[3])
{
	v[0] = RATIO_WV *(2.0*x -w)/w;
	v[1] = RATIO_WV *(h-2.0*y)/h;

	float d = v[0]*v[0] + v[1]*v[1];
	if(d > pow(TRACKBALL_RADIUS,2.0))
		d = pow(TRACKBALL_RADIUS,2.0); // if point is out of circle

	if(pow(TRACKBALL_RADIUS,2.0)-d > 0)
		v[2] =  sqrt(pow(TRACKBALL_RADIUS,2.0)-d);
	else v[2] = 0;
}

float Trackball :: normalize(float v[3]) {
	return sqrt(v[0]*v[0] + v[1]*v[1] + v[2]*v[2]);
}

float Trackball :: dotProduct(float v_1[3], float v_2[3]) {
	return v_1[0]*v_2[0] + v_1[1]*v_2[1] + v_1[2]*v_2[2];
}

void Trackball :: crossProduct(float v_1[3], float v_2[3], float v_3[3])
{
	v_3[0] = v_1[1]*v_2[2] - v_1[2]*v_2[1];
	v_3[1] = v_1[2]*v_2[0] - v_1[0]*v_2[2];
	v_3[2] = v_1[0]*v_2[1] - v_1[1]*v_2[0];
}

void Trackball :: normalization (float v[3]) {
	v[0] = v[0] / normalize(v);
	v[1] = v[1] / normalize(v);
	v[2] = v[2] / normalize(v);
}
