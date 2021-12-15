#include<stdlib.h>
#include<gl/glut.h>
#include<iostream>

using namespace std;

void drawPoints(int xc, int yc, int x, int y)
{
	glColor3f(0, 0, 1);
	glBegin(GL_POINTS);
	glVertex2f(xc + x, yc + y);
	glVertex2f(xc - x, yc + y);
	glVertex2f(xc + x, yc - y);
	glVertex2f(xc - x, yc - y);
	glVertex2f(xc + y, yc + x);
	glVertex2f(xc - y, yc + x);
	glVertex2f(xc + y, yc - x);
	glVertex2f(xc - y, yc - x);
	glEnd();
}

void drawCircle(int xc, int yc, int r)
{
	int x = 0, y = r, e = 3 - 2 * r;
	while (x <= y)
	{
		drawPoints(xc, yc, x, y);
		x++;
		if (e > 0)
		{
			y--;
			e += 4 * (x - y) + 10;
		}
		else
			e += 4 * x + 6;
		drawPoints(xc, yc, x, y);
	}
}

void display_cy()
{
	glClear(GL_COLOR_BUFFER_BIT);
	int xc = 0, yc = 0, r = 60;
	for (int i = 0; i <= 60; i += 3)
		drawCircle(xc, yc + i, r);
	glFlush();
}

void drawParallelogram(int x1,int y1,int x2,int y2)
{
	glColor3f(1, 0, 0);
	glBegin(GL_LINE_LOOP);
	glVertex2f(x1, y1);
	glVertex2f(x2, y1);
	glVertex2f(x2, y2);
	glVertex2f(x1, y2);
	glEnd();
}

void display_pp()
{
	glClear(GL_COLOR_BUFFER_BIT);
	int x1 = -50, x2 = 50, y1 = -50, y2 = 50;
	for (int i = 0; i < 40; i += 2)
		drawParallelogram(x1 + i, y1 + i, x2 + i, y2 + i);
	glFlush();
}

void init()
{
	glClearColor(1, 1, 1, 1);
	gluOrtho2D(-250, 250, -250, 250);
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(500, 500);

	int cy = glutCreateWindow("Cylinder");
	glutSetWindow(cy);
	glutDisplayFunc(display_cy);
	init();

	int pp = glutCreateWindow("Parallelopiped");
	glutSetWindow(pp);
	glutDisplayFunc(display_pp);
	init();

	glutMainLoop();
	return 0;
}