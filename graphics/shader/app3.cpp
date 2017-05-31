#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/freeglut.h>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>
#include "mathclass/include/mathclass.h"

#include "Trackball.h"
#include "Model.h"
#include "CatmullRom_2D.h"
#include "BSpline_2D.h"
#include "TransformManager.h"
#include "Material.h"
#include "Cube.h"
#include "Triangle.h"

using namespace std;

GLdouble rotMatrix[16] =
{
	1, 0, 0, 0,
	0, 1, 0, 0,
	0, 0, 1, 0,
	0, 0, 0, 1
};

// ------------------------------
// variables for Mymodel
// ------------------------------

Model model;

// ------------------------------
// variables for views
// ------------------------------

int width, height;
GLfloat mousePosX, mousePosY;
Trackball trackball;

bool controlButton = false;
bool leftButton = false;
float zoomRatio = 1;

float eye[3] = { 0.0f, 0.0f, 200.0f };
float ori[3] = { 0.0f, 0.0f, 0.0f };
float look[3] = { 0.0f, 1.0f, 0.0f};
float rot[3] = { 0.0f, 0.0f, 0.0f };

void loadGlobalCoord()
{
	glLoadIdentity();
	gluLookAt((eye[0]-ori[0])*zoomRatio,
		(eye[1]-ori[1])*zoomRatio,
		(eye[2]-ori[2])*zoomRatio,
		ori[0], ori[1], ori[2],
		look[0], look[1], look[2]);
	glMultMatrixd(rotMatrix);
}

//-----------------------------------------------------
// Moves the screen based on mouse pressed button
//-----------------------------------------------------

void glutMotion(int x, int y)
{
	if (controlButton) { // translation mode
		float dx = (x-mousePosX)/10;
		float dy = (y-mousePosY)/10;

		mousePosX = x;
		mousePosY = y;

		glPushMatrix();
		glLoadIdentity();
		glTranslatef(-dx,dy,0);
		glMultMatrixd(rotMatrix);
		glGetDoublev(GL_MODELVIEW_MATRIX, rotMatrix);
		glPopMatrix();
	}

	else { // translation mode
		if ( leftButton ) {

			int a[2]; a[0] = mousePosX; a[1] = mousePosY;
			int b[2]; b[0] = x; b[1] = y;

			mousePosX = x;
			mousePosY = y;

			float axis[3]; float angle;
			trackball.getAxisAngle(a,b,axis,angle);
			glPushMatrix();
			glLoadIdentity();
			glRotatef(angle,axis[0],axis[1],axis[2]);
			glMultMatrixd(rotMatrix);
			glGetDoublev(GL_MODELVIEW_MATRIX, rotMatrix);
			glPopMatrix();

			loadGlobalCoord();
		}
	}
	return;
}

//-----------------------------------------
// Function that handles mouse input
//-----------------------------------------
void glutMouse(int button, int state, int x, int y) {

	switch ( button )
	{
		case GLUT_LEFT_BUTTON:
			if (controlButton) { // translation
					if(state == GLUT_DOWN) {
						mousePosX = x;
						mousePosY = y;
						leftButton = true;
					}
					else if(state == GLUT_UP) {
						leftButton = false;
					}
			}
			else {
				if ( state == GLUT_DOWN )
				{
					mousePosX = x;
					mousePosY = y;
					leftButton = true;
				}
				else if ( state == GLUT_UP )
				{
					leftButton = false;
				}
			}

			break;
		case GLUT_RIGHT_BUTTON:break;
		case 3:
			if(zoomRatio < 0.1) break;
			zoomRatio = zoomRatio- 0.05;
			break;
		case 4:
			zoomRatio = zoomRatio+ 0.05;
			break;
		default:break;
	}
	return;
}
// -----------------------
// Object Drawing part
// -----------------------

void stack_cuboid(
	GLfloat x, GLfloat y, GLfloat z,
	GLfloat R, GLfloat G, GLfloat B, GLfloat alpha
)
{
	glBegin(GL_TRIANGLES);
	float d= 1./sqrt(3);

	jhm::position p1;
	jhm::position p2;
	jhm::position p3;
	//Front
}

void draw_cuboid(GLfloat x,
                   GLfloat y,
                   GLfloat z)
{
	glBegin(GL_QUADS);
	float d = 1./sqrt(3);
    //Front
    glNormal3f(-d, -d, d);
    glVertex3f(-x, -y, z);
		glNormal3f(d, -d, d);
    glVertex3f(x, -y, z);
		glNormal3f(d, d, d);
    glVertex3f(x, y, z);
		glNormal3f(-d, d, d);
    glVertex3f(-x, y, z);

    //Right
		glNormal3f(d, -d, -d);
    glVertex3f(x, -y, -z);
		glNormal3f(d, d, -d);
    glVertex3f(x, y, -z);
		glNormal3f(d, d, d);
    glVertex3f(x, y, z);
		glNormal3f(d, -d, d);
    glVertex3f(x, -y, z);

    //Back
		glNormal3f(-d, -d, -d);
    glVertex3f(-x, -y, -z);
		glNormal3f(-d, d, -d);
    glVertex3f(-x, y, -z);
		glNormal3f(d, d, -d);
    glVertex3f(x, y, -z);
		glNormal3f(d, -d, -d);
    glVertex3f(x, -y, -z);

    //Left
		glNormal3f(-d, -d, -d);
    glVertex3f(-x, -y, -z);
		glNormal3f(-d, -d, d);
    glVertex3f(-x, -y, z);
		glNormal3f(-d, d, d);
    glVertex3f(-x, y, z);
		glNormal3f(-d, d, -d);
    glVertex3f(-x, y, -z);

    //Top
		glNormal3f(-d, d, -d);
    glVertex3f(-x, y, -z);
		glNormal3f(-d, d, d);
    glVertex3f(-x, y, z);
		glNormal3f(d, d, d);
    glVertex3f(x, y, z);
		glNormal3f(d, d, -d);
    glVertex3f(x, y, -z);

    //Bottom
		glNormal3f(-d, -d, -d);
    glVertex3f(-x, -y, -z);
		glNormal3f(-d, -d, d);
    glVertex3f(-x, -y, z);
		glNormal3f(d, -d, d);
    glVertex3f(x, -y, z);
		glNormal3f(d, -d, -d);
    glVertex3f(x, -y, -z);
    glEnd();


		glDisable(GL_COLOR_MATERIAL);
}

void display() {
	glClearColor(10./255,105./255,148./255,0.5);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	loadGlobalCoord();

	Material::onEmerald();
	glEnable(GL_COLOR_MATERIAL);
	draw_cuboid(10, 10, 10);
	glDisable(GL_COLOR_MATERIAL);

	Material::onPearl();
	glEnable(GL_COLOR_MATERIAL);
	glTranslatef(-20, 0, 0);
	glutSolidSphere(5,20,20);
	glDisable(GL_COLOR_MATERIAL);

	glTranslatef(20,0,0);

	Material::onRuby();
	glEnable(GL_COLOR_MATERIAL);
	jhm::position eye_p(eye[0], eye[1], eye[2]);
	model.draw_BSPdepthOrder(eye_p);

	glDisable(GL_COLOR_MATERIAL);

	glTranslatef(20,0,0);
	glRotatef(30.0, 0.0, 1.0, 0.5);
	Material::onEmerald();
	glEnable(GL_COLOR_MATERIAL);
	model.draw_BSPdepthOrder(eye_p);

	glDisable(GL_COLOR_MATERIAL);

	// Material::onRuby();
	// glEnable(GL_COLOR_MATERIAL);
	// glColor4f(1.0, 1.0, 1.0, 0.5);
	// glutSolidSphere(65, 30, 30);

	glutSwapBuffers();
}

void resize(int w, int h) {
	width = w;
	height = h;
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, (GLfloat)w / (GLfloat)h, .1f, 500.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

bool lightOn[] = {false, false, false};
bool colorOn = true;

void keyboard(unsigned char key, int x, int y) {
	switch (key) {

	case 27:
		exit(0);
		break;

	case 99:
		controlButton = !controlButton;
		if(controlButton == false) {
			std::cout << "Rotation Mode." << std::endl;
		}
		else {
			std::cout << "Translation Mode." << std::endl;
		}

	case '1':
		if(lightOn[0]) {
			glDisable(GL_LIGHT0);
			lightOn[0] = false;
		}
		else {
			glEnable(GL_LIGHT0);
			lightOn[0] = true;
		}
		break;

	case '2':
		if(lightOn[1]) {
			glDisable(GL_LIGHT1);
			lightOn[1] = false;
		}
		else {
			glEnable(GL_LIGHT1);
			lightOn[1] = true;
		}
		break;

	case '3':
		if(lightOn[2]) {
			glDisable(GL_LIGHT2);
			lightOn[2] = false;
		}
		else {
			glEnable(GL_LIGHT2);
			lightOn[2] = true;
		}
		break;

	default:
		break;
	}
}

unsigned timeStep = 30;

void Timer(int unused)
{
	loadGlobalCoord();
	glutPostRedisplay();
	glutTimerFunc(timeStep, Timer, 0);
}

int main(int argc, char **argv) {

	trackball = Trackball(7.0, 5.0);
  model = Model("data.txt", 3, 0.5);
	model.stack_Surface_stripe(1.0, 1.0, 1.0, 0.5, 1.0, 102./255, 0.0, 0.5);
	model.tree.buildBSPtree();
	std::cout << model.tree.triangles.size() << std::endl;

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(400, 400);
	glutInitWindowPosition( 50, 0 );
	glutCreateWindow("Example");
	glEnable(GL_DEPTH_TEST);

	glEnable( GL_LIGHTING );
	glEnable( GL_LIGHT0 );
	GLfloat AmbientLightValue0[4] = {1.0f, 0.0f, 0.0f, 0.0f};
	GLfloat DiffuseLightValue0[4] = {1.0f, 1.0f, 1.0f, 1.0f}; // white
	GLfloat SpecularLightValue0[4] = {1.0f, 1.0f, 1.0f, 1.0f};
	GLfloat PositionLightValue0[4] = {1.0f, 1.0f, 1.0f, 0.0f};
	glLightfv( GL_LIGHT0, GL_AMBIENT, AmbientLightValue0 );
	glLightfv( GL_LIGHT0, GL_DIFFUSE, DiffuseLightValue0 );
	glLightfv( GL_LIGHT0, GL_SPECULAR, SpecularLightValue0 );
	glLightfv( GL_LIGHT0, GL_POSITION, PositionLightValue0 );
	glDisable( GL_LIGHT0 );

	glEnable( GL_LIGHT1 );
	GLfloat DiffuseLightValue1[4] = {0.1f, 0.7f, 0.3f, 1.0f}; // green
	GLfloat SpecularLightValue1[4] = {1.0f, 1.0f, 1.0f, 1.0f};
	GLfloat PositionLightValue1[4] = {1000.0f, 0.0f, 0.0f, 1.0f};
	glLightfv( GL_LIGHT1, GL_DIFFUSE, DiffuseLightValue1 );
	glLightfv( GL_LIGHT1, GL_SPECULAR, SpecularLightValue1 );
	glLightfv( GL_LIGHT1, GL_POSITION, PositionLightValue1 );
	glDisable( GL_LIGHT1 );

	glEnable( GL_LIGHT2 );
	GLfloat DiffuseLightValue2[4] = {1.0f, 1.0f, 1.0f, 1.0f}; // white
	GLfloat SpecularLightValue2[4] = {1.0f, 1.0f, 1.0f, 1.0f};
	GLfloat PositionLightValue2[4] = {-1000.0f, 0.0f, 0.0f, 1.0f};
	glLightfv( GL_LIGHT2, GL_DIFFUSE, DiffuseLightValue2 );
	glLightfv( GL_LIGHT2, GL_SPECULAR, SpecularLightValue2 );
	glLightfv( GL_LIGHT2, GL_POSITION, PositionLightValue2 );
	glDisable( GL_LIGHT2 );

	glEnable(GL_BLEND); //Enable blending.
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); //Set blending function.
	glColorMaterial(GL_FRONT, GL_DIFFUSE); // color material

	glutReshapeFunc(resize);
	glutDisplayFunc(display);
	glutTimerFunc(timeStep, Timer, 0);
	glutKeyboardFunc(keyboard);
	glutMouseFunc(glutMouse);
	glutMotionFunc(glutMotion);

	glutMainLoop();

	return 0;
}
