#include<stdlib.h>
#include<gl/glut.h>
#include<iostream>

using namespace std;

typedef float point3[3];

point3 tetrahedron_points[4] = { {0,0,150}, {0,150,-150},{-150,-150,-150},{150,-150,-150} };

void drawTriangle(point3 p1, point3 p2, point3 p3)
{
	glBegin(GL_TRIANGLES);
	glVertex3fv(p1);
	glVertex3fv(p2);
	glVertex3fv(p3);
	glEnd();
}

void drawTetrahedron(point3 p1, point3 p2, point3 p3, point3 p4)
{
	glColor3f(1, 1, 0);
	drawTriangle(p1, p2, p3);
	glColor3f(0, 0, 1);
	drawTriangle(p1, p3, p4);
	glColor3f(0, 1, 0);
	drawTriangle(p1, p4, p2);
	glColor3f(1, 0, 0);
	drawTriangle(p2, p3, p4);
}

void divideTetrahedron(point3 p1, point3 p2, point3 p3, point3 p4,int iter)
{
	if (iter > 0)
	{
		point3 mid[6];
		for (int i = 0; i < 3; i++)
		{
			mid[0][i] = (p1[i] + p2[i]) / 2;
			mid[1][i] = (p2[i] + p3[i]) / 2;
			mid[2][i] = (p1[i] + p3[i]) / 2;
			mid[3][i] = (p1[i] + p4[i]) / 2;
			mid[4][i] = (p2[i] + p4[i]) / 2;
			mid[5][i] = (p3[i] + p4[i]) / 2;
		}

		divideTetrahedron(p1, mid[0], mid[2], mid[3], iter - 1);
		divideTetrahedron(mid[0], p2, mid[1], mid[4], iter - 1);
		divideTetrahedron(mid[2], mid[1], p3, mid[5], iter - 1);
		divideTetrahedron(mid[3], mid[4], mid[5], p4, iter - 1);
	}
	else
		drawTetrahedron(p1, p2, p3, p4);
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	divideTetrahedron(tetrahedron_points[0], tetrahedron_points[1], tetrahedron_points[2], tetrahedron_points[3],3);
	glFlush();
}

void init()
{
	glClearColor(1, 1, 1, 1);
	glOrtho(-250, 250, -250, 250,-250,250);
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE | GLUT_DEPTH);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Sierpinski Gasket");
	glutDisplayFunc(display);
	glEnable(GL_DEPTH_TEST);
	init();
	glutMainLoop();
}