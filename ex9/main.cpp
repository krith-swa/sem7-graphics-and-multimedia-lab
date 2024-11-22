#define GL_SILENCE_DEPRECATION

#include <GL/glut.h>
#include <iostream>
using namespace std;

void display_ortho() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-200, 200, -200, 200, -200, 200); // Set up orthographic projection
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	// Draw the colored edges of the cube
	glPushMatrix();
	glRotatef(45, 1, 1, 0);
	//glColor3f(0.0f, 1.0f, 1.0f);
	glColor3f(1.0f, 0.0f, 1.0f);
	glutWireCube(100);
	glPopMatrix();
	glPushMatrix();
	glRotatef(45, 1, 1, 0);
	//glColor3f(0.2f, 0.4f, 0.7f);
	glColor3f(0.4f, 0.1f, 0.7f);
	glutSolidCube(100);
	glPopMatrix();
	glutSwapBuffers();
}
void display_pers() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, 1.0f, 0.1f, 500.0f); // Set up perspective projection
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0, 0, 250, 0, 0, 0, 0, 1, 0); // Set the camera position
	// Draw the colored edges of the cube
	glPushMatrix();
	glRotatef(45, 1, 1, 0);
	glColor3f(1.0f, 0.0f, 1.0f);
	glutWireCube(100);
	glPopMatrix();
	// Draw the solid faces of the cube
	glPushMatrix();
	glRotatef(45, 1, 1, 0);
	glColor3f(0.4f, 0.1f, 0.7f);
	glutSolidCube(100);
	glPopMatrix();
	glutSwapBuffers();
}
int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(400, 400);
	glutCreateWindow("3D Projections");
	glEnable(GL_DEPTH_TEST);
	int choice;
	cout << "\n1.Orthographic Projection\n2.Perspective Projection\nEnter your choice:";
	cin >> choice;
	switch (choice)
	{
	case 1:
		glutDisplayFunc(display_ortho);
		break;
	case 2:
		glutDisplayFunc(display_pers);
		break;
	default:
		cout << "Please enter a valid choice!!!\n";
		return 0;
	}
	glutMainLoop();
	return 0;
}