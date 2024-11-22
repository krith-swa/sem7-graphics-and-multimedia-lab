#define GL_SILENCE_DEPRECATION

#include <GL/glut.h>
#include <iostream>
#include <math.h>
using namespace std;

float toRad(float deg) {
	return deg * 3.14159 / 180;
}

float P[4] = { 1, 1, 1, 1 };
float M[4][4] = {
	{1, 0, 0, 0},
	{0, 1, 0, 0},
	{0, 0, 1, 0},
	{0, 0, 0, 1}
};

float angle = 90;

void myInit() {
	glClearColor(0, 0, 0, 1); 
	glMatrixMode(GL_PROJECTION);
	glPointSize(5);
	//glOrtho(-320, 320, -320, 320, -320, 320);
	//glOrtho(-30, 30, -30, 30, -30, 30);
	gluPerspective(45, 1, 1, 100);
	glMatrixMode(GL_MODELVIEW);  
	glLoadIdentity();
	gluLookAt(30, 30, 30, 0, 0, 0, 0, 1, 0); 
	glEnable(GL_DEPTH_TEST); 
	//glRotatef(45, 1, 1, 0);
}

void myInitLighting() {
	glClearColor(0, 0, 0, 1);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	GLfloat lightPosition[] = { 1, 1, 1, 0 };
	GLfloat lightAmbient[] = { 0.2, 0.2, 0.2, 1 };
	GLfloat lightDiffuse[] = { 0.8, 0.8, 0.8, 1 };
	GLfloat lightSpecular[] = { 1, 1, 1, 1 };

	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
	glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecular);

	GLfloat matAmbient[] = { 0, 0.8, 0, 1 };
	GLfloat matDiffuse[] = { 0, 0.8, 0, 1 };
	GLfloat matSpecular[] = { 1, 1, 1, 1 };
	GLfloat shininess = 100;

	glMaterialfv(GL_FRONT, GL_AMBIENT, matAmbient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, matDiffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, matSpecular);
	glMaterialf(GL_FRONT, GL_SHININESS, shininess);

	glPointSize(5);
	glMatrixMode(GL_PROJECTION);
	gluPerspective(45, 1, 1, 100);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(15, 15, 15, 0, 0, 0, 0, 1, 0);
	//gluLookAt(30, 30, 30, 0, 0, 0, 0, 1, 0);
}

void displayPoint(int x, int y, int z) {
	glBegin(GL_POINTS);
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

void transformPoint(float x, float y, float z) {
	P[0] = x; P[1] = y; P[2] = z;
	displayPoint(x, y, z);

	float theta = toRad(angle);
	M[1][1] = cos(theta); M[1][2] = -sin(theta);
	M[2][1] = sin(theta); M[2][2] = cos(theta);

	float newP[4];
	for (int i = 0; i < 4; i++) {
		newP[i] = 0;
		for (int j = 0; j < 4; j++) {
			newP[i] += M[i][j] * P[j];
		}
	}

	for (int k = 0; k < 4; k++) {
		P[k] = newP[k];
	}

	x = P[0]; y = P[1]; z = P[2];
	displayPoint(x, y, z);
}

void plotChart() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	drawAxes();

	//glColor3f(1, 1, 1);
	//displayPoint(0, 0, 0);
	//displayPoint(15, 10, 2);
	//transformPoint(0, 5, 0);

	//glutSolidCube(10);
	//glColor3f(0, 0, 1);
	//glutWireCube(10);

	//glRotatef(90, 1, 0, 0);
	//glutSolidTorus(3, 5, 32, 32);
	//glutSolidCone(5, 5, 100, 1);

	//glRotatef(angle, 0, 1, 0);
	//glutSolidTeapot(5);

	//glutSolidSphere(5, 100, 100);
	//gluSphere(gluNewQuadric(), 2, 50, 50);

	/*
	glPushMatrix();
	glScalef(5, 5, 5);
	glutSolidTetrahedron();
	glPopMatrix();
	*/
	//glTranslatef(0, -5, 0);
	//glutSolidCube(3);

	glutSwapBuffers();
}

void animate() {
	angle += 5;
	if (angle >= 360) {
		angle = 0;
	}
	glutPostRedisplay();
}

int main(int argc, char* argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(640, 640);
	glutCreateWindow("sem practice");

	glutDisplayFunc(plotChart);
	//glutIdleFunc(animate);

	//myInit();
	myInitLighting();
	glutMainLoop();

	return 0;
}