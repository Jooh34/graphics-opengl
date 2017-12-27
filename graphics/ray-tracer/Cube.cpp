#include "Cube.h"

void Cube :: draw(float x, float y, float z) {

  glBegin(GL_QUADS);
	float d = 1./sqrt(3);
  float alpha = 0.5;

  //////////////////////////////
  // Emerald Front
  //////////////////////////////

	Material::onEmerald();

  glNormal3f(-d, -d, d);
  glVertex3f(-x, -y, z);
  glNormal3f(d, -d, d);
  glVertex3f(x, -y, z);
  glNormal3f(d, d, d);
  glVertex3f(x, y, z);
  glNormal3f(-d, d, d);
  glVertex3f(-x, y, z);


  //////////////////////////////
  // Ruby Right
  //////////////////////////////

	Material::onRuby();

  glNormal3f(d, -d, -d);
  glVertex3f(x, -y, -z);
  glNormal3f(d, d, -d);
  glVertex3f(x, y, -z);
  glNormal3f(d, d, d);
  glVertex3f(x, y, z);
  glNormal3f(d, -d, d);
  glVertex3f(x, -y, z);


  //////////////////////////////
  // Gold Back
  //////////////////////////////

	Material::onGold();

  glNormal3f(-d, -d, -d);
  glVertex3f(-x, -y, -z);
  glNormal3f(-d, d, -d);
  glVertex3f(-x, y, -z);
  glNormal3f(d, d, -d);
  glVertex3f(x, y, -z);
  glNormal3f(d, -d, -d);
  glVertex3f(x, -y, -z);


  //////////////////////////////
  // Bronze Left
  //////////////////////////////

  Material::onBronze();

  glNormal3f(-d, -d, -d);
  glVertex3f(-x, -y, -z);
  glNormal3f(-d, -d, d);
  glVertex3f(-x, -y, z);
  glNormal3f(-d, d, d);
  glVertex3f(-x, y, z);
  glNormal3f(-d, d, -d);
  glVertex3f(-x, y, -z);

  //////////////////////////////
  // Pearl Top
  //////////////////////////////

  Material::onPearl();

  glNormal3f(-d, d, -d);
  glVertex3f(-x, y, -z);
  glNormal3f(-d, d, d);
  glVertex3f(-x, y, z);
  glNormal3f(d, d, d);
  glVertex3f(x, y, z);
  glNormal3f(d, d, -d);
  glVertex3f(x, y, -z);


  //////////////////////////////
  // Green Plastic Bottom
  //////////////////////////////

  Material::onGreenPlastic();

  glNormal3f(-d, -d, -d);
  glVertex3f(-x, -y, -z);
  glNormal3f(-d, -d, d);
  glVertex3f(-x, -y, z);
  glNormal3f(d, -d, d);
  glVertex3f(x, -y, z);
  glNormal3f(d, -d, -d);
  glVertex3f(x, -y, -z);

  glEnd();

}
