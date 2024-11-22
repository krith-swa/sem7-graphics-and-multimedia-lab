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
    gluOrtho2D(-320.0, 320.0, -240.0, 240.0);
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

void plotDDALine() {
    int x1, y1, x2, y2;
    float m;
    int dir;

    cout << "Enter start coords: ";
    cin >> x1 >> y1;
    cout << "Enter end coords: ";
    cin >> x2 >> y2;
    cout << endl;

    m = float(y2 - y1) / float(x2 - x1);
    cout << "Slope: " << m << endl;
    dir = x1 <= x2 ? 1 : 2;
    if (dir == 1) {
        cout << "Direction: L to R" << endl;
    }
    else {
        cout << "Direction: R to L" << endl;
    }

    if (m >= 0) {
        if (dir == 1) {
            if (abs(m) <= 1) {
                float y = y1;
                cout << "x " << "y " << "round(y)" << endl;
                for (int x = x1; x <= x2; x++) {
                    y += m;
                    cout << x << " " << y << " " << round(y) << endl;
                    displayPoint(x, round(y));
                }
            }
            else {
                float x = x1;
                cout << "x " << "round(x)" << "y " << endl;
                for (int y = y1; y <= y2; y++) {
                    x += (1 / m);
                    cout << x << " " << round(x) << " " << y << endl;
                    displayPoint(round(x), y);
                }
            }
        }
        else {
            if (abs(m) <= 1) {
                float y = y1;
                cout << "x " << "y " << "round(y)" << endl;
                for (int x = x1; x >= x2; x--) {
                    y -= m;
                    cout << x << " " << y << " " << round(y) << endl;
                    displayPoint(x, round(y));
                }
            }
            else {
                float x = x1;
                cout << "x " << "round(x)" << "y " << endl;
                for (int y = y1; y >= y2; y--) {
                    x -= (1 / m);
                    cout << x << " " << round(x) << " " << y << endl;
                    displayPoint(round(x), y);
                }
            }
        }
    }
    else {
        m = abs(m);
        if (dir == 1) {
            if (abs(m) <= 1) {
                float y = y1;
                cout << "x " << "y " << "round(y)" << endl;
                for (int x = x1; x <= x2; x++) {
                    y -= m;
                    cout << x << " " << y << " " << round(y) << endl;
                    displayPoint(x, round(y));
                }
            }
            else {
                float x = x1;
                cout << "x " << "round(x)" << "y " << endl;
                for (int y = y1; y >= y2; y--) {
                    x += (1 / m);
                    cout << x << " " << round(x) << " " << y << endl;
                    displayPoint(round(x), y);
                }
            }
        }
        else {
            if (abs(m) <= 1) {
                float y = y1;
                cout << "x " << "y " << "round(y)" << endl;
                for (int x = x1; x >= x2; x--) {
                    y += m;
                    cout << x << " " << y << " " << round(y) << endl;
                    displayPoint(x, round(y));
                }
            }
            else {
                float x = x1;
                cout << "x " << "round(x)" << "y " << endl;
                for (int y = y1; y <= y2; y++) {
                    x -= (1 / m);
                    cout << x << " " << round(x) << " " << y << endl;
                    displayPoint(round(x), y);
                }
            }
        }
    }
}

void plotChart() {
    glClear(GL_COLOR_BUFFER_BIT);

    drawPlane();
    plotDDALine();

    glFlush();
}

int main(int argc, char* argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
    glutInitWindowSize(640, 480);
    glutCreateWindow("DDA Line Drawing Algorithm");
    glutDisplayFunc(plotChart);
    myInit();
    glutMainLoop();
    return 1;
}