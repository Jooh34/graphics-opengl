#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/freeglut.h>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "mathclass/include/mathclass.h"

#include "Color.h"
#include "Object.h"
#include "Sphere.h"
#include "Polygon.h"
#include "Model.h"
#include "Texture.h"
#include "Model.h"
#include "ObjParser.h"

using namespace std;

#define EPS 0.01f

//---------------------
// Temp light value
//---------------------

jhm::position lightPosition = jhm::position(-200.0f, 800.0f, 0.0f);
float lightRadius = 200;
int shadowSample = 50;
//---------------------
// variables for image
//---------------------

int MAX_DEPTH = 5;
float zoom = 60;

int w = 2480;
int h = 1920;

jhm::position eye(0.0f, 1600.0f, 2800.0f);
jhm::position ori(0.0f, 0.0f, 0.0f);
float vp_D = 80.0f; // distance of view plane ( eye <-> viewPlane)

std::vector<Object*> objects;


////////////////////////

void drawWall(float size) {
	float height = 400;
	jhm::position p1(-size, -height, -size);
	jhm::position p2(size, -height, -size);
	jhm::position p3(size, 2*size-height, -size);
	jhm::position p4(-size, 2*size-height, -size);
	jhm::position p5(-size, 2*size-height, size);
	jhm::position p6(-size, -height, size);
	jhm::position p7(size, -height, size);
	jhm::position p8(size, 2*size-height, size);

	Texture* wood = new Texture("wood.bmp");
	Texture* check = new Texture("check.bmp");

	objects.push_back(new Polygon(
		p1,p2,p3,
		jhm::vector(0.05, 0.05, 0.05),
		jhm::vector(0.5, 0.5, 0.5),
		jhm::vector(0.7, 0.7, 0.7),
		40, 0, 0, 1, check
	));

	objects.push_back(new Polygon(
		p1,p4,p3,
		jhm::vector(0.05, 0.05, 0.05),
		jhm::vector(0.5, 0.5, 0.5),
		jhm::vector(0.7, 0.7, 0.7),
		40, 0, 0, 1, check
	));

	objects.push_back(new Polygon(
		p1,p4,p5,
		jhm::vector(0.05, 0.05, 0.05),
		jhm::vector(0.5, 0.5, 0.5),
		jhm::vector(0.7, 0.7, 0.7),
		40, 0, 0, 1, check
	));

	objects.push_back(new Polygon(
		p1,p6,p5,
		jhm::vector(0.05, 0.05, 0.05),
		jhm::vector(0.5, 0.5, 0.5),
		jhm::vector(0.7, 0.7, 0.7),
		40, 0, 0, 1, check
	));

	objects.push_back(new Polygon(
		p1,p6,p7,
		jhm::vector(0.05, 0.05, 0.05),
		jhm::vector(0.5, 0.5, 0.5),
		jhm::vector(0.7, 0.7, 0.7),
		40, 0, 0, 1, wood
	));

	objects.push_back(new Polygon(
		p1,p2,p7,
		jhm::vector(0.05, 0.05, 0.05),
		jhm::vector(0.5, 0.5, 0.5),
		jhm::vector(0.7, 0.7, 0.7),
		40, 0, 0, 1, wood
	));

	objects.push_back(new Polygon(
		p8,p3,p2,
		jhm::vector(0.05, 0.05, 0.05),
		jhm::vector(0.5, 0.5, 0.5),
		jhm::vector(0.7, 0.7, 0.7),
		40, 0, 0, 1, check
	));

	// objects.push_back(new Polygon(
	// 	p8,p3,p4,
	// 	jhm::vector(0.05, 0.05, 0.05),
	// 	jhm::vector(0.5, 0.5, 0.3),
	// 	jhm::vector(0.7, 0.7, 0.5),
	// 	40, 0, 0, 1, wood
	// ));
	//
	// objects.push_back(new Polygon(
	// 	p8,p5,p4,
	// 	jhm::vector(0.05, 0.05, 0.05),
	// 	jhm::vector(0.5, 0.5, 0.3),
	// 	jhm::vector(0.7, 0.7, 0.5),
	// 	40, 0, 0, 1, wood
	// ));

	// objects.push_back(new Polygon(
	// 	p8,p5,p6,
	// 	jhm::vector(0.192, 0.192, 0.192),
	// 	jhm::vector(0.5, 0.5, 0.5),
	// 	jhm::vector(0.5, 0.5, 0.5),
	// 	0.4, 0, 0, 1
	// ));
	//
	// objects.push_back(new Polygon(
	// 	p8,p6,p7,
	// 	jhm::vector(0.192, 0.192, 0.192),
	// 	jhm::vector(0.5, 0.5, 0.5),
	// 	jhm::vector(0.5, 0.5, 0.5),
	// 	0.4, 0, 0, 1
	// ));

	objects.push_back(new Polygon(
		p8,p7,p2,
		jhm::vector(0.05, 0.05, 0.05),
		jhm::vector(0.5, 0.5, 0.5),
		jhm::vector(0.7, 0.7, 0.7),
		40, 0, 0, 1, check
	));
}

void drawCube(float size,
	jhm::vector translation,
	jhm::vector ka,
	jhm::vector kd,
	jhm::vector ks,
	float kn,
	float reflectivity,
	float transparency,
	float ns
) {
	jhm::position p_1(-size, -size, -size);
	jhm::position p_2(size, -size, -size);
	jhm::position p_3(size, size, -size);
	jhm::position p_4(-size, size, -size);
	jhm::position p_5(-size, size, size);
	jhm::position p_6(-size, -size, size);
	jhm::position p_7(size, -size, size);
	jhm::position p_8(size, size, size);

	jhm::position p1=p_1+translation;
	jhm::position p2=p_2+translation;
	jhm::position p3=p_3+translation;
	jhm::position p4=p_4+translation;
	jhm::position p5=p_5+translation;
	jhm::position p6=p_6+translation;
	jhm::position p7=p_7+translation;
	jhm::position p8=p_8+translation;

	objects.push_back(new Polygon(
		p1,p2,p3,
		ka,kd,ks,kn,
		reflectivity,transparency,ns
	));

	objects.push_back(new Polygon(
		p1,p3,p4,
		ka,kd,ks,kn,
		reflectivity,transparency,ns
	));

	objects.push_back(new Polygon(
		p1,p4,p5,
		ka,kd,ks,kn,
		reflectivity,transparency,ns
	));

	objects.push_back(new Polygon(
		p1,p5,p6,
		ka,kd,ks,kn,
		reflectivity,transparency,ns
	));

	objects.push_back(new Polygon(
		p8,p2,p3,
		ka,kd,ks,kn,
		reflectivity,transparency,ns
	));

	objects.push_back(new Polygon(
		p8,p3,p4,
		ka,kd,ks,kn,
		reflectivity,transparency,ns
	));

	objects.push_back(new Polygon(
		p8,p4,p5,
		ka,kd,ks,kn,
		reflectivity,transparency,ns
	));

	objects.push_back(new Polygon(
		p8,p5,p6,
		ka,kd,ks,kn,
		reflectivity,transparency,ns
	));

	objects.push_back(new Polygon(
		p8,p6,p7,
		ka,kd,ks,kn,
		reflectivity,transparency,ns
	));

	objects.push_back(new Polygon(
		p8,p7,p2,
		ka,kd,ks,kn,
		reflectivity,transparency,ns
	));
}

void draw() {

	drawWall(900);
	// drawCube(100,
	// 	jhm::vector(-500,-300,100),
	// 	jhm::vector(0.24,0.20,0.07),
	// 	jhm::vector(0.75,0.60,0.22),
	// 	jhm::vector(0.63,0.56,0.37),
	// 	40, 0, 0, 1);

	//light source

	//color ball
	Texture* colorball = new Texture("color.bmp");
	objects.push_back(new Sphere(
		jhm::position(350,0,0),
		100,
		jhm::vector(0.05, 0.05, 0.05),
		jhm::vector(0.5, 0.5, 0.5),
		jhm::vector(0.7, 0.7, 0.7),
		30, 0, 0, 1, colorball
	));

	//ruby sphere
	objects.push_back(new Sphere(
		jhm::position(-150,-340,-0),
		60,
		jhm::vector(0.17, 0.011, 0.11),
		jhm::vector(0.61, 0.04, 0.04),
		jhm::vector(0.72, 0.62, 0.62),
		10, 0, 0, 0.5
	));

	//emerald sphere
	objects.push_back(new Sphere(
		jhm::position(0,-320,-0),
		80,
		jhm::vector(0.02, 0.17, 0.02),
		jhm::vector(0.07, 0.61, 0.07),
		jhm::vector(0.63, 0.73, 0.63),
		10, 0, 0, 0.5
	));

	//mirror sphere
	// objects.push_back(new Sphere(
	// 	jhm::position(-350,-100,-300),
	// 	100,
	// 	jhm::vector(0.25, 0.20, 0.20),
	// 	jhm::vector(1, 0.83, 0.83),
	// 	jhm::vector(0.30, 0.30, 0.30),
	// 	8, 1.0, 0, 1
	// ));

	//mirror
	jhm::vector t = jhm::vector(0,0,0);
	objects.push_back(new Polygon(
		jhm::position(-350, -390, 100),
		jhm::position(-50, -390, -400),
		jhm::position(-50, 0, -400),
		t, t, t, 30,
		0.9,0,1
	));

	objects.push_back(new Polygon(
		jhm::position(-50, 0, -400),
		jhm::position(-350, 0, 100),
		jhm::position(-350, -390, 100),
		t, t, t, 30,
		0.9,0,1
	));


	// glass sphere
	objects.push_back(new Sphere(
		jhm::position(200,-150,100),
		100,
		jhm::vector(0.17, 0.011, 0.11),
		jhm::vector(0.61, 0.04, 0.04),
		jhm::vector(0.72, 0.62, 0.62),
		8, 0, 1, 1.6
	));

	//gold fish
  // Model* model = new Model("data.txt", 2, 1.0,
	// jhm::vector(0,0,0), 1,
	// jhm::vector(0.33, 0.22, 0.02),
	// jhm::vector(0.78, 0.45, 0.11),
	// jhm::vector(0.99, 0.94, 0.80),
	// 20, 0, 0, 1);
	//
	//
	// char objname[] = "teapot.obj";
	// ObjParser parser = ObjParser(objname, jhm::vector(0,0,-500), 50, model->tree);
	// model->stack_Surface_stripe(1.0, 1.0, 1.0, 1.0, 1.0, 102./255, 0.0, 1.0);
	// model->tree.buildBSPtree();
	// objects.push_back(model);
}

jhm::vector getRayVector(int x_, int y_) {
  float x = float(x_);
  float y = float(y_);

  jhm::vector look_vec = ori-eye;
  float look_D = look_vec.length();
  float ratio = vp_D/look_D;

  jhm::vector plane_vec(x-((float)(w-1))/2, y-((float)(h-1))/2, 0);
  return (look_vec * ratio) + plane_vec/zoom;
}

int findNearestObject(jhm::position ori, jhm::vector dir) {
	bool find = false;
	float min = 99999999;
	int min_i = -1;

	for (int i = 0; i < objects.size(); i++) {
		jhm::position intersect;
		jhm::vector pv;
		if (objects.at(i)->intersect(ori, dir, intersect, pv)) {
			if ((ori-intersect).length() < min) {
				min = (ori-intersect).length();
				min_i = i;
				find = true;
			}
    }
	}

	if(find) return min_i;
	else return -1;
}

jhm::vector trace(jhm::position ori, jhm::vector dir, int depth) {
  if(depth > MAX_DEPTH) {
    return jhm::vector(0,0,0);
  }


	int index = findNearestObject(ori,dir);

  if(index == -1) { // background
    return jhm::vector(0.3,0.3,0.3);
  }

	Object* object = objects.at(index);
	jhm::position pHit;
	jhm::vector N;
	object->intersect(ori,dir, pHit, N);

	jhm::vector color_stack = jhm::vector(0,0,0);
	pHit = pHit + N*EPS;

	// reflectiion
	if(object->reflectivity > 0)
	{
		jhm::vector L = -dir;
		//get reflection Ray
		jhm::vector reflecDir = (2*L % N)*N - L;
		color_stack = color_stack + object->reflectivity * trace(pHit, reflecDir, depth+1);
	}

	// refraction
	if(object->transparency > 0)
	{
		jhm::vector L = -dir;
		float ratio; // ni / nr;
		jhm::vector refracN;

		if(N%L > 0) { // out -> in
			ratio = 1 / object->n;
			refracN = N;
		}
		else { // in -> out
			ratio = object->n;
			refracN = -N;
		}

		float cos_i = (refracN%L)/refracN.length()*L.length();
		float cos_r = sqrt(abs(1-ratio*ratio*(1-cos_i*cos_i)));
		jhm::vector refracDir = (ratio*cos_i - cos_r)*refracN - ratio*L;

		color_stack = color_stack + object->transparency * trace(pHit-refracN*2*EPS, refracDir.normalize(), depth+1);
	}

  //diffuse color
	else if (1-object->reflectivity-object->transparency > 0)
	{
		jhm::vector shadowRayVec = (lightPosition - pHit);
		int shadowCount = 0;

		for (int i=0; i<shadowSample; i++) { // soft shadow
	    float e1 = static_cast<float> (rand()) / (static_cast<float> (RAND_MAX/2)) - 1;
	    float e2 = static_cast<float> (rand()) / (static_cast<float> (RAND_MAX/2)) - 1;
	    float e3 = static_cast<float> (rand()) / (static_cast<float> (RAND_MAX/2)) - 1;
	    float d = static_cast<float> (rand()) / (static_cast<float> (RAND_MAX/lightRadius));

	    jhm::vector randomVec = jhm::vector(e1, e2, e3);
	    jhm::vector orth = (shadowRayVec * randomVec).normalize();
	    jhm::vector randomRay = shadowRayVec + (d * orth);

			index = findNearestObject(pHit, randomRay.normalize());

			if(index != -1) {
				Object* block_object = objects.at(index);
				jhm::position shadow_Hit;
				jhm::vector temp;
				block_object->intersect(pHit, shadowRayVec.normalize(), shadow_Hit, temp);

				if((pHit-shadow_Hit).length() < randomRay.length()) { // Shadow
					shadowCount ++;
			  }
			}
		}

		jhm::vector color = object->ka;
		if(object->texture) color = object->getTextureColor(pHit);

		color = 0.2 * color + 0.8 * color * (shadowSample - shadowCount) / shadowSample;

		jhm::vector L = (lightPosition-pHit).normalize();
		jhm::vector R = N * (2 * (L%N)) - L;
		R = R.normalize();

		color = color + (object->kd * abs(N%L) + object->ks * pow(max((R%-dir), 0.0), object->kn));
		color_stack = color_stack + color * (1-object->reflectivity-object->transparency);
	}
	return color_stack;
}

void render() {

  FILE *f;
  unsigned char *img = NULL;
  int filesize = 54 + 3*w*h;  //w is your image width, h is image height, both int
  if( img )
      free( img );
  img = (unsigned char *)malloc(3*w*h);
  memset(img,0,sizeof(img));

  for(int i=0; i<w; i++)
  {
		printf("i = %d\n",i);
      for(int j=0; j<h; j++)
      {
				jhm::vector pixel;
				jhm::vector ray_vec = getRayVector(i, j);
	      ray_vec = ray_vec.normalize();
	      pixel = trace(eye, ray_vec, 0);
          int x=i; int y=(h-1)-j;
          float r = pixel[0]*255;
          float g = pixel[1]*255;
          float b = pixel[2]*255;
          if (r > 255) r=255;
          if (g > 255) g=255;
          if (b > 255) b=255;
          img[(x+y*w)*3+2] = (unsigned char)(r);
          img[(x+y*w)*3+1] = (unsigned char)(g);
          img[(x+y*w)*3+0] = (unsigned char)(b);
      }
  }

  unsigned char bmpfileheader[14] = {'B','M', 0,0,0,0, 0,0, 0,0, 54,0,0,0};
  unsigned char bmpinfoheader[40] = {40,0,0,0, 0,0,0,0, 0,0,0,0, 1,0, 24,0};
  unsigned char bmppad[3] = {0,0,0};

  bmpfileheader[ 2] = (unsigned char)(filesize    );
  bmpfileheader[ 3] = (unsigned char)(filesize>> 8);
  bmpfileheader[ 4] = (unsigned char)(filesize>>16);
  bmpfileheader[ 5] = (unsigned char)(filesize>>24);

  bmpinfoheader[ 4] = (unsigned char)(       w    );
  bmpinfoheader[ 5] = (unsigned char)(       w>> 8);
  bmpinfoheader[ 6] = (unsigned char)(       w>>16);
  bmpinfoheader[ 7] = (unsigned char)(       w>>24);
  bmpinfoheader[ 8] = (unsigned char)(       h    );
  bmpinfoheader[ 9] = (unsigned char)(       h>> 8);
  bmpinfoheader[10] = (unsigned char)(       h>>16);
  bmpinfoheader[11] = (unsigned char)(       h>>24);

  f = fopen("img.bmp","wb");
  fwrite(bmpfileheader,1,14,f);
  fwrite(bmpinfoheader,1,40,f);
  for(int i=0; i<h; i++)
  {
      fwrite(img+(w*(h-i-1)*3),3,w,f);
      fwrite(bmppad,1,(4-(w*3)%4)%4,f);
  }
  fclose(f);
}

void delete_all() {
	for (int i = 0; i < objects.size(); i++) {
		delete objects.at(i);
	}
}

int main(int argc, char **argv) {
  srand((unsigned)time(NULL));
  draw(); // draw and stack triangles
	printf("start rendering...\n");
  render();
	delete_all();

	return 0;
}
