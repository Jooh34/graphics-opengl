#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/freeglut.h>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>
#include <fstream>
#include <sstream>
#include "mathclass/include/mathclass.h"


using namespace std;

GLdouble rotMatrix[16] =
{
	1, 0, 0, 0,
	0, 1, 0, 0,
	0, 0, 1, 0,
	0, 0, 0, 1
};

// ------------------------------
// variables for views
// ------------------------------

int width, height;
GLfloat mousePosX, mousePosY;

bool controlButton = false;
bool leftButton = false;
float zoomRatio = 1;

float eye[3] = { -180.0f, 180.0f, 230.0f };
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

//------------------------------------------------------------------------
// Moves the screen based on mouse pressed button
//------------------------------------------------------------------------

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
			getAxisAngle(a,b,axis,angle);
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

//------------------------------------------------------------------------
// Function that handles mouse input
//------------------------------------------------------------------------
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
// 3D curve drawing part
// -----------------------
jhm::position addPos(jhm::position p1, jhm::position p2) {
	return jhm::position(p1[0]+p2[0], p1[1]+p2[1], p1[2]+p2[2]);
}

float tj(float ti, jhm::position Pi, jhm::position Pj) {
	return pow(pow(pow(Pj[0]-Pi[0], 2.0) + pow(Pj[1]-Pi[1], 2.0) + pow(Pj[2]-Pi[2],2.0), 0.5), alpha) + ti;
}

void catmullRomSpline(jhm::position P0, jhm::position P1, jhm::position P2,
	jhm::position P3, vector<jhm::position> &curve) {

	float t0 = 0;
	float t1 = tj(t0, P0, P1);
	float t2 = tj(t1, P1, P2);
	float t3 = tj(t2, P2, P3);

	float t = t1;

	for (int i = 0; i < nPoint; i++) {

		jhm::position A1 = addPos(P0*((t1-t)/(t1-t0)), P1*((t-t0)/(t1-t0)));
	  jhm::position A2 = addPos(P1*((t2-t)/(t2-t1)), P2*((t-t1)/(t2-t1)));
	  jhm::position A3 = addPos(P2*((t3-t)/(t3-t2)), P3*((t-t2)/(t3-t2)));

		jhm::position B1 = addPos(A1*((t2-t)/(t2-t0)), A2*((t-t0)/(t2-t0)));
	  jhm::position B2 = addPos(A2*((t3-t)/(t3-t1)), A3*((t-t1)/(t3-t1)));

	  jhm::position C  = addPos(B1*((t2-t)/(t2-t1)), B2*((t-t1)/(t2-t1)));

		curve.push_back(C);

		t = t + ((t2-t1)/nPoint);
	}
}

// -----------------------
// Rotation & Translation & scailing part
// -----------------------
vector<jhm::position> multQuater(int c_i, vector<jhm::position> curve) {
	vector<jhm::position> curve_rotated;
	float angle = crossSectionVec.at(c_i).angle;
	float axis[3];
	for(int j = 0; j<3; j++) axis[j] = crossSectionVec.at(c_i).axis[j];

	for(int i = 0; i<curve.size(); i++) {
		jhm::position pos = curve.at(i);

		jhm::quater q(cos(0.5*angle),
		axis[0]*sin(0.5*angle),
		axis[1]*sin(0.5*angle),
		axis[2]*sin(0.5*angle));

		jhm::position new_pos = rotate(q, pos);
		curve_rotated.push_back(new_pos);
	}
	return curve_rotated;
}

vector<jhm::position> translation(int c_i, vector<jhm::position> curve) {
	vector<jhm::position> curve_translated;

	float position[3];
	for(int j = 0; j<3; j++) position[j] = crossSectionVec.at(c_i).position[j];

	for(int i=0; i<curve.size(); i++) {
		jhm::position pos = jhm::position(curve.at(i)[0] + position[0],
		curve.at(i)[1] + position[1],
		curve.at(i)[2] + position[2]);

		curve_translated.push_back(pos);
	}
	return curve_translated;
}

vector<jhm::position> scailing(int c_i, vector<jhm::position> curve) {
	vector<jhm::position> curve_scailed;

	float scale;
	scale = crossSectionVec.at(c_i).scale;

	for(int i=0; i<curve.size(); i++) {
		jhm::position pos = jhm::position(curve.at(i)[0]*scale,
		curve.at(i)[1]*scale,
		curve.at(i)[2]*scale);

		curve_scailed.push_back(pos);
	}
	return curve_scailed;
}

// -----------------------
// Object Drawing part
// -----------------------
vector<jhm::position> reflectCrossSection(
	vector<jhm::position> C1,
	vector<jhm::position> C2
) {
	vector<jhm::position> C3;
	for(int i=0; i<C1.size(); i++) {
		C3.push_back(C1.at(i) + (C1.at(i)-C2.at(i)));
	}
	return C3;
}

void drawLineBetweenCrossSection (vector<jhm::position> C1,
	vector<jhm::position> C2,
	vector<jhm::position> C3,
	vector<jhm::position> C4,
	GLfloat R,
	GLfloat G,
	GLfloat B)
{
	glLineWidth(0.01);
	glColor3f(R, G, B);
	for(int i=0; i<C1.size(); i++) {
		vector<jhm::position> curve;
		catmullRomSpline(C1.at(i), C2.at(i), C3.at(i), C4.at(i), curve);
		curve.push_back(C3.at(i));
		glBegin(GL_LINE_STRIP);
		for(int j=0; j<curve.size(); j++) {
			glVertex3f(curve.at(j)[0], curve.at(j)[1], curve.at(j)[2]);
		}
		glEnd();
	}
}

void drawSurfaceBetweenCrossSection (vector<jhm::position> C1,
	vector<jhm::position> C2,
	vector<jhm::position> C3,
	vector<jhm::position> C4,
	GLfloat R,
	GLfloat G,
	GLfloat B)
	{
		glColor3f(R, G, B);
		for(int i=0; i<C1.size(); i++) {
			vector<jhm::position> curve1;
			vector<jhm::position> curve2;
			catmullRomSpline(C1.at(i), C2.at(i), C3.at(i), C4.at(i), curve1);
			catmullRomSpline(C1.at((i+1)%C1.size()),
			C2.at((i+1)%C1.size()),
			C3.at((i+1)%C1.size()),
			C4.at((i+1)%C1.size()),
			curve2
			);
			curve1.push_back(C3.at(i));
			curve2.push_back(C3.at((i+1)%C1.size()));

			glBegin(GL_QUAD_STRIP);
			for(int j=0; j<curve1.size(); j++) {
				glVertex3f(curve1.at(j)[0], curve1.at(j)[1], curve1.at(j)[2]);
				glVertex3f(curve2.at(j)[0], curve2.at(j)[1], curve2.at(j)[2]);
			}
			glEnd();
		}
	}

void interpolateCrossSection_line(vector<vector<jhm::position> > allVector,
	GLfloat R, GLfloat G, GLfloat B)
{
	for(int a_i=0; a_i<allVector.size()-3; a_i++) {
		drawLineBetweenCrossSection(allVector.at(a_i),
		allVector.at(a_i+1),
		allVector.at(a_i+2),
		allVector.at(a_i+3),
		R,G,B);
	}

	drawLineBetweenCrossSection(
		reflectCrossSection(allVector.at(0),allVector.at(1)),
	allVector.at(0),
	allVector.at(1),
	allVector.at(2),
	R,G,B);

	drawLineBetweenCrossSection(allVector.at(allVector.size()-3),
	allVector.at(allVector.size()-2),
	allVector.at(allVector.size()-1),
	reflectCrossSection(allVector.at(allVector.size()-1),allVector.at(allVector.size()-2)),
	R,G,B);

}

void interpolateCrossSection_surface(vector<vector<jhm::position> > allVector,
	GLfloat R, GLfloat G, GLfloat B) {
	for(int a_i=0; a_i<allVector.size()-3; a_i++) {
		drawSurfaceBetweenCrossSection(allVector.at(a_i),
		allVector.at(a_i+1),
		allVector.at(a_i+2),
		allVector.at(a_i+3),
		R, G, B);
	}

	drawSurfaceBetweenCrossSection(
		reflectCrossSection(allVector.at(0),allVector.at(1)),
	allVector.at(0),
	allVector.at(1),
	allVector.at(2),
	R, G, B);

	drawSurfaceBetweenCrossSection(allVector.at(allVector.size()-3),
	allVector.at(allVector.size()-2),
	allVector.at(allVector.size()-1),
	reflectCrossSection(allVector.at(allVector.size()-1),allVector.at(allVector.size()-2)),
	R, G, B);
}


void interpolateCrossSection_stripeSurface(vector<vector<jhm::position> > allVector,
	GLfloat R1, GLfloat G1, GLfloat B1,
	GLfloat R2, GLfloat G2, GLfloat B2)
{
	for(int a_i=0; a_i<allVector.size()-3; a_i++) {
		if(a_i%2 == 0) {
			drawSurfaceBetweenCrossSection(allVector.at(a_i),
			allVector.at(a_i+1),
			allVector.at(a_i+2),
			allVector.at(a_i+3),
			R1, G1, B1);
		}
		else {
			drawSurfaceBetweenCrossSection(allVector.at(a_i),
			allVector.at(a_i+1),
			allVector.at(a_i+2),
			allVector.at(a_i+3),
			R2, G2, B2);
		}
	}

	drawSurfaceBetweenCrossSection(
		reflectCrossSection(allVector.at(0),allVector.at(1)),
	allVector.at(0),
	allVector.at(1),
	allVector.at(2),
	R2, G2, B2);

	drawSurfaceBetweenCrossSection(allVector.at(allVector.size()-3),
	allVector.at(allVector.size()-2),
	allVector.at(allVector.size()-1),
	reflectCrossSection(allVector.at(allVector.size()-1),allVector.at(allVector.size()-2)),
	R2, G2, B2);
}

void drawCrossSection(vector<vector<jhm::position> > &allVector,
	GLfloat R, GLfloat G, GLfloat B) {
	for(int c_i=0; c_i<numCrossSection; c_i++) {
		glBegin(GL_LINE_STRIP);
		glColor3f(0.0, 1.0, 0.0);
		glLineWidth(1.0);
		vector<jhm::position> curve;
		(curveType == 0) ?
		curve = getBSplineCrossSection(c_i):
		curve = getCatmullRomCrossSection(c_i);

		vector<jhm::position> curve_scailed = scailing(c_i, curve);
		vector<jhm::position> curve_rotated = multQuater(c_i, curve_scailed);
		vector<jhm::position> curve3D = translation(c_i, curve_rotated);

		// drawing crossSection
		for(int j=0; j<curve.size(); j++) {
			glVertex3f(curve3D.at(j)[0], curve3D.at(j)[1], curve3D.at(j)[2]);
		}
		glVertex3f(curve3D.at(0)[0], curve3D.at(0)[1], curve3D.at(0)[2]);
		glEnd();
		allVector.push_back(curve3D);

		// cover first & last crossSection
		if(c_i==0 || c_i==numCrossSection-1) {
			glBegin(GL_POLYGON);
			glColor3f(R, G, B);
			for(int j=0; j<curve.size(); j++) {
				glVertex3f(curve3D.at(j)[0], curve3D.at(j)[1], curve3D.at(j)[2]);
			}
			glVertex3f(curve3D.at(0)[0], curve3D.at(0)[1], curve3D.at(0)[2]);
			glEnd();
		}
	}
}
void draw (GLfloat R, GLfloat G, GLfloat B) {
	vector<vector<jhm::position> > allVector;
	drawCrossSection(allVector, R, G, B);

	/////////////////////////////////////
	// interpolateCrossSection_line(allVector,0.0,1.0,0.0);
	interpolateCrossSection_surface(allVector,R,G,B);
}

void drawStripe(GLfloat R1, GLfloat G1, GLfloat B1,
	GLfloat R2, GLfloat G2, GLfloat B2)
{
	vector<vector<jhm::position> > allVector;
	drawCrossSection(allVector, R1, G1, B1);

	/////////////////////////////////////
	// interpolateCrossSection_line(allVector);
	interpolateCrossSection_stripeSurface(allVector,
	R1,G1,B1,R2,G2,B2);
}

void myWireSphere(float r, int nParal, int nMerid){
    float x,y,z,i,j;
    for (j=0;j<M_PI; j+=M_PI/(nParal+1)){
        glBegin(GL_LINE_LOOP);
				glLineWidth(0.0000001);
        y=(float) (r*cos(j));
        for(i=0; i<2*M_PI; i+=M_PI/60){
            x=(float) (r*cos(i)*sin(j));
            z=(float) (r*sin(i)*sin(j));
            glVertex3f(x,y,z);
        }
        glEnd();
    }

    for(j=0; j<M_PI; j+=M_PI/nMerid){
        glBegin(GL_LINE_LOOP);
        for(i=0; i<2*M_PI; i+=M_PI/60){
            x=(float) (r*sin(i)*cos(j));
            y=(float) (r*cos(i));
            z=(float) (r*sin(j)*sin(i));
            glVertex3f(x,y,z);
        }
        glEnd();
    }
}

void display() {
	glClearColor(10./255,105./255,148./255,0.5);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	loadGlobalCoord();

	glColor3f(1.0, 1.0, 1.0);
	myWireSphere(130, 50, 50);
	getDataFile("data.txt");

	drawStripe(1.0, 1.0, 1.0, 1.0, 102./255, 0.0);
	glTranslatef(30.0, 0, 30.0);
	drawStripe(1.0, 1.0, 1.0, 1.0, 102./255, 0.0);
	glTranslatef(30.0, 0, -60.0);
	drawStripe(1.0, 1.0, 1.0, 1.0, 102./255, 0.0);
	glTranslatef(-120.0, 30.0, 0);
	getDataFile("data2.txt");
	glRotatef(90, 0.0, 1.0, 0);
	drawStripe(66./255, 255./255, 49./255, 72./255, 90./255, 255./255);
	glTranslatef(0, 50.0, 50.0);
	drawStripe(66./255, 255./255, 49./255, 72./255, 90./255, 255./255);

	cout << "finish" << endl;
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
	case 49:
		break;

	case 50:
		break;

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

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(400, 400);
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

void getDataFile(string fileName) {

	crossSectionVec.clear();
  ifstream fileopen;
  fileopen.open(fileName.c_str());
  string line;

  getline(fileopen, line); // get curve Type
  if(line.compare("BSPLINE") == 0) {
    curveType = 0;
  } else if (line.compare("CATMULL_ROM") == 0) {
    curveType = 1;
  } else {
    // error
  }

  getline(fileopen, line); // get numCrossSection
  numCrossSection = atoi(line.c_str());

  getline(fileopen, line); // get numControlPoint
  numControlPoint = atoi(line.c_str());

	for(int i = 0; i<numCrossSection; i++) {

		vector<jhm::position> controlPointVec;
		float scale;
		float axis[3];
		float angle;
		float position[3];

		getline(fileopen, line); // \n
		for(int j = 0; j<numControlPoint; j++) { // get control points

			getline(fileopen, line);
			vector<string> v;
			istringstream iss(line);
			for(string s; iss >> s;)
	    v.push_back(s);

			controlPointVec.push_back(
				jhm::position(atof(v.at(0).c_str()), atof(v.at(1).c_str()), 0)
			);
		}

		getline(fileopen, line); // get scailing factor
		scale = atof(line.c_str());

		getline(fileopen, line); // get angle/axis[3]
		cout << line << endl;
		istringstream iss2(line);
		int k = 0;
		for(string s; iss2 >> s;) {
			if(k == 0) {
				angle = atof(s.c_str()) * (M_PI/180);
			}
			else {
				axis[k-1] = atof(s.c_str());
			}
			k++;
		}

		getline(fileopen, line); // get position[3]
		istringstream iss3(line);
		k = 0;
		for(string s; iss3 >> s;) {
			cout << k << "th" << endl;
			position[k] = atof(s.c_str());
			k++;
		}

		crossSectionVec.push_back(CrossSection(controlPointVec, scale, angle, axis, position));
	}
}
