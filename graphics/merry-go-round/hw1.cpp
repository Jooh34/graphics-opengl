#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/freeglut.h>
#include <iostream>
#include <cmath>
#include <algorithm>

GLdouble rotMatrix[16] =
{
	1, 0, 0, 0,
	0, 1, 0, 0,
	0, 0, 1, 0,
	0, 0, 0, 1
};

GLdouble rotMatrixSave[16] =
{
	1, 0, 0, 0,
	0, 1, 0, 0,
	0, 0, 1, 0,
	0, 0, 0, 1
};

float TRACKBALL_RADIUS = 10.0;
// should manage float overflow if Radius is too long

float RATIO_WV = 5.0;
// Aspect Ratio

void crossProduct(float v_1[3], float v_2[3], float v_3[3]);
float normalize(float v[3]);
void crossProduct(float v_1[3], float v_2[3], float v_3[3]);
float dotProduct(float v_1[3], float v_2[3]);
void normalization (float v[3]);

// ------------------------------
// variabless for animation
float frameRot;
float framespeed = 0.5;

float firstHorse = 15;
float secondHorse = 20;
float thirdHorse = 25;
float fourthHorse = 30;

float legspeed = 1;
// ------------------------------

// ------------------------------
// variables for views
int width, height;
GLfloat mousePosX, mousePosY;

bool controlButton = false;
bool leftButton = false;
float zoomRatio = 1;
bool isTranslated = false;
// ------------------------------

float eye[3] = { 0.0f, 0.0f, 200.0f };
float ori[3] = { 0.0f, 0.0f, 0.0f };
float look[3] = { 0.0f, 1.0f, 0.0f};
float rot[3] = { 0.0f, 0.0f, 0.0f };

void getVectorOnTrackball(int x, int y, int w, int h, float v[3])
{
	v[0] = RATIO_WV *(2.0*x -w)/w;
	v[1] = RATIO_WV *(h-2.0*y)/h;

	float d = v[0]*v[0] + v[1]*v[1];
	if(d > pow(TRACKBALL_RADIUS,2.0))
		d = pow(TRACKBALL_RADIUS,2.0); // if point is out of circle

	if(pow(TRACKBALL_RADIUS,2.0)-d > 0)
		v[2] =  sqrt(pow(TRACKBALL_RADIUS,2.0)-d);
	else v[2] = 0;

}

void getAxisAngle(int a[2], int b[2], float axis[3], float &angle)
{
	float v_1[3]; float v_2[3];
	getVectorOnTrackball(a[0],a[1],glutGet(GLUT_WINDOW_WIDTH),glutGet(GLUT_WINDOW_HEIGHT),v_1);
	getVectorOnTrackball(b[0],b[1],glutGet(GLUT_WINDOW_WIDTH),glutGet(GLUT_WINDOW_HEIGHT),v_2);
	normalization(v_2);
	normalization(v_1);

	crossProduct(v_1, v_2, axis);
	normalization(axis);

	float cosine = dotProduct(v_1,v_2)/(normalize(v_1) * normalize(v_2));

	// to avoid cosine or 1-cosine^2 approximate to 0 (it occurs really really rarely)
	if(cosine == 0) angle = atan2(0.00000001,0.99999999);
	else if((1-cosine*cosine) ==0) angle = atan2(0.99999999, 0.00000001);
	else angle = atan2(cosine,1-cosine*cosine);

}

float normalize(float v[3]) {
	return sqrt(v[0]*v[0] + v[1]*v[1] + v[2]*v[2]);
}

float dotProduct(float v_1[3], float v_2[3]) {
	return v_1[0]*v_2[0] + v_1[1]*v_2[1] + v_1[2]*v_2[2];
}

void crossProduct(float v_1[3], float v_2[3], float v_3[3])
{
	v_3[0] = v_1[1]*v_2[2] - v_1[2]*v_2[1];
	v_3[1] = v_1[2]*v_2[0] - v_1[0]*v_2[2];
	v_3[2] = v_1[0]*v_2[1] - v_1[1]*v_2[0];
}

void normalization (float v[3]) {
	v[0] = v[0] / normalize(v);
	v[1] = v[1] / normalize(v);
	v[2] = v[2] / normalize(v);
}

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

			if(isTranslated) {
				// for(int i=0; i<16; i++) { // load saved orientation
				// 	rotMatrix[i] = rotMatrixSave[i];
				// }
				isTranslated = false;
			}

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
void glutMouse(int button, int state, int x, int y)
{
	switch ( button )
	{
		case GLUT_LEFT_BUTTON:
			if (controlButton) { // translation
					if(state == GLUT_DOWN) {
						if(!isTranslated) {
							isTranslated = true;
							for (int i=0; i<16; i++) {
								rotMatrixSave[i] = rotMatrix[i];
							}
						}


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

//------------------------------------------------------------------------
// Function that Draws Something
//------------------------------------------------------------------------
static int RED = 0;
static int WHITE = 1;

void color_change(int &color) {
	if(color == RED) {
		color = WHITE;
		glColor3ub(255,255,255);
	}
	else if(color == WHITE) {
		color = RED;
		glColor3ub(220,0,0);
	}
}

void draw_roof(GLfloat radius,
               GLfloat height)
{
	GLfloat x              = 0.0;
    GLfloat z              = 0.0;
    int angle          = 0;
    int angle_stepsize = 30;

    glColor3ub(220,0,0);
    int color = RED;
    glBegin(GL_TRIANGLES);
	glVertex3f(0, height , 0);
	glVertex3f(radius, 0.0 , z);
    angle = 30;

	    while( angle <= 360) {

	        x = radius * cos(2*M_PI*angle/360);
	        z = radius * sin(2*M_PI*angle/360);

	        glVertex3f(x, 0.0 , z);
	        angle = angle + angle_stepsize;

	        glEnd();
	        color_change(color);
	        glBegin(GL_TRIANGLES);
	        glVertex3f(x, 0.0 , z);
			glVertex3f(0, height , 0);
	    }


    glVertex3f(radius, 0.0, 0.0);
    glEnd();

    x = 0;
    z = 0;
    /** Draw the Line on bottom of corn */
    glColor3ub(0,0,0);
    glBegin(GL_LINE_STRIP);
    glVertex3f(radius, 0.0, z);
    angle = 0;
        while( angle <= 360 ) {
            x = radius * cos(2*M_PI*angle/360);
	        z = radius * sin(2*M_PI*angle/360);
            glVertex3f(x, 0.0 , z);
            angle = angle + angle_stepsize;
        }
        glVertex3f(radius, 0.0, z);
    glEnd();
}

void draw_cylinder(GLfloat radius,
                   GLfloat height,
                   GLubyte R,
                   GLubyte G,
                   GLubyte B)
{
    GLfloat x              = 0.0;
    GLfloat z              = 0.0;
    GLfloat angle          = 0.0;
    GLfloat angle_stepsize = 0.1;

    /** Draw the tube */
    glColor3ub(R-40,G-40,B-40);
    glBegin(GL_QUAD_STRIP);
    angle = 0.0;
        while( angle < 2*M_PI ) {
            x = radius * cos(angle);
            z = radius * sin(angle);
            glVertex3f(x, height , z);
            glVertex3f(x, 0.0 , z);
            angle = angle + angle_stepsize;
        }
        glVertex3f(radius, height, 0.0);
        glVertex3f(radius, 0.0, 0.0);
    glEnd();

    /** Draw the circle on bottom of cylinder */
    glColor3ub(R,G,B);
    glBegin(GL_POLYGON);
    angle = 0.0;
        while( angle < 2*M_PI ) {
            x = radius * cos(angle);
            z = radius * sin(angle);
            glVertex3f(x, 0.0 , z);
            angle = angle + angle_stepsize;
        }
        glVertex3f(radius, 0.0, z);
    glEnd();


    /** Draw the circle on top of cylinder */
    glColor3ub(R,G,B);
    glBegin(GL_POLYGON);
    angle = 0.0;
        while( angle < 2*M_PI ) {
            x = radius * cos(angle);
            z = radius * sin(angle);
            glVertex3f(x, height , z);
            angle = angle + angle_stepsize;
        }
        glVertex3f(radius, height, z);
    glEnd();


}

void draw_poll() {
	draw_cylinder(1, 45, 255, 255, 255);
}

void drawFrame() {

	glTranslatef(0.0,20,0.0);

	draw_roof(50, 30); // roof
	glTranslatef(0.0,-40.0,0.0);

	draw_cylinder(50, 2, 255, 127, 80); // bottom one
	draw_cylinder(2, 50, 255, 255, 255); // poll
}

void draw_cuboid(GLfloat x,
                   GLfloat y,
                   GLfloat z,
                   GLubyte R,
                   GLubyte G,
                   GLubyte B)
{
	glColor3ub(R,G,B);
	glBegin(GL_QUADS);

    //Front
    glNormal3f(0.0f, 0.0f, 1.0f);
    glVertex3f(-x, -y, z);
    glVertex3f(x, -y, z);
    glVertex3f(x, y, z);
    glVertex3f(-x, y, z);

    //Right
    glColor3ub(R+20,G+20,B+20);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(x, -y, -z);
    glVertex3f(x, y, -z);
    glVertex3f(x, y, z);
    glVertex3f(x, -y, z);

    //Back
    glColor3ub(R,G,B);
    glNormal3f(0.0f, 0.0f, -1.0f);
    glVertex3f(-x, -y, -z);
    glVertex3f(-x, y, -z);
    glVertex3f(x, y, -z);
    glVertex3f(x, -y, -z);

    //Left
    glColor3ub(R+20,G+20,B+20);
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(-x, -y, -z);
    glVertex3f(-x, -y, z);
    glVertex3f(-x, y, z);
    glVertex3f(-x, y, -z);

    //Top
    glColor3ub(R,G,B);
    glNormal3f(0.0f, 1.0f, 0.0f);
    glVertex3f(-x, y, -z);
    glVertex3f(-x, y, z);
    glVertex3f(x, y, z);
    glVertex3f(x, y, -z);

    //Bottom
    glNormal3f(0.0f, -1.0f, 0.0f);
    glVertex3f(-x, -y, -z);
    glVertex3f(-x, -y, z);
    glVertex3f(x, -y, z);
    glVertex3f(x, -y, -z);
    glEnd();
}

void draw_cuboid_ordiedge (GLfloat x,
                   GLfloat y,
                   GLfloat z,
                   GLubyte R,
                   GLubyte G,
                   GLubyte B
                   )
{
	glColor3ub(R,G,B);
	glBegin(GL_QUADS);

    //Front
    glNormal3f(0.0f, 0.0f, 1.0f);
    glVertex3f(0, -y, z);
    glVertex3f(x, -y, z);
    glVertex3f(x, y, z);
    glVertex3f(0, y, z);

    //Right
    glColor3ub(R+20,G+20,B+20);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(x, -y, -z);
    glVertex3f(x, y, -z);
    glVertex3f(x, y, z);
    glVertex3f(x, -y, z);

    //Back
    glColor3ub(R,G,B);
    glNormal3f(0.0f, 0.0f, -1.0f);
    glVertex3f(0, -y, -z);
    glVertex3f(0, y, -z);
    glVertex3f(x, y, -z);
    glVertex3f(x, -y, -z);

    //Left
    glColor3ub(R+20,G+20,B+20);
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(0, -y, -z);
    glVertex3f(0, -y, z);
    glVertex3f(0, y, z);
    glVertex3f(0, y, -z);

    //Top
    glColor3ub(R,G,B);
    glNormal3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0, y, -z);
    glVertex3f(0, y, z);
    glVertex3f(x, y, z);
    glVertex3f(x, y, -z);

    //Bottom
    glNormal3f(0.0f, -1.0f, 0.0f);
    glVertex3f(0, -y, -z);
    glVertex3f(0, -y, z);
    glVertex3f(x, -y, z);
    glVertex3f(x, -y, -z);
    glEnd();
}

float front_upperleg1 = -80.0;
float front_lowerleg1 = -30.0;
float front_upperleg2 = -60.0;
float front_lowerleg2 = -10.0;
void draw_frontlegs() {

	glTranslatef(0.0f, 0.0f, 2.0f);
	glRotatef(front_upperleg1, 0.0, 0.0, 1.0);

	glPushMatrix();
	{
		draw_cuboid_ordiedge(5.0f, 0.8f, 0.8f, 139,69,19); // front_upperleg

		glTranslatef(5.0f, 0.0, 0.0);
		glRotatef(front_lowerleg1, 0.0, 0.0, 1.0);

		glPushMatrix();
		{
			draw_cuboid_ordiedge(5.0f, 0.8f, 0.8f, 139,69,19); // front_lowerleg
		}
		glPopMatrix();

		glRotatef(-front_lowerleg1, 0.0, 0.0, 1.0);
		glTranslatef(-5.0f, 0.0, 0.0);

	}
	glPopMatrix();

	glRotatef(-front_upperleg1, 0.0, 0.0, 1.0);
	glTranslatef(0.0f, 0.0f, -2.0f);

	glTranslatef(0.0f, 0.0f, -2.0f);
	glRotatef(front_upperleg2, 0.0, 0.0, 1.0);

	glPushMatrix();
	{
		draw_cuboid_ordiedge(5.0f, 0.8f, 0.8f, 139,69,19); // front_upperleg

		glTranslatef(5.0f, 0.0, 0.0);
		glRotatef(front_lowerleg2, 0.0, 0.0, 1.0);

		glPushMatrix();
		{
			draw_cuboid_ordiedge(5.0f, 0.8f, 0.8f, 139,69,19); // front_lowerleg
		}
		glPopMatrix();

		glRotatef(-front_lowerleg2, 0.0, 0.0, 1.0);
		glTranslatef(-5.0f, 0.0, 0.0);

	}
	glPopMatrix();

	glRotatef(-front_upperleg2, 0.0, 0.0, 1.0);
	glTranslatef(0.0f, 0.0f, 2.0f);

}

float back_upperleg1 = -80.0;
float back_lowerleg1 = -30.0;
float back_upperleg2 = -60.0;
float back_lowerleg2 = -10.0;
void draw_backlegs() {

	glTranslatef(0.0f, 0.0f, 2.0f);
	glRotatef(back_upperleg1, 0.0, 0.0, 1.0);

	glPushMatrix();
	{
		draw_cuboid_ordiedge(5.0f, 0.8f, 0.8f, 139,69,19); // back_upperleg

		glTranslatef(5.0f, 0.0, 0.0);
		glRotatef(back_lowerleg1, 0.0, 0.0, 1.0);

		glPushMatrix();
		{
			draw_cuboid_ordiedge(5.0f, 0.8f, 0.8f, 139,69,19); // back_lowerleg
		}
		glPopMatrix();

		glRotatef(-back_lowerleg1, 0.0, 0.0, 1.0);
		glTranslatef(-5.0f, 0.0, 0.0);

	}
	glPopMatrix();

	glRotatef(-back_upperleg1, 0.0, 0.0, 1.0);
	glTranslatef(0.0f, 0.0f, -2.0f);

	glTranslatef(0.0f, 0.0f, -2.0f);
	glRotatef(back_upperleg2, 0.0, 0.0, 1.0);

	glPushMatrix();
	{
		draw_cuboid_ordiedge(5.0f, 0.8f, 0.8f, 139,69,19); // back_upperleg

		glTranslatef(5.0f, 0.0, 0.0);
		glRotatef(back_lowerleg2, 0.0, 0.0, 1.0);

		glPushMatrix();
		{
			draw_cuboid_ordiedge(5.0f, 0.8f, 0.8f, 139,69,19); // back_lowerleg
		}
		glPopMatrix();

		glRotatef(-back_lowerleg2, 0.0, 0.0, 1.0);
		glTranslatef(-5.0f, 0.0, 0.0);

	}
	glPopMatrix();

	glRotatef(-back_upperleg2, 0.0, 0.0, 1.0);
	glTranslatef(0.0f, 0.0f, 2.0f);
}

float head = 60.0;

void draw_horse() {

	draw_cuboid(6.0f, 3.0f, 3.0f, 139,69,19); // body

	glTranslatef(5.0f, 2.0f, 0.0f);
	glRotatef(head, 0.0, 0.0, 1.0);

		glPushMatrix();
		{
			draw_cuboid_ordiedge(6.0f, 1.5f, 2.0f, 139,69,19); // neck

			glTranslatef(6.0f, -2.5f, 0.0f);
			glRotatef(-90.0, 0.0, 0.0, 1.0);
				draw_cuboid(3.0f, 1.5f, 2.0f, 139,69,19); // head

			glRotatef(90.0, 0.0, 0.0, 1.0);
			glTranslatef(-6.0f, 2.5f, 0.0f);
		}
		glPopMatrix();

	glRotatef(-head, 0.0, 0.0, 1.0); //ordi back
	glTranslatef(-5.0f, -2.0f, 0.0f);

	glTranslatef(5.0f, -2.0f, 0.0f);
	draw_frontlegs();
	glTranslatef(-5.0f, 2.0f, 0.0f);

	glTranslatef(-5.0f, -2.0f, 0.0f);
	glRotatef(180.0, 0.0, 1.0, 0.0);
	draw_backlegs();
	glRotatef(-180.0, 0.0, 1.0, 0.0);
	glTranslatef(5.0f, 2.0f, 0.0f);

}

float dir1 = 0.0;
float dir2 = 90.0;
float dir3 = -180.0;
float dir4 = 270.0;

void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	loadGlobalCoord();


	glRotatef(frameRot,0.0, 1.0, 0.0);

	glPushMatrix();
	{
		drawFrame();

		glTranslatef(0.0,0.0,40.0);
		draw_poll();

		glPushMatrix();
		{
			glRotatef(dir1, 0.0, 1.0, 0.0);
			glTranslatef(0.0,firstHorse,0.0); // horse coordi.
			draw_horse(); // First horse
			glTranslatef(0.0,-firstHorse,0.0); // return
			glRotatef(-dir1, 0.0, 1.0, 0.0);
		}
		glPopMatrix();

		glTranslatef(40.0,0.0,-40.0);
		draw_poll();

		glPushMatrix();
		{
			glRotatef(dir2, 0.0, 1.0, 0.0);
			glTranslatef(0.0,secondHorse,0.0); // horse coordi.

			draw_horse(); // Second horse

			glTranslatef(0.0,-secondHorse,0.0); // return
			glRotatef(-dir2, 0.0, 1.0, 0.0);
		}
		glPopMatrix();

		glTranslatef(-40.0,0.0,-40.0);
		draw_poll();

		glPushMatrix();
		{
			glRotatef(dir3, 0.0, 1.0, 0.0);
			glTranslatef(0.0,thirdHorse,0.0); // horse coordi.
			draw_horse(); // Third horse
			glTranslatef(0.0,-thirdHorse,0.0); // return
			glRotatef(-dir3, 0.0, 1.0, 0.0);
		}
		glPopMatrix();

		glTranslatef(-40.0,0.0,40.0);
		draw_poll();

		glPushMatrix();
		{
			glRotatef(dir4, 0.0, 1.0, 0.0);
			glTranslatef(0.0,fourthHorse,0.0); // horse coordi.
			draw_horse(); // Fourth horse
			glTranslatef(0.0,-fourthHorse,0.0); // return
			glRotatef(-dir4, 0.0, 1.0, 0.0);
		}
		glPopMatrix();

	}
	glPopMatrix();

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
		framespeed += 0.1;
		break;

	case 50:
		framespeed -= 0.1;
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
void movingHorse(float &horse, float speed, bool &direction) {
	if(direction)
	{
		horse += speed;
		if(horse > 30.0) direction = !direction;
	}

	else
	{
		horse -= speed;
		if(horse < 15.0) direction = !direction;
	}
}

void rotateHorse(float &dir, float stepsize) {
	dir = dir + stepsize;
}

void movingUpperleg(float &leg, float speed, bool &direction) {
	if(direction)
	{
		leg += speed;
		if(leg > -60.0) direction = !direction;
	}

	else
	{
		leg -= speed;
		if(leg < -80.0) direction = !direction;
	}
}

void movingLowerleg(float &leg, float speed, bool &direction) {
	if(direction)
	{
		leg += speed;
		if(leg > -0.0) direction = !direction;
	}

	else
	{
		leg -= speed;
		if(leg < -40.0) direction = !direction;
	}
}

void movingHead(float &head, float speed, bool &direction) {
	if(direction)
	{
		head += speed;
		if(head > 70.0) direction = !direction;
	}

	else
	{
		head -= speed;
		if(head < 50.0) direction = !direction;
	}
}

bool firstHorseDir = false;
bool secondHorseDir = true;
bool thirdHorseDir = false;
bool fourthHorseDir = true;

unsigned timeStep = 30;

bool front_upperleg1D = true;
bool front_upperleg2D = true;
bool front_lowerleg1D = true;
bool front_lowerleg2D = true;

bool back_upperleg1D = true;
bool back_upperleg2D = true;
bool back_lowerleg1D = true;
bool back_lowerleg2D = true;

bool headDir = true;

void Timer(int unused)
{
	frameRot += framespeed;
	movingHorse(firstHorse, 0.3, firstHorseDir);
	movingHorse(secondHorse, 0.3, secondHorseDir);
	movingHorse(thirdHorse, 0.3, thirdHorseDir);
	movingHorse(fourthHorse, 0.3, fourthHorseDir);

	movingUpperleg(front_upperleg1, legspeed, front_upperleg1D);
	movingUpperleg(front_upperleg2, legspeed, front_upperleg2D);
	movingUpperleg(back_upperleg1, legspeed, back_upperleg1D);
	movingUpperleg(back_upperleg2, legspeed, back_upperleg2D);

	movingLowerleg(front_lowerleg1, legspeed+1, front_lowerleg1D);
	movingLowerleg(front_lowerleg2, legspeed+1, front_lowerleg2D);
	movingLowerleg(back_lowerleg1, legspeed+1, back_lowerleg1D);
	movingLowerleg(back_lowerleg2, legspeed+1, back_lowerleg2D);

	movingHead(head, 1, headDir);

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
