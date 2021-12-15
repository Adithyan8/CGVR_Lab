#include<stdlib.h>
#include<gl/glut.h.>
#include<iostream>

using namespace std;

int poly_size, org_poly_size,clipper_size; int org_poly_points[10][2], poly_points[10][2], clipper_points[10][2];

void drawPoly(int p[][2], int n) {
	glBegin(GL_POLYGON);
	for (int i = 0; i < n; i++)
		glVertex2f(p[i][0], p[i][1]);
	glEnd();
}

int xint(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4)
{
	int num = (x1 * y2 - y1 * x2) * (x3 - x4) - (x1 - x2) * (x3 * y4 - y3 * x4);
	int den = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);
	return num / den;
}

int yint(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4)
{
	int num = (x1 * y2 - y1 * x2) * (y3 - y4) - (y1 - y2) * (x3 * y4 - y3 * x4);
	int den = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);
	return num / den;
}

void clip(int poly_points[][2], int poly_size, int x1, int y1, int x2, int y2)
{
	int new_points[20][2],new_poly_size=0;
	for (int i = 0; i < poly_size; i++)
	{
		int k = (i + 1) % poly_size;
		int ix = poly_points[i][0], iy = poly_points[i][1], kx = poly_points[k][0], ky = poly_points[k][1];
		int i_pos = (x2 - x1)*(iy - y1) - (y2 - y1)*(ix - x1);
		int k_pos = (x2 - x1)*(ky - y1) - (y2 - y1)*(kx - x1);

		if (i_pos >= 0 && k_pos>=0)
		{
			new_points[new_poly_size][0] = kx;
			new_points[new_poly_size][1] = ky;
			new_poly_size++;
		}
		else if (i_pos >= 0 && k_pos < 0)
		{
			new_points[new_poly_size][0] = xint(x1, y1, x2, y2, ix, iy, kx, ky);
			new_points[new_poly_size][1] = yint(x1, y1, x2, y2, ix, iy, kx, ky);
			new_poly_size++;

			new_points[new_poly_size][0] = kx;
			new_points[new_poly_size][1] = ky;
			new_poly_size++;
		}
		else if (i_pos < 0 && k_pos >= 0)
		{
			new_points[new_poly_size][0] = xint(x1, y1, x2, y2, ix, iy, kx, ky);
			new_points[new_poly_size][1] = yint(x1, y1, x2, y2, ix, iy, kx, ky);
			new_poly_size++;
		}
	}
	poly_size = new_poly_size;
	for (int i = 0; i < poly_size; i++)
	{
		poly_points[i][0] = new_points[i][0];
		poly_points[i][1] = new_points[i][1];
	}
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0, 0, 1);
	drawPoly(clipper_points, clipper_size);
	glColor3f(0, 1, 0);
	drawPoly(org_poly_points, org_poly_size);
	for (int i = 0; i < clipper_size; i++)
	{
		int k = (i + 1) % clipper_size;
		clip(poly_points, poly_size, clipper_points[i][0], clipper_points[i][1], clipper_points[k][0], clipper_points[k][1]);
	}
	glColor3f(1, 0, 0);
	drawPoly(poly_points, poly_size);
	glFlush();
}

void init() {
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	gluOrtho2D(0.0, 500.0, 0.0, 500.0);
}

int main(int argc, char* argv[])
{
	cout << "Enter no. of polygon vertices: \n";
	cin>>poly_size;
	org_poly_size = poly_size;
	for (int i = 0; i < poly_size; i++)
	{
		cout << "Polygon Vertex:\n";
		cin>>poly_points[i][0]>>poly_points[i][1];
		org_poly_points[i][0] = poly_points[i][0];
		org_poly_points[i][1] = poly_points[i][1];
	}

	cout<<"Enter no. of vertices of clipping window:";
	cin>>clipper_size;
	for (int i = 0; i < clipper_size; i++)
	{
		cout<<"Clip Vertex:\n";
		cin>>clipper_points[i][0]>>clipper_points[i][1];
	}

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(400, 400);
	glutCreateWindow("Polygon Clipping!");
	glutDisplayFunc(display);
	init();
	glutMainLoop();
	return 0;
}