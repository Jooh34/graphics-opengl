#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/freeglut.h>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>
#include <string>
#include "mathclass/include/mathclass.h"

#include "Trackball.h"
#include "Piece.h"
#include "EdgePiece.h"
#include "CornerPiece.h"
#include "CenterPiece.h"
#include "RotationManager.h"

using namespace std;

GLdouble rotMatrix[16] =
{
	1, 0, 0, 0,
	0, 1, 0, 0,
	0, 0, 1, 0,
	0, 0, 0, 1
};

// ----------------------
//	const vars for color
// ----------------------

const static int M = 0;
const static int W = 1;
const static int Y = 2;
const static int B = 3;
const static int R = 4;
const static int G = 5;
const static int O = 6;

// ----------------------
//	const vars for location
// ----------------------

// Rotation Dir //
const static int U_ = 0;
const static int U_i = 1;
const static int F_ = 2;
const static int F_i = 3;
const static int R_ = 4;
const static int R_i = 5;
const static int B_ = 6;
const static int B_i = 7;
const static int L_ = 8;
const static int L_i = 9;
const static int D_ = 10;
const static int D_i = 11;

// ------------------------------
//	global declaration for pieces
// ------------------------------

float size = 20;

vector<EdgePiece> EP_list;
vector<CornerPiece> CP_list;
vector<CenterPiece> TP_list;

RotationManager rotManager = RotationManager(EP_list, CP_list, TP_list);

// ------------------------------
// variables for views
// ------------------------------

int width, height;
GLfloat mousePosX, mousePosY;
Trackball trackball = Trackball(7.0, 5.0);

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

	else { // rotation mode
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

void setPiece() {
	EdgePiece edgepiece0 = EdgePiece(0, Y, B, size);
	EP_list.push_back(edgepiece0);
	EdgePiece edgepiece1 = EdgePiece(1, Y, R, size);
	EP_list.push_back(edgepiece1);
	EdgePiece edgepiece2 = EdgePiece(2, Y, G, size);
	EP_list.push_back(edgepiece2);
	EdgePiece edgepiece3 = EdgePiece(3, Y, O, size);
	EP_list.push_back(edgepiece3);
	EdgePiece edgepiece4 = EdgePiece(4, B, R, size);
	EP_list.push_back(edgepiece4);
	EdgePiece edgepiece5 = EdgePiece(5, G, R, size);
	EP_list.push_back(edgepiece5);
	EdgePiece edgepiece6 = EdgePiece(6, G, O, size);
	EP_list.push_back(edgepiece6);
	EdgePiece edgepiece7 = EdgePiece(7, B, O, size);
	EP_list.push_back(edgepiece7);
	EdgePiece edgepiece8 = EdgePiece(8, B, W, size);
	EP_list.push_back(edgepiece8);
	EdgePiece edgepiece9 = EdgePiece(9, R, W, size);
	EP_list.push_back(edgepiece9);
	EdgePiece edgepiece10 = EdgePiece(10, G, W, size);
	EP_list.push_back(edgepiece10);
	EdgePiece edgepiece11 = EdgePiece(11, O, W, size);
	EP_list.push_back(edgepiece11);

	CornerPiece cornerpiece0 = CornerPiece(0, Y, O, B, size);
	CP_list.push_back(cornerpiece0);
	CornerPiece cornerpiece1 = CornerPiece(1, Y, B, R, size);
	CP_list.push_back(cornerpiece1);
	CornerPiece cornerpiece2 = CornerPiece(2, Y, R, G, size);
	CP_list.push_back(cornerpiece2);
	CornerPiece cornerpiece3 = CornerPiece(3, Y, G, O, size);
	CP_list.push_back(cornerpiece3);
	CornerPiece cornerpiece4 = CornerPiece(4, W, B, O, size);
	CP_list.push_back(cornerpiece4);
	CornerPiece cornerpiece5 = CornerPiece(5, W, R, B, size);
	CP_list.push_back(cornerpiece5);
	CornerPiece cornerpiece6 = CornerPiece(6, W, G, R, size);
	CP_list.push_back(cornerpiece6);
	CornerPiece cornerpiece7 = CornerPiece(7, W, O, G, size);
	CP_list.push_back(cornerpiece7);

	CenterPiece centerpiece0 = CenterPiece(0, Y, size);
	TP_list.push_back(centerpiece0);
	CenterPiece centerpiece1 = CenterPiece(1, B, size);
	TP_list.push_back(centerpiece1);
	CenterPiece centerpiece2 = CenterPiece(2, R, size);
	TP_list.push_back(centerpiece2);
	CenterPiece centerpiece3 = CenterPiece(3, O, size);
	TP_list.push_back(centerpiece3);
	CenterPiece centerpiece4 = CenterPiece(4, G, size);
	TP_list.push_back(centerpiece4);
	CenterPiece centerpiece5 = CenterPiece(5, W, size);
	TP_list.push_back(centerpiece5);

}

void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	loadGlobalCoord();

	glBegin(GL_QUADS);

	if(rotManager.rotating) {
		rotManager.rotate();
		rotManager.timer--;
	}

	if(rotManager.timer == 0) {
		rotManager.rotating = false;
	}


	for(int i=0; i<EP_list.size(); i++) {
		EP_list.at(i).draw();
	}

	for(int i=0; i<CP_list.size(); i++) {
		CP_list.at(i).draw();
	}

	for(int i=0; i<TP_list.size(); i++) {
		TP_list.at(i).draw();
	}
	glEnd();
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

void keyboard(unsigned char key, int x, int y) {
	switch (key) {

	case 27:
		exit(0);
		break;

	case 101: // e
		if(!rotManager.rotating) {
			rotManager.setRotate(U_i);
		}
		break;

	case 114: // r
		if(!rotManager.rotating) {
			rotManager.setRotate(U_);
		}
		break;

	case 99: // c
		if(!rotManager.rotating) {
			rotManager.setRotate(D_);
		}
		break;

	case 118: // v
		if(!rotManager.rotating) {
			rotManager.setRotate(D_i);
		}
		break;

	case 103: //g
		if(!rotManager.rotating) {
			rotManager.setRotate(R_);
		}
		break;

	case 104: //h
		if(!rotManager.rotating) {
			rotManager.setRotate(R_i);
		}
		break;

	case 97: //a
		if(!rotManager.rotating) {
			rotManager.setRotate(L_);
		}
		break;

	case 115: //s
		if(!rotManager.rotating) {
			rotManager.setRotate(L_i);
		}
		break;

	case 100: //d
		if(!rotManager.rotating) {
			rotManager.setRotate(F_);
		}
		break;

	case 102: //f
		if(!rotManager.rotating) {
			rotManager.setRotate(F_i);
		}
		break;

	case 116: //t
		if(!rotManager.rotating) {
			rotManager.setRotate(B_);
		}
		break;

	case 121: //y
		if(!rotManager.rotating) {
			rotManager.setRotate(B_i);
		}
		break;

	// case 99:
	// 	controlButton = !controlButton;
	// 	if(controlButton == false) {
	// 		std::cout << "Rotation Mode." << std::endl;
	// 	}
	// 	else {
	// 		std::cout << "Translation Mode." << std::endl;
	// 	}

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

	setPiece();

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(700, 700);
	glutInitWindowPosition( 50, 0 );
	glutCreateWindow("Example");
	glEnable(GL_DEPTH_TEST);

	glutReshapeFunc(resize);
	glutDisplayFunc(display);
	glutTimerFunc(timeStep, Timer, 0);
	glutKeyboardFunc(keyboard);
	glutMouseFunc(glutMouse);
	glutMotionFunc(glutMotion);

	glutMainLoop();

	return 0;
}
