#include<stdlib.h>
#include<gl/glut.h>
#include<iostream>

using namespace std;

int axis = 0; float theta[3] = { 0,0,0 };

float vertices[8][3] = {
{-1.0,-1.0,-1.0},{1.0,-1.0,-1.0},
{1.0,1.0,-1.0},{-1.0,1.0,-1.0},
{-1.0,-1.0,1.0},{1.0,-1.0,1.0},
{1.0,1.0,1.0},{-1.0,1.0,1.0}
};

float color[8][3] = { {1,0,0},{0,1,0},{0,0,1},{1,1,0},{1,1,0},{1,0,0},{0,1,0},{0,0,1} };

void polygon(int a, int b, int c, int d)
{
	glBegin(GL_POLYGON);
	glColor3fv(color[a]);
	glVertex3fv(vertices[a]);
	glColor3fv(color[b]);
	glVertex3fv(vertices[b]);
	glColor3fv(color[c]);
	glVertex3fv(vertices[c]);
	glColor3fv(color[d]);
	glVertex3fv(vertices[d]);
	glEnd();
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	//glPushMatrix();
	glRotatef(theta[0], 1, 0, 0);
	glRotatef(theta[1], 0, 1, 0);
	glRotatef(theta[2], 0, 0, 1);
	polygon(0, 3, 2, 1);
	polygon(2, 3, 7, 6);
	polygon(4, 5, 6, 7);
	polygon(1, 5, 4, 0);
	polygon(7, 3, 0, 4);
	polygon(2, 6, 5, 1);
	//glPopMatrix();
	glutSwapBuffers();
}

void spincube()
{
	theta[axis] += 0.2;
	if (theta[axis] > 360) theta[axis] -= 360;
	glutPostRedisplay();
}

void mouse(int b, int s, int x, int y)
{
	if (b == GLUT_LEFT_BUTTON && s == GLUT_DOWN) axis = 0; //x
	else if (b == GLUT_RIGHT_BUTTON && s == GLUT_DOWN) axis = 1; //y
	else if (b == GLUT_MIDDLE_BUTTON && s == GLUT_DOWN) axis = 2; //z
}

void myReshape(int w, int h)// common reshape func for all prgrms
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (w <= h)
		glOrtho(-2.0, 2.0, -2.0 * (float)h / w, 2.0 * (float)h / w, -10.0, 10.0);
	else
		glOrtho(-2.0 * (float)w / h, 2.0 * (float)w / h, -2.0, 2.0, -10.0, 10.0);
	glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(700, 700);
	glutCreateWindow("Color Cube ");
	glutDisplayFunc(display);
	glutReshapeFunc(myReshape);
	glutMouseFunc(mouse);
	glutIdleFunc(spincube);
	glEnable(GL_DEPTH_TEST);
	glutMainLoop();
	return 0;
}