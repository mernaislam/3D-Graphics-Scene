#include <GL/glut.h>
#include<iostream>
#include "draw.h"
GLfloat T = 0;
GLfloat cx = 0, cy = 0, cz = 3;
Drawer drawer =  Drawer();

void display();
void myInit();
void key(unsigned char ch, int x, int y);
void mouse(int button, int state, int x, int y);


int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitWindowSize(900, 700);
	glutInitWindowPosition(100, 100);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutCreateWindow("Graphics Project");
	myInit();
	glutDisplayFunc(display);
	glutKeyboardFunc(key);
	glutMouseFunc(mouse);
	//glutIdleFunc(spin);
	glutMainLoop();
	return 0;
}

void myInit() {
	glClearColor(0.075f, 0.51f, 0.031f, 1.0f);
	glEnable(GL_DEPTH_TEST);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-1, 1, -1, 1, 2, 20);
	glMatrixMode(GL_MODELVIEW);

}

void key(unsigned char ch, int x, int y) { // for camera movements
	switch (ch) {
		case 'x': cx += 0.5; break;
		case 'X': cx -= 0.5; break;
		case 'y': cy += 0.5; break;
		case 'Y': cy -= 0.5; break;
		case 'z': cz -= 0.5; break;
		case 'Z': cz += 0.5; break;
		case 'o': drawer.setOpenDoor(true); break;
		case 'c': drawer.setOpenDoor(false); break;
		case 'O': drawer.setOpenWindow(true); break;
		case 'C': drawer.setOpenWindow(false); break;
		case 'f': drawer.setMoveX(true, 0.5); break;
		case 'b': drawer.setMoveX(false, -0.5); break;
	}
	glutPostRedisplay();
}

void mouse(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		
	}
	else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
		
	}
}

void display() {
	
	// initialize verticies 
	GLfloat triangleVertices[6][3] = {
		{-0.25, -0.25, 0.25},
		{0.25, -0.25, 0.25},
		{0, 0.25, 0.25},

		{-0.25, -0.25, -0.25},
		{0.25, -0.25, -0.25},
		{0, 0.25, -0.25},
	};
	GLfloat cubeVertices[8][3] = {
	   {0.25, 0.25, 0.25},
	   {-0.25, 0.25, 0.25},
	   {-0.25, -0.25, 0.25},
	   {0.25, -0.25, 0.25},

	   {0.25, 0.25, -0.25},
	   {-0.25, 0.25, -0.25},
	   {-0.25, -0.25, -0.25},
	   {0.25, -0.25, -0.25}
	};

	GLfloat doorVertices[4][3] = {
		{0.05, -0.25, 0.26},
		{-0.05, -0.25, 0.26},
		{-0.05, -0.05, 0.26},
		{0.05, -0.05, 0.26}
	};

	GLfloat window[4][3] = {
		{0.1, 0.1, 0.26},
	   {-0.02, 0.1, 0.26},
	   {-0.02, -0.05, 0.26},
	   {0.1, -0.05, 0.26},
	};

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();

	gluLookAt(cx, cy, cz, 0, 0, 0, 0, 1, 0);
	//glRotatef(T, 1, 1, 1); // using built in function
	
	drawer.drawGround();
	drawer.drawBuilding(triangleVertices, cubeVertices, window, doorVertices);
	glPushMatrix();
		glTranslated(0, -0.05, 0);
		drawer.moveBikeFoward();
		drawer.moveBikeBackward();
		drawer.drawBike();
	glPopMatrix();

	drawer.drawCircularRoad();

	glutSwapBuffers();
}
