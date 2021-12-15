#include<stdlib.h>
#include<gl/glut.h>
#include<iostream>

using namespace std;

int flag = 0, x1, x2, yc1, y2;

void display(){}

void drawPoint(int x, int y)
{
	glColor3f(0, 0, 0);
	glPointSize(5);
	glBegin(GL_POINTS);
	glVertex2f(x, y);
	glEnd();
}

void drawLine()
{
	int dx = x2 - x1, dy = y2 - yc1;
	int incx = 1, incy = 1, inc1, inc2;
	if (dx == 0)
	{
		for (int i = 0; i <= dx; i++)
			drawPoint(x1+i, yc1);
	}
	if (dy == 0)
	{
		for (int i = 0; i <= dy; i++)
			drawPoint(x1, yc1 + i);
	}
	if (y2 < yc1) incy = -1;
	if (x2 < x1) incx = -1;
	if (dx < 0) dx = -dx;
	if (dy < 0) dy = -dy;

	if (dx > dy)
	{
		int e = 2 * dy - dx;
		inc1 = 2 * dy - 2 * dx;
		inc2 = 2 * dy;
		int x = x1, y = yc1;
		for (int i = 0; i < dx ; i++)
		{
			drawPoint(x, y);
			if (e > 0) {
				y += incy;
				e += inc1;
			}
			else
				e += inc2;
			x += incx;
			drawPoint(x, y);
		}
	}
	else
	{
		int e = 2 * dx - dy;
		inc1 = 2 * dx - 2 * dy;
		inc2 = 2 * dx;
		int x = x1, y = yc1;
		for (int i = 0; i < dy; i++)
		{
			drawPoint(x, y);
			if (e > 0) {
				x += incx;
				e += inc1;
			}
			else
				e += inc2;
			y += incy;
			drawPoint(x, y);
		}
	}
	glFlush();
}

void mouse(int b, int s, int x, int y)
{
	if (b == GLUT_LEFT_BUTTON && s == GLUT_DOWN)
	{
		if (flag == 0)
		{
			x1 = x - 250;
			yc1 = 250 - y;
			cout << "x1,y1 : " <<x1<<","<<yc1<<endl;
			flag = 1;
		}
		else
		{
			x2 = x - 250;
			y2 = 250 - y;
			cout << "x2,y2 : " <<x2<<"," << y2 << endl;
			flag = 0;
			drawLine();
		}
	}
}

void myInit()
{
	glClearColor(1, 1, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluOrtho2D(-250, 250, -250, 250);
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Bresenham Line");
	myInit();
	glutDisplayFunc(display);
	glutMouseFunc(mouse);
	glutMainLoop();
	return 0;
}