#include<stdlib.h>
#include<gl/glut.h>
#include<iostream>

float spin; int w1, w2,t;

void display()
{
	glutSetWindow(t);
	glClear(GL_COLOR_BUFFER_BIT);
	glPushMatrix();
	glLoadIdentity();
	glRotatef(spin, 0, 0, 1);
	glBegin(GL_POLYGON);
	glColor3f(1, 0, 0);
	glVertex2f(-0.50, -0.50);
	glColor3f(0, 1, 0);
	glVertex2f(0.50, -0.50);
	glColor3f(0, 0, 1);
	glVertex2f(0.50, 0.50);
	glColor3f(1, 1, 0);
	glVertex2f(-0.50, 0.50);
	glEnd();
	glPopMatrix();
	if (t == w1)
	{
		glFlush();
		t = w2;
	}
	else
	{
		t = w1;
		glutSwapBuffers();
	}
}

void spindisplay()
{
	spin += 0.2;
	glutPostRedisplay();
}

void mouse(int b, int s, int x, int y)
{
	if (b == GLUT_LEFT_BUTTON && s == GLUT_DOWN)
		glutIdleFunc(spindisplay);
	else if (b == GLUT_RIGHT_BUTTON && s == GLUT_DOWN)
		glutIdleFunc(NULL);
}


void init()
{
	glClearColor(1, 1, 1, 1);
	gluOrtho2D(-1, 1, -1, 1);
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(0, 0);
	w1 = glutCreateWindow("Single buffer");
	t = w1;
	glutDisplayFunc(display);
	glutMouseFunc(mouse);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(0, 0);
	w2 = glutCreateWindow("Double buffer");
	glutDisplayFunc(display);
	glutMouseFunc(mouse);
	init();
	glutMainLoop();
	return 0;
}