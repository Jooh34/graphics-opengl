#include "Texture.h"

Texture :: Texture (const char* filename) {
  bmp.ReadFromFile(filename);
  width = bmp.TellWidth();
  height = bmp.TellHeight();
}

jhm::vector Texture :: getTextureColor(float u, float v) {
  int x = floor((width * u)+0.5);
  int y = floor((height * v)+0.5);

  RGBApixel *temp = bmp(x, y);
  jhm::vector color(temp->Red / 255.0,
    temp->Green / 255.0,
    temp->Blue / 255.0);

  return color;
}
