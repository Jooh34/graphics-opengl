#include "Color.h"

Color :: Color (){}

Color :: Color (float R, float G, float B)
{
  this->R = R;
  this->G = G;
  this->B = B;
}

Color Color::operator+(const Color& c) {
  Color temp(R+c.R, G+c.G, B+c.B);
  return temp;
}
