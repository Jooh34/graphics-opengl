#ifndef TRACKBALL_H
#define TRACKBALL_H

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/freeglut.h>

class Trackball
{
public:
  float TRACKBALL_RADIUS;
  // should manage float overflow if Radius is too long

  float RATIO_WV;
  // Aspect Ratio

  Trackball();
  Trackball(float radius, float ratio_wv);
  void getAxisAngle(int a[2], int b[2], float axis[3], float &angle);
  void getVectorOnTrackball(int x, int y, int w, int h, float v[3]);
  float normalize(float v[3]);
  float dotProduct(float v_1[3], float v_2[3]);
  void crossProduct(float v_1[3], float v_2[3], float v_3[3]);
  void normalization (float v[3]);
};

#endif
