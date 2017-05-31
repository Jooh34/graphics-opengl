#include "Light.h"

Light :: Light (
  GLfloat AmbientLightValue[],
  GLfloat DiffuseLightValue[],
  GLfloat SpecularLightValue[],
  GLfloat PositionLightValue[])
{
  for (int i=0; i<4; i++) {
    this->AmbientLightValue[i] = AmbientLightValue[i];
    this->DiffuseLightValue[i] = DiffuseLightValue[i];
    this->SpecularLightValue[i] = SpecularLightValue[i];
    this->PositionLightValue[i] = PositionLightValue[i];

  }
}

void Light :: initLight() {

	glLightfv( GL_LIGHT0, GL_AMBIENT, AmbientLightValue );
	glLightfv( GL_LIGHT0, GL_DIFFUSE, DiffuseLightValue );
	glLightfv( GL_LIGHT0, GL_SPECULAR, SpecularLightValue );
	glLightfv( GL_LIGHT0, GL_POSITION, PositionLightValue );

}
