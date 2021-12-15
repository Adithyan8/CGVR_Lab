#include<stdlib.h>
#include<gl/glut.h>
#include<iostream>
#include<algorithm>
#include<windows.h>

using namespace std;

int n = 4,wx=500,wy=500;
float pt[10];int m;
float x[4] = {-150,-150,150,150 }, y[4] = { 150,-150,-150,150 };

void drawLine(float x1, float x2, float s)
{
	Sleep(100);
	glColor3f(1, 0, 0);
	glBegin(GL_LINES);
	glVertex2f(x1, s);
	glVertex2f(x2, s);
	glEnd();
	glFlush();
}

void edgeDetect(float x1,float y1,float x2,float y2,float s)
{
	if (y2 < y1)
	{
		swap(x1, x2);
		swap(y1, y2);
	}
	if (s > y1 && s < y2)
		pt[m++] = x1 + (s - y1) * (x2 - x1) / (y2 - y1);
}

void scanfill()
{
	for (int s = -150; s < wy; s++)
	{
		m = 0;
		for (int i = 0; i < n; i++)
			edgeDetect(x[i],y[i], x[(i + 1) % n], y[(i + 1) % n],s);
		if (m >= 2)
		{
			sort(pt, pt + m);
			for (int i = 0; i < m; i += 2)
				drawLine(pt[i],pt[i+1],s);
		}
	}
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0, 0, 0);
	glBegin(GL_LINE_LOOP);
	glVertex2f(x[0], y[0]);
	glVertex2f(x[1], y[1]);
	glVertex2f(x[2], y[2]);
	glVertex2f(x[3], y[3]);
	glEnd();
	scanfill();
}

void init()
{
	glClearColor(1, 1, 1, 1);
	gluOrtho2D(-250, 250, -250, 250);
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(wx,wy);
	glutCreateWindow("Scanline");
	glutDisplayFunc(display);
	init();
	glutMainLoop();
	return 0;
}