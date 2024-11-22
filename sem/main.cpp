#define GL_SILENCE_DEPRECATION

#include <iostream>
#include <gl/glut.h>
#include <math.h>
using namespace std;

float P[3] = {{0}, {0}, {1}};
float M[3][3] = {
	{1, 0, 0},
	{0, 1, 0},
	{0, 0, 1}
};

float xmax = 100, ymax = 100, xmin = -100, ymin = -100;

//TBRL
int RC1[4] = { 0, 0, 0, 0 };
int RC2[4] = { 0, 0, 0, 0 };
int OR[4] = { 0, 0, 0, 0 };
int AND[4] = { 0, 0, 0, 0 };

int valx = 10, valy = 10;

char letter = 'A';

void myInit() {
	glClearColor(0, 0, 0, 1);
	glMatrixMode(GL_PROJECTION);
	glPointSize(5);
	glLoadIdentity();
	gluOrtho2D(-320.0, 320.0, -240.0, 240.0);
}

void displayPoint(int x, int y) {
	glBegin(GL_POINTS);
	glVertex2d(x, y);
	glEnd();
}

void labelPoint(float x, float y, char label) {
	glRasterPos2f(x, y);
	glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, label);
}

void displayLine(int x1, int y1, int x2, int y2) {
	glBegin(GL_LINES);
	glVertex2d(x1, y1);
	glVertex2d(x2, y2);
	glEnd();
}


void drawDDALine(float x1, float y1, float x2, float y2) {
	float dx, dy, steps, xInc, yInc, x, y;

	dx = x2 - x1;
	dy = y2 - y1;

	if (abs(dy) >= abs(dx)) {
		steps = abs(dy);
	}
	else {
		steps = abs(dx);
	}

	xInc = dx / steps;
	yInc = dy / steps;

	x = x1; y = y1;
	displayPoint(round(x), round(y));
	for (int i = 1; i <= steps; i++) {
		x += xInc;
		y += yInc;
		displayPoint(round(x), round(y));
	}
}

void drawBresenhamLine(float x1, float y1, float x2, float y2) {
	float dx, dy, m, P, xEnd;
	int x, y, step = 1;

	dx = x2 - x1;
	dy = y2 - y1;
	m = dy / dx; 

	//swap x and y if |m|>1
	if (abs(m) > 1) {
		float temp1 = x1, temp2 = x2;
		x1 = y1; x2 = y2;
		y1 = temp1; y2 = temp2;

		float tempd = dx;
		dx = dy;
		dy = tempd;
	}

	//swap begin-end and -d if dir R to L
	if (x2 < x1) {
		x = x2; y = y2;
		xEnd = x1;

		dx = -dx; dy = -dy;
	}
	else {
		x = x1; y = y1;
		xEnd = x2;
	}

	//abs(d) and y-- if -ve m
	if (m < 0) {
		dx = abs(dx); dy = abs(dy);
		step = -1;
	}

	//start algo
	P = (2 * dy) - dx;
	if (abs(m) > 1) {
		displayPoint(y, x);
	}
	else {
		displayPoint(x, y);
	}
	while (x < xEnd) {
		x++;
		if (P < 0) {
			P += 2 * dy;
		}
		else {
			y += step;
			P += 2 * (dy - dx);
		}
		if (abs(m) > 1) {
			displayPoint(y, x);
		}
		else {
			displayPoint(x, y);
		}
	}
}

void drawMidptCircle(int xc, int yc, int r) {
	int x, y, P;

	x = 0; y = r;
	P = 1 - r;

	while (x < y) {
		x++;
		if (P < 0) {
			P += (2 * x) + 1;
		}
		else {
			y--;
			P += 2 * (x - y) + 1;
		}
		displayPoint(x, y);
	}
}

void transformPoint(float x, float y) {
	P[0] = x; P[1] = y;
	displayPoint(x, y);

	//put following code in a while loop with input for composite transformation
	//get input for full M matrix or have switch case within input while loop for initialising M for each type of transformation
	float Sx = valx, Sy = valy;
	M[0][0] = Sx; M[1][1] = Sy;

	float newP[3];

	for (int i = 0; i < 3; i++) {
		newP[i] = 0;
		for (int j = 0; j < 3; j++) {
			newP[i] += M[i][j] * P[j];
		}
	}

	for (int k = 0; k < 3; k++) {
		P[k] = newP[k];
	}
	x = P[0]; y = P[1];
	displayPoint(x, y);
}

void getRC1(float x1, float y1) {
	RC1[0] = (y1 > ymax) ? 1 : 0;
	RC1[1] = (y1 < ymin) ? 1 : 0;
	RC1[2] = (x1 > xmax) ? 1 : 0;
	RC1[3] = (x1 < xmin) ? 1 : 0;
}

void getRC2(float x2, float y2) {
	RC2[0] = (y2 > ymax) ? 1 : 0;
	RC2[1] = (y2 < ymin) ? 1 : 0;
	RC2[2] = (x2 > xmax) ? 1 : 0;
	RC2[3] = (x2 < xmin) ? 1 : 0;
}

bool isTrivialAccept() {
	for (int i = 0; i < 4; i++) {
		if (OR[i] == 1) {
			cout << "not accept" << endl;
			return false;
		}
	}
	cout << "accept" << endl;
	return true;
}
bool isTrivialReject() {
	for (int i = 0; i < 4; i++) {
		if (AND[i] == 1) {
			cout << "reject" << endl;
			return true;
		}
	}
	cout << "not reject" << endl;
	return false;
}

int firstRegion() {
	int i;
	for (i = 0; OR[i] == 0; i++);
	return i;
}

void clipLineCS(float x1, float y1, float x2, float y2) {
	bool algoEnd = false;
	do {
		for (int i = 0; i < 4; i++) {
			OR[i] = max(RC1[i], RC2[i]);
			cout << OR[i] << " ";
			AND[i] = min(RC1[i], RC2[i]);
			cout << AND[i] << endl;
		}

		if (isTrivialAccept() || isTrivialReject()) {
			algoEnd = true;
			displayLine(x1, y1, x2, y2);
		}
		else {
			int r = firstRegion();

			float x = x1, y = y1;
			float m = (y2 - y1) / (x2 - x1);

			glColor3f(1, 0, 0);

			if (r == 0) {
				y = ymax;
				x = x1 + (1 / m) * (y - y1);
				getRC1(x, y);
				x1 = x; y1 = y;
				labelPoint(x1, y1, letter++);
			}
			else if (r == 1) {
				y = ymin;
				x = x1 + (1 / m) * (y - y1);
				getRC2(x, y);
				x2 = x; y2 = y;
				labelPoint(x2, y2, letter++);
			}
			else if (r == 2) {
				x = xmax;
				y = y1 + m * (x - x1);
				getRC2(x, y);
				x2 = x; y2 = y;
				labelPoint(x2, y2, letter++);
			}
			else if (r == 3) {
				x = xmin;
				y = y1 + m * (x - x1);
				getRC1(x, y);
				x1 = x; y1 = y;
				labelPoint(x1, y1, letter++);
			}
			cout << "\nP1: " << x1 << " " << y1 << endl;
			cout << "P2: " << x2 << " " << y2 << endl;
			displayLine(x1, y1, x2, y2);
		}
	} while (!algoEnd);
}

void plotChart() {
	glClear(GL_COLOR_BUFFER_BIT);

	glColor3f(1, 1, 1);
	//drawDDALine(-300, 200, 0, 0);
	//drawBresenhamLine(200, 100, 0, 0);
	//drawMidptCircle(100, 100, 50);
	//transformPoint(-5, 10);
	//transformPoint(10, 10);
	//displayPoint(0, 0);
	clipLineCS(-150, 50, 200, -150);

	//glutSwapBuffers();
	glFlush();
}

void animate() {
	valx += 1; valy += 1;
	if (valx > 20 && valy > 20) {
		valx = -20; valy = -20;
	}
	glutPostRedisplay();
}

void timer(int time) {
	valx += 1; valy += 1;
	if (valx > 20 && valy > 20) {
		valx = -20; valy = -20;
	}
	glutTimerFunc(1000, timer, 0);
	glutPostRedisplay();
}

int main (int argc, char* argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	//glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(640, 320);
	glutCreateWindow("Sem Practice");

	glutDisplayFunc(plotChart);
	//glutIdleFunc(animate);
	//glutTimerFunc(0, timer, 0);

	myInit();
	glutMainLoop();
	return 0;
}