#define GL_SILENCE_DEPRECATION

#include<GL/glut.h>
#include<iostream>
#include<math.h>
using namespace std;

float* G1 = new float[3];
float* G2 = new float[3];
float* G3 = new float[3];

float xwmax = 1280, ywmax = 960;
float xvmax = 640, yvmax = 480;

void myInit_win1(float x, float y) {
	glClearColor(0.6, 0.2, 1.0, 0.0); // violet
	glColor3f(0.0f, 0.0f, 0.5f); //dark blue
	glMatrixMode(GL_PROJECTION);
	glLineWidth(2);
	glLoadIdentity();
	gluOrtho2D(0.0, x, 0.0, y);
}

void myInit_win2(float x, float y) {
	glClearColor(0.0, 0.0, 0.5, 0.0); // dark blue
	glColor3f(0.5f, 0.3f, 0.5f); //
	glMatrixMode(GL_PROJECTION);
	glLineWidth(2);
	glLoadIdentity();
	gluOrtho2D(0.0, x, 0.0, y);
}

void displayLine(int x1, int y1, int x2, int y2, int xc, int yc) {
	glBegin(GL_LINES);
	glVertex2d(x1 + xc, y1 + yc);
	glVertex2d(x2 + xc, y2 + yc);
	glEnd();
}

void displayTriangle(int x1, int y1, int x2, int y2, int x3, int y3, int xc, int yc) {
	glBegin(GL_TRIANGLES);
	glVertex2d(x1 + xc, y1 + yc);
	glVertex2d(x2 + xc, y2 + yc);
	glVertex2d(x3 + xc, y3 + yc);
	glEnd();
}

void displayLineWindow(int x1, int y1, int x2, int y2) {
	displayLine(x1, y1, x2, y2, xwmax/2, ywmax/2);
}

void displayLineViewport(int x1, int y1, int x2, int y2) {
	displayLine(x1, y1, x2, y2, xvmax/2, yvmax/2);
}

void displayTriangleWindow(int x1, int y1, int x2, int y2, int x3, int y3) {
	displayTriangle(x1, y1, x2, y2, x3, y3, xwmax/2, ywmax/2);
}

void displayTriangleViewport(int x1, int y1, int x2, int y2, int x3, int y3) {
	displayTriangle(x1, y1, x2, y2, x3, y3, xvmax/2, yvmax/2);
}

void displayHomogeneousTriangle(float* p1, float* p2, float* p3) {
	float x1 = *(p1 + 0);
	float y1 = *(p1 + 1);
	float x2 = *(p2 + 0);
	float y2 = *(p2 + 1);
	float x3 = *(p3 + 0);
	float y3 = *(p3 + 1);

	displayTriangleViewport(x1, y1, x2, y2, x3, y3);
}

void printMatrix(float* arr, int m, int n)
{
	int i, j;
	for (i = 0; i < m; i++) {
		for (j = 0; j < n; j++)
			cout << *((arr + i * n) + j) << " ";
		cout << endl;
	}
}

float* mulMatrix(float* a, int m1, int n1, float* b, int m2, int n2) {
	if (n1 != m2) {
		cout << "Multiplication Input Error" << endl;
		return NULL;
	}

	float* res = new float[m1 * n2];
	for (int i = 0; i < m1; i++) {
		for (int j = 0; j < n2; j++) {
			*((res + i * n2) + j) = 0;
			for (int k = 0; k < n1; k++) {
				*((res + i * n2) + j) += *((a + i * n1) + k) * *((b + k * n2) + j);
			}
		}
	}
	return res;
}

void printPoint(float* P) {
	printMatrix(P, 3, 1);
}

float* transformPoint(float* m, float* p) {
	return mulMatrix(m, 3, 3, p, 3, 1);
}

void drawPlane(int xmax, int ymax) {
	int hx = xmax/2, hy = ymax/2;
	glClear(GL_COLOR_BUFFER_BIT);
	glColor4f(1, 1, 0.4, 1); //yellow
	displayLine(-hx, 0, hx, 0, hx, hy); //x-axis
	displayLine(0, -hy, 0, hy, hx, hy); //y-axis
	glFlush();
}

void plotWindow()
{
	cout << "GET INPUTS FOR WINDOW IMAGE" << endl;

	//Point P1
	float x1, y1;
	cout << "Enter point P1 coords: ";
	cin >> x1 >> y1;

	float* P1 = new float[3] { {x1}, { y1 }, { 1 } };
	cout << "Homogeneous representation of P1: " << endl;
	printPoint(P1);
	cout << endl;
	G1 = P1;

	//Point P2
	float x2, y2;
	cout << "Enter point P2 coords: ";
	cin >> x2 >> y2;

	float* P2 = new float[3] { {x2}, { y2 }, { 1 } };
	cout << "Homogeneous representation of P2: " << endl;
	printPoint(P2);
	cout << endl;
	G2 = P2;

	//Point P3
	float x3, y3;
	cout << "Enter point P3 coords: ";
	cin >> x3 >> y3;

	float* P3 = new float[3] { {x3}, { y3 }, { 1 } };
	cout << "Homogeneous representation of P3: " << endl;
	printPoint(P3);
	cout << endl;
	G3 = P3;

	//plot triangle
	displayTriangleWindow(x1, y1, x2, y2, x3, y3);
}

void plotViewport() {
	cout << "GETTING INPUTS FROM WINDOW IMAGE" << endl;

	float Sx = xvmax/xwmax, Sy = yvmax/ywmax;
	//Scaling matrix: Window to Viewport
	float S[3][3] = {
		{Sx, 0, 0},
		{0, Sy, 0},
		{0, 0, 1}
	};

	//Point P1
	float* P1 = transformPoint((float*)S, G1);
	cout << "Homogeneous representation of P1: " << endl;
	printPoint(P1);
	cout << endl;

	//Point P2
	float* P2 = transformPoint((float*)S, G2);
	cout << "Homogeneous representation of P2: " << endl;
	printPoint(P2);
	cout << endl;

	//Point P3
	float* P3 = transformPoint((float*)S, G3);
	cout << "Homogeneous representation of P3: " << endl;
	printPoint(P3);
	cout << endl;

	//plot triangle
	displayHomogeneousTriangle(P1, P2, P3);

	delete[] P1;
	delete[] P2;
	delete[] P3;
}

void plotChart_win1() {
	myInit_win1(xwmax, ywmax);
	glClear(GL_COLOR_BUFFER_BIT);
	cout << "Window" << endl;

	drawPlane(xwmax, ywmax);
	plotWindow();

	glFlush();
	glutSwapBuffers();
}

void plotChart_win2() {
	myInit_win2(xvmax, yvmax);
	glClear(GL_COLOR_BUFFER_BIT);
	cout << "Viewport" << endl;

	drawPlane(xvmax, yvmax);
	plotViewport();

	glFlush();
	glutSwapBuffers();
}

int main(int argc, char* argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	
	glutInitWindowSize(xwmax, ywmax);
	glutInitWindowPosition(0, 0);
	int win1 = glutCreateWindow("Window");

	glutInitWindowSize(xvmax, yvmax);
	glutInitWindowPosition(0, 0);
	int win2 = glutCreateWindow("Viewport");

	glutSetWindow(win1);
	glutDisplayFunc(plotChart_win1);

	glutSetWindow(win2);
	glutDisplayFunc(plotChart_win2);

	glutMainLoop();
	return 1;
}