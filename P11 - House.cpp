#include<stdlib.h>
#include<gl/glut.h>
#include<iostream>
#include<math.h>

using namespace std;

float house[7][2] = { {-100,100},{0,200},{100,100},{100,-100},{-100,-100},{-100,100},{100,100} };
float angle, m, c;

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(1, 1, 1, 1);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-500, 500, -500, 500);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glColor3f(1, 0, 0);
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < 7; i++)
		glVertex2fv(house[i]);
	glEnd();
	glFlush();

	glPushMatrix();
	glRotatef(angle, 0, 0, 1);
	glColor3f(0, 1, 0);
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < 7; i++)
		glVertex2fv(house[i]);
	glEnd();
	glPopMatrix();
	glFlush();
}

void display2()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(1, 1, 1, 1);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-500, 500, -500, 500);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glColor3f(1, 0, 0);
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < 7; i++)
		glVertex2fv(house[i]);
	glEnd();
	glFlush();

	float x1 = -250, x2 = 0;
	float y1 = m * x1 + c;
	float y2 = m * x2 + c;
	glColor3f(0, 0, 0);
	glBegin(GL_LINES);
	glVertex2f(x1, y1);
	glVertex2f(x2, y2);
	glEnd();
	glFlush();

	double theta = atan(m);
	theta = theta * 180 / 3.14;
	glPushMatrix();
	glTranslatef(0, c, 0);
	glRotatef(theta, 0, 0, 1);
	glScalef(1, -1, 1);
	glRotatef(-theta, 0, 0, 1);
	glTranslatef(0, -c, 0);
	glColor3f(1, 0, 0);
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < 7; i++)
		glVertex2fv(house[i]);
	glEnd();
	glPopMatrix();
	glFlush();
}

void mouse(int btn, int state, int x, int y)
{
	if (btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		display();
	}
	else if (btn == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
		display2();
	}
}

void init()
{
	glClearColor(1, 1, 1, 1);
	gluOrtho2D(-500, 500, -500, 500);
}

int main(int argc, char** argv)
{
	cout << "Enter the rotation angle : \n";
	cin >> angle;
	cout << "Enter c and m for line y = mx + c\n";
	cin >> c >> m;
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(1000, 1000);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("House");
	glutDisplayFunc(display2);
	glutMouseFunc(mouse);
	init();
	glutMainLoop();
	return 0;
}