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

void plotBresenhamLine() {
    int x1, y1, x2, y2;
    float dx, dy, m;
    int dir;
    float P;

    cout << "Enter start coords: ";
    cin >> x1 >> y1;
    cout << "Enter end coords: ";
    cin >> x2 >> y2;
    cout << endl;

    dir = x1 <= x2 ? 1 : 2;
    if (dir == 1) {
        cout << "Direction: L to R" << endl;
    }
    else {
        cout << "Direction: R to L" << endl;
    }

    dx = float(x2 - x1);
    dy = float(y2 - y1);
    m = dy / dx;
    cout << "Slope: " << m << endl;
    if (abs(m) > 1) {
        int temp1 = x1, temp2 = x2;
        x1 = y1; x2 = y2;
        y1 = temp1; y2 = temp2;

        int temp = dx;
        dx = dy; dy = temp;
    }

    dir = x1 <= x2 ? 1 : 2;
    if (dir == 2) {
        cout << "Direction: R to L" << endl;
        int tempX = x1, tempY = y1;
        x1 = x2; y1 = y2;
        x2 = tempX; y2 = tempY;

        dx = -dx; dy = -dy;
    }

    cout << "x y\n";
    cout << x1 << " " << y1 << endl;

    if (m >= 0) {
        P = (2 * dy) - dx;
        displayPoint(x1, y1);

        int y = y1;
        for (int x = x1 + 1; x <= x2; x++) {
            if (P < 0) {
                P += 2 * dy;
            }
            else {
                y++;
                P += 2 * (dy - dx);
            }
            if (abs(m) <= 1) {
                displayPoint(x, y);
                cout << x << " " << y << endl;
            }
            else {
                displayPoint(y, x);
                cout << y << " " << x << endl;
            }
        }
        /*
        else { //if abs(m) > 1
            int x = x1;
            for (int y = y1 + 1; y <= y2; y++) {
                if (P < 0) {
                    P += 2 * dx;
                }
                else {
                    x++;
                    P += 2 * (dx - dy);
                }
                displayPoint(x, y);
                cout << x << " " << y << endl;
            }
        }
        */
    }
    else {
        dx = abs(dx); dy = abs(dy);

        P = (2 * dy) - dx;
        displayPoint(x1, y1);

        int y = y1;
        for (int x = x1 + 1; x <= x2; x++) {
            if (P < 0) {
                P += 2 * dy;
            }
            else {
                y--;
                P += 2 * (dy - dx);
            }
            if (abs(m) <= 1) {
                displayPoint(x, y);
                cout << x << " " << y << endl;
            }
            else {
                displayPoint(y, x);
                cout << y << " " << x << endl;
            }
        }
    }
}

void plotChart() {
    glClear(GL_COLOR_BUFFER_BIT);

    drawPlane();
    plotBresenhamLine();

    glFlush();
}

int main(int argc, char* argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
    glutInitWindowSize(640, 480);
    glutCreateWindow("Bresenham Line Drawing Algorithm");
    glutDisplayFunc(plotChart);
    myInit();
    glutMainLoop();
    return 1;
}