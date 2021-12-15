#include<stdlib.h>
#include<gl/glut.h>
#include<iostream>
#include<math.h>
#define WINDOW_WIDTH 500
#define WINDOW_HEIGHT 500

using namespace std;

int xc, yc, r, flag=0;

void drawPoint(int x, int y)
{
	glBegin(GL_POINTS);
	glColor3f(0, 0, 0);
	glPointSize(3);
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

void drawCircle()
{
	glClear(GL_COLOR_BUFFER_BIT);
	int x = 0, y = r;
	int e = 3 - 2 * r;
	while (x <= y)
	{
		drawPoint(x, y);
		x++;
		if (e > 0)
		{
			y--;
			e += 4 * (x - y) + 10;
		}
		else
			e += 4 * x + 6;
		drawPoint(x, y);
	}
	glFlush();
}

void mouse(int b, int s, int x, int y)
{
	if (b == GLUT_LEFT_BUTTON && s == GLUT_DOWN)
	{
		if (flag == 0)
		{
			xc = x - (WINDOW_WIDTH / 2);
			yc = (WINDOW_HEIGHT / 2) - y;
			cout << "xc, yc : " << xc << "," << yc << endl;
			flag = 1;
		}
		else
		{
			int x1 = x - (WINDOW_WIDTH / 2);
			int y1 = (WINDOW_HEIGHT / 2) - y;
			float temp = (x1 - xc) * (x1 - xc) + (y1 - yc) * (y1 - yc);
			r = (int)sqrt(temp);
			cout << "r : " << r << endl;
			flag = 0;
			drawCircle();
		}
	}
}

void display(){}

void myInit()
{
	glClearColor(1, 1, 1, 1);
	glLoadIdentity();
	gluOrtho2D(-250, 250, -250, 250);
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutCreateWindow("Bresenham - Circle");
	myInit();
	glutDisplayFunc(display);
	glutMouseFunc(mouse);
	glutMainLoop();
	return 0;
}