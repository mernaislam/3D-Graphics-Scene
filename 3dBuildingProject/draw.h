#pragma once
#include <GL/glut.h>
#include<iostream>

class Drawer {
public:
	bool openingDoor = false;
	bool openingWindow = false;
	bool animate = false;
	int forward = -1;
	int prevMove = -1;
	GLfloat bikePosition = 0;
	

	//GLfloat leftWheelRotate = ;

	GLfloat T = 0;
public:
	void setOpenDoor(bool val) {
		openingDoor = val;
	}

	void setOpenWindow(bool val) {
		openingWindow = val;
	}

	void setMoveX(bool f) {
		forward = f;
	}

	void Light(GLfloat col[], GLfloat pos[]) {
		glLightfv(GL_LIGHT0, GL_POSITION, pos);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, col);
	}

	// 3 sides
	void face3(GLfloat a[], GLfloat b[], GLfloat c[]) {
		glBegin(GL_POLYGON);
			glVertex3fv(a);
			glVertex3fv(b);
			glVertex3fv(c);
		glEnd();
	}

	// 4 sides
	void face4(GLfloat a[], GLfloat b[], GLfloat c[], GLfloat d[]) {
		glBegin(GL_POLYGON);
			glVertex3fv(a);
			glVertex3fv(b);
			glVertex3fv(c);
			glVertex3fv(d);
		glEnd();
	}

	void drawRect(GLfloat v[4][3], GLfloat r, GLfloat g, GLfloat b) {
		glColor3f(r, g, b); 
		face4(v[0], v[1], v[2], v[3]);
	}

	void drawCube(GLfloat vertices[8][3]) {
		// front
		glColor3f(0.976, 0.988, 0.671); 
		face4(vertices[0], vertices[1], vertices[2], vertices[3]);

		// back
		glColor3f(0.976, 0.988, 0.671); 
		face4(vertices[4], vertices[5], vertices[6], vertices[7]);

		// top
		glColor3f(1, 1, 1); 
		face4(vertices[0], vertices[4], vertices[5], vertices[1]);

		// left
		glColor3f(0.831, 0.808, 0.49); 
		face4(vertices[5], vertices[1], vertices[2], vertices[6]);

		// bottom
		glColor3f(1, 1, 1); 
		face4(vertices[3], vertices[7], vertices[6], vertices[2]);

		// right
		glColor3f(0.831, 0.808, 0.49); 
		face4(vertices[0], vertices[4], vertices[7], vertices[3]);
	}

	void drawTriangle(GLfloat vertices[6][3]) {
		// front
		glColor3f(1, 0.992, 0.867);  
		face3(vertices[0], vertices[1], vertices[2]);

		// back
		glColor3f(1, 0.992, 0.867); 
		face3(vertices[3], vertices[4], vertices[5]);

		// right
		glColor3f(0.929, 0.918, 0.765); 
		face4(vertices[2], vertices[5], vertices[4], vertices[1]);

		// left
		glColor3f(0.929, 0.918, 0.765); 
		face4(vertices[2], vertices[5], vertices[3], vertices[0]);

		// bottom
		glColor3f(0.859, 0.851, 0.706); 
		face4(vertices[0], vertices[1], vertices[4], vertices[3]);
	}

	void drawBuilding(GLfloat triangleVertices[6][3], GLfloat cubeVertices[8][3],
		GLfloat window[4][3], GLfloat doorVertices[4][3]) {

		// draw building roof
		glPushMatrix();
			glTranslatef(0, 0.19, 0);
			glScalef(1.5, 1, 1);
			drawTriangle(triangleVertices);
		glPopMatrix();

		// lower right cube
		glPushMatrix();
			glTranslatef(0.12, -0.62, 0);
			glScalef(0.75, 0.75, 1);
			drawCube(cubeVertices);
		glPopMatrix();

		// lower left cube
		glPushMatrix();
			glTranslatef(-0.12, -0.62, 0);
			glScalef(0.75, 0.75, 1);
			drawCube(cubeVertices);
		glPopMatrix();
		
		// upper right cube
		glPushMatrix();
			glTranslatef(0.12, -0.25, 0);
			glScalef(0.75, 0.75, 1);
			drawCube(cubeVertices);
		glPopMatrix();

		// upper left cube
		glPushMatrix();
			glTranslatef(-0.12, -0.25, 0);
			glScalef(0.75, 0.75, 1);
			drawCube(cubeVertices);
		glPopMatrix();

		// draw left uppper window
		glPushMatrix();
			glTranslatef(-0.26, -0.2, 0);
			openWindow();
			drawRect(window, 0.757, 0.898, 0.961);
		glPopMatrix();

		// draw behind left upper window
		glPushMatrix();
			glTranslatef(-0.26, -0.2, 0);
			drawRect(window, 0, 0, 0);
		glPopMatrix();

		// draw left lower window
		glPushMatrix();
			glTranslatef(-0.26, -0.42, 0);
			openWindow();
			drawRect(window, 0.757, 0.898, 0.961);
		glPopMatrix();

		// draw behind left lower window
		glPushMatrix();
			glTranslatef(-0.26, -0.42, 0);
			drawRect(window, 0, 0, 0);
		glPopMatrix();

		// draw right lower window
		glPushMatrix();
			glTranslatef(0.18, -0.42, 0);
			openWindow();
			drawRect(window, 0.757, 0.898, 0.961);
		glPopMatrix();

		// draw behind left upper window
		glPushMatrix();
			glTranslatef(0.18, -0.42, 0);
			drawRect(window, 0, 0, 0);
		glPopMatrix();

		// draw left upper window
		glPushMatrix();
			glTranslatef(0.18, -0.2, 0);
			openWindow();
			drawRect(window, 0.757, 0.898, 0.961);
		glPopMatrix();

		// draw behind left upper window
		glPushMatrix();
		glTranslatef(0.18, -0.2, 0);
		drawRect(window, 0, 0, 0);
		glPopMatrix();

		// draw door
		glPushMatrix();
			glTranslatef(0, -0.43, 0);
			glScalef(1.5, 1.5, 1);
			openDoor();
			drawRect(doorVertices, 0.4, 0.188, 0);
		glPopMatrix();

		/*GLfloat doorVertices[4][3] = {
		{0.05, -0.25, 0.26},
		{-0.05, -0.25, 0.26},
		{-0.05, -0.05, 0.26},
		{0.05, -0.05, 0.26}
		};*/

		// draw behind door
		glPushMatrix();
			glTranslatef(0, -0.43, 0);
			glScalef(1.5, 1.5, 1);
			drawRect(doorVertices, 0, 0, 0);
		glPopMatrix();

	}

	void drawGround() {
		// draw the ground
		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);

		glPushMatrix();
			GLfloat pos[] = { 0, 1, 0, 0.5 };
			GLfloat Gray[] = { 0.5, 0.5, 0.5 ,1 };
			Light(Gray, pos);
			glTranslatef(0, -0.85, 0);
			glColor3f(0.545, 0.561, 0.545);
			glBegin(GL_QUADS);
			glVertex3f(-10, 0, -10); // Bottom-left
			glVertex3f(10.0, 0.0, -10.0);  // Bottom-right
			glVertex3f(10.0, 0.0, 10.0);   // Top-right
			glVertex3f(-10.0, 0.0, 10.0);  // Top-left
			glEnd();
		glPopMatrix();

		glDisable(GL_LIGHTING);
		glEnable(GL_LIGHT0);
	}

	void openDoor() {
		if (openingDoor) {
			glTranslatef(-0.155, 0, 0.43);
			glRotatef(120.0f, 0, 1, 0);
		}
	}

	void openWindow() {
		if (openingWindow) {
			glTranslatef(-0.1, 0, 0.43);
			glRotatef(120.0f, 0, 1, 0);
		}
	}
	
	void moveBikeFoward() {
		if (forward == 1) {
			bikePosition += 0.2;
			 forward = -1;
		}
	}
	
	void moveBikeBackward() {
		
		if (forward == 0) {
			bikePosition -= 0.2;
			forward = -1;
		
		}
	}

	void drawBike() {
		// 3aglteen el odam
		//int temp = forward;
		glPushMatrix();
			glRotatef(T, 0, 0.5f, 0);
			glTranslatef(0.5, -0.7, 0.8);
			drawCircle(0.0f, 0.0f, 0.1f, 100);
		glPopMatrix();
		
		glPushMatrix();
			glRotatef(T, 0, 0.5f, 0);
			glTranslatef(0.5, -0.7, 0.79);
			drawCircle(0.0f, 0.0f, 0.1f, 100);
		glPopMatrix();
		

		// 3amood el dreksyon
		glPushMatrix();
			glRotatef(T, 0, 0.5f, 0);
			glTranslatef(0.5, -0.6, 0.8);
			glScalef(0.5, 3, 0.2);
			glutSolidCube(0.1);
		glPopMatrix();

		// el dreksyon nafso
		glPushMatrix();
			glRotatef(T, 0, 0.5f, 0);
			glTranslatef(0.5, -0.45, 0.8);
			glScalef(0.5, 0.5, 3);
			glutSolidCube(0.1);
		glPopMatrix();

		// el satr elly fel nos
		glPushMatrix();
			glRotatef(T, 0, 0.5f, 0);
			glTranslatef(0.25, -0.7, 0.8);
			glScalef(4, 0.5, 0.5);
			glutSolidCube(0.1);
		glPopMatrix();

		// 3aglteen elly wara
		glPushMatrix();
			glRotatef(T, 0, 0.5f, 0);
			glTranslatef(0, -0.7, 0.8);
			drawCircle(0.0f, 0.0f, 0.1f, 100);
		glPopMatrix();

		glPushMatrix();
			glRotatef(T, 0, 0.5f, 0);
			glTranslatef(0, -0.7, 0.79);
			drawCircle(0.0f, 0.0f, 0.1f, 100);
		glPopMatrix();

		if(animate)
			move();
	}

	void drawCircularRoad() {
		std::cout << "new Road";
		glTranslatef(0, -0.79999999, 0);
		glRotatef(90, 6, 0.0f, 0.0);
		float radius1 = abs(bikePosition) + 1;
		float radius2 = abs(bikePosition) + 0.8;
		std::cout << radius1 << ' ' << radius2 << std::endl;
		drawOutlineCircle(0, 0, radius1, 100);
		drawOutlineCircle(0, 0, radius2, 100);
	}
	
	void drawCircle(float cx, float cy, float r, int numSegments) {
		glBegin(GL_TRIANGLE_FAN);
		for (int i = 0; i < numSegments; ++i) {
			float theta = 2.0f * 3.14 * static_cast<float>(i) / static_cast<float>(numSegments);
			float x = r * cosf(theta);
			float y = r * sinf(theta);
			glVertex2f(x + cx, y + cy);
		}
		glEnd();
	}

	void drawOutlineCircle(float cx, float cy, float r, int numSegments) {
		glBegin(GL_LINE_LOOP);
		for (int i = 0; i < numSegments; ++i) {
			float theta = 2.0f * 3.14 * static_cast<float>(i) / static_cast<float>(numSegments);
			float x = r * cosf(theta);
			float y = r * sinf(theta);
			glVertex2f(x + cx, y + cy);
		}
		glEnd();
	}
	
	void move() {
		
		T = T + 0.1;
		if (T > 360) {
			T = 0;
		}
		glutPostRedisplay();
		
	}

	
	
};
