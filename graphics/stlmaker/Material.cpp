#include "Material.h"

void Material :: onEmerald() {
  float alpha = 0.5;

  float ambient_emerald[4] = {0.0215, 0.1745, 0.0215, alpha};
	float diffuse_emerald[4] = {0.07568, 0.61424, 0.07568, alpha};
	float specular_emerald[4] = {0.633, 0.727811, 0.633, alpha};
	float shininess_emerald = 0.6;

  on(ambient_emerald, diffuse_emerald, specular_emerald, shininess_emerald);
}

void Material :: onRuby() {
  float alpha = 0.5;

  float ambient_ruby[4] = {0.1745, 0.01175, 0.01175, alpha};
	float diffuse_ruby[4] = {1, 0.829, 0.829, alpha};
	float specular_ruby[4] = {0.727811, 0.626959, 0.626959, alpha};
	float shininess_ruby = 0.6;

  on(ambient_ruby, diffuse_ruby, specular_ruby, shininess_ruby);
}

void Material :: onGold() {
  float alpha = 0.5;

  float ambient_gold[4] = {0.24725, 0.1995, 0.0745, alpha};
	float diffuse_gold[4] = {0.75164, 0.60648, 0.22648, alpha};
	float specular_gold[4] = {0.628281, 0.555802, 0.366065, alpha};
	float shininess_gold = 0.4;

  on(ambient_gold, diffuse_gold, specular_gold, shininess_gold);
}

void Material :: onBronze() {
  float alpha = 0.5;

  float ambient_bronze[4] = {0.2125, 0.1275, 0.054, alpha};
	float diffuse_bronze[4] = {0.714, 0.4284, 0.18144, alpha};
	float specular_bronze[4] = {0.393548, 0.271906, 0.166721, alpha};
	float shininess_bronze = 0.2;

  on(ambient_bronze, diffuse_bronze, specular_bronze, shininess_bronze);
}

void Material :: onPearl() {
  float alpha = 0.5;

  float ambient_pearl[4] = {0.25, 0.20725, 0.20725, alpha};
	float diffuse_pearl[4] = {1, 0.829, 0.829, alpha};
	float specular_pearl[4] = {0.296648, 0.296648, 0.296648, alpha};
	float shininess_pearl = 0.2;

  on(ambient_pearl, diffuse_pearl, specular_pearl, shininess_pearl);
}

void Material :: onGreenPlastic() {
  float alpha = 0.5;

  float ambient_plastic[4] = {0.25, 0.20725, 0.20725, alpha};
	float diffuse_plastic[4] = {1, 0.829, 0.829, alpha};
	float specular_plastic[4] = {0.296648, 0.296648, 0.296648, alpha};
	float shininess_plastic = 0.2;

  on(ambient_plastic, diffuse_plastic, specular_plastic, shininess_plastic);
}

void Material :: on(
  float ambient[],
  float diffuse[],
  float specular[],
  float shininess
) {
  glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
  glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
  glMaterialf(GL_FRONT, GL_SHININESS, shininess*128);

  glBindTexture(GL_TEXTURE_2D, 0);
}
