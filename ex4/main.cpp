#define GL_SILENCE_DEPRECATION

#include<GL/glut.h>
#include<iostream>
#include<math.h>
using namespace std;

void myInit() {
    glClearColor(0.6, 0.2, 1.0, 0.0);
    //glClearColor(0.4,0.2,1.0,0.0);
    glColor3f(0.0f, 0.0f, 0.5f);
    //glPointSize(10);
    glMatrixMode(GL_PROJECTION);
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glLineWidth(2);
    glLoadIdentity();
    gluOrtho2D(0.0, 640.0, 0.0, 480.0);
}

void displayPoint(int x, int y) {
    glBegin(GL_POINTS);
    glVertex2d(x + 320, y + 240);
    glEnd();
}

void displayLine(int x1, int y1, int x2, int y2) {
    glBegin(GL_LINES);
    glColor4f(1, 1, 0.4, 1);
    glVertex2d(x1 + 320, y1 + 240);
    glVertex2d(x2 + 320, y2 + 240);
    glEnd();
}

void drawPlane() {
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_LINES);
    glColor4f(1, 1, 1, 1);
    //y-axis
    displayLine(0, -240, 0, 240);
    //x-axis
    displayLine(-320, 0, 320, 0);
    glEnd();
    glFlush();
}

void plotAllOctets(int xc, int yc, int x, int y) {
    displayPoint(xc + x, yc + y);
    displayPoint(xc - x, yc + y);
    displayPoint(xc + x, yc - y);
    displayPoint(xc - x, yc - y);
    displayPoint(xc + y, yc + x);
    displayPoint(xc - y, yc + x);
    displayPoint(xc + y, yc - x);
    displayPoint(xc - y, yc - x);
}

void plotMidpointCircle() {
    int xc, yc, r;
    int P, x, y;

    cout << "Enter center coords: ";
    cin >> xc >> yc;
    cout << "Enter radius: ";
    cin >> r;
    cout << endl;

    plotAllOctets(xc, yc, 0, r);
    P = 1 - r;
    x = 0; y = r;

    while (x < y) {
        x++;
        if (P < 0) {
            P += (2 * x) + 1;
        }
        else {
            y--;
            P += 2 * (x - y) + 1;
        }
        plotAllOctets(xc, yc, x, y);
    }
}

void plotChart() {
    glClear(GL_COLOR_BUFFER_BIT);

    drawPlane();
    plotMidpointCircle();

    glFlush();
}

int main(int argc, char* argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
    glutInitWindowSize(640, 480);
    glutCreateWindow("Midpoint Circle Drawing Algorithm");
    glutDisplayFunc(plotChart);
    myInit();
    glutMainLoop();
    return 1;
}