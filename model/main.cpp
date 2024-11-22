#define GL_SILENCE_DEPRECATION

#include <GL/glut.h>
#include <iostream>

void myInit() {
	glClearColor(0, 0, 0, 0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//glOrtho(-320, 320, -320, 320, -320, 320);
	gluPerspective(45.0, 1.0, 1.0, 100);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(30, 30, 30, 0, 0, 0, 0, 1, 0);
	glEnable(GL_DEPTH_TEST);
}

void displayPoint(int x, int y, int z) {
	glBegin(GL_POINT);
	glVertex3d(x, y, z);
	glEnd();
}

void displayLine(int x1, int y1, int z1, int x2, int y2, int z2) {
	glBegin(GL_LINES);
	glVertex3d(x1, y1, z1);
	glVertex3d(x2, y2, z2);
	glEnd();
}

void drawAxes() {
	glColor3f(1, 0.4, 1);
	glBegin(GL_LINES);
	displayLine(-320, 0, 0, 320, 0, 0);
	displayLine(0, -320, 0, 0, 320, 0);
	displayLine(0, 0, -320, 0, 0, 320);
	glEnd();
}

void drawCube(int size = 1) {
	glBegin(GL_QUADS);

	glVertex3d(size, size, size);
	glVertex3d(size, size, -size);
	glVertex3d(-size, size, -size);
	glVertex3d(-size, size, size);

	glVertex3d(size, -size, size);
	glVertex3d(size, -size, -size);
	glVertex3d(-size, -size, -size);
	glVertex3d(-size, -size, size);

	glVertex3d(size, size, size);
	glVertex3d(size, size, -size);
	glVertex3d(size, -size, -size);
	glVertex3d(size, -size, size);

	glVertex3d(-size, size, size);
	glVertex3d(-size, size, -size);
	glVertex3d(-size, -size, -size);
	glVertex3d(-size, -size, size);

	glVertex3d(size, size, size);
	glVertex3d(size, -size, size);
	glVertex3d(-size, -size, size);
	glVertex3d(-size, size, size);

	glVertex3d(size, size, -size);
	glVertex3d(size, -size, -size);
	glVertex3d(-size, -size, -size);
	glVertex3d(-size, size, -size);

	glEnd();
}

void drawCubeFrame(int size) {
	glPushMatrix();
	glutWireCube(size);
	glPopMatrix();
}

void drawCubeSolid(int size) {
	glPushMatrix();
	glutSolidCube(size);
	glPopMatrix();
}

void drawSphere(float radius) {
	gluSphere(gluNewQuadric(), radius, 50, 50);
}

void plotWindow() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	drawAxes();

	glTranslatef(1.5f, 0.0f, -15.0f);
	//glRotatef(45, 1, 1, 0);

	glColor3f(1, 1, 1);
	//glScalef(0.5, 1, 0.5);
	drawCube(10/2); 
	//drawCubeSolid(10);

	glColor3f(0, 1, 0);
	drawCubeFrame(10);

	glTranslatef(-10.0f, 10.0f, 10.0f);

	glColor3f(0, 0, 1);
	drawSphere(5);

	glFlush();
}

int main(int argc, char* argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(640, 640);
	glutCreateWindow("Window name");

	glutDisplayFunc(plotWindow);
	
	myInit();
	glutMainLoop();

	return 0;
}