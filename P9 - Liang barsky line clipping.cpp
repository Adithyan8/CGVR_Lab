#include<stdlib.h>
#include<gl/glut.h>
#include<iostream>

using namespace std;

int n;
double xmin, xmax, ymin, ymax, xvmin, yvmin, xvmax, yvmax;

struct line
{
	int x1, y1, x2, y2;
};
line ls[10];

bool cliptest(double p, double q, double* t1, double* t2)
{
	if (p == 0)
	{
		if (q < 0) return false;
	}
	double r = q / p;
	if (p < 0)
	{
		if (r > * t1) *t1 = r;
		if (r > * t2) return false;
	}
	else if(p>0)
	{
		if (r < *t2)*t2 = r;
		if (r > * t2) return false;
	}
	return true;
}

void liangbarsky(double x1, double y1, double x2, double y2)
{
	glColor3f(1, 0, 0);
	glBegin(GL_LINE_LOOP);
	glVertex2f(xvmin, yvmin);
	glVertex2f(xvmax, yvmin);
	glVertex2f(xvmax, yvmax);
	glVertex2f(xvmin, yvmax);
	glEnd();

	double dx = x2 - x1, dy = y2 - y1;
	double t1 = 0, t2 = 1;
	if(cliptest(-dx,x1-xmin,&t1,&t2))
		if (cliptest(dx, xmax - x1, &t1, &t2))
			if (cliptest(-dy, y1 - ymin, &t1, &t2))
				if (cliptest(dy, ymax - y1, &t1, &t2))
				{
					if (t2 < 1)
					{
						x2 = x1 + dx * t2;
						y2 = y1 + dy * t2;
					}

					if (t1 > 0)
					{
						x1 = x1 + dx * t1;
						y1 = y1 + dy * t1;
					}
					cout << dx << " " << dy << endl;
					cout << t1 << " " << x1 << " " << y1 << endl;
					cout << t2 << " " << x2 << " " << y2 << endl;
					float sx = (xvmax - xvmin) / (xmax - xmin);
					float sy = (yvmax - yvmin) / (ymax - ymin);
					float vx1 = xvmin + (x1 - xmin) * sx;
					float vy1 = yvmin + (y1 - ymin) * sy;
					float vx2 = xvmin + (x2 - xmin) * sx;
					float vy2 = yvmin + (y2 - ymin) * sy;

					glColor3f(1, 0, 0);
					glBegin(GL_LINES);
					glVertex2f(vx1, vy1);
					glVertex2f(vx2, vy2);
					glEnd();
				}
		
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0, 0, 0);
	glBegin(GL_LINE_LOOP);
	glVertex2f(xmin, ymin);
	glVertex2f(xmax, ymin);
	glVertex2f(xmax, ymax);
	glVertex2f(xmin, ymax);
	glEnd();

	for (int i = 0; i < n; i++)
	{
		glBegin(GL_LINES);
		glVertex2f(ls[i].x1, ls[i].y1);
		glVertex2f(ls[i].x2, ls[i].y2);
		glEnd();
	}

	for (int i = 0; i < n; i++)
		liangbarsky(ls[i].x1, ls[i].y1, ls[i].x2, ls[i].y2);
	glFlush();
}

void init()
{
	glClearColor(1, 1, 1, 1);
	gluOrtho2D(0, 600, 0, 600);
}

int main(int argc, char** argv)
{
	cout << "Enter Window Coordinates : (xmin ymin xmax ymax)" << endl;
	cin >> xmin >> ymin >> xmax >> ymax;
	cout << "Enter Viewport Coordinates : (xvmin yvmin xvmax yvmax)" << endl;
	cin >> xvmin >> yvmin >> xvmax >> yvmax;

	cout << "Enter number of lines : " << endl;
	cin >> n;
	cout << "Enter coordinates of the lines :" << endl;
	for (int i = 0; i < n; i++)
		cin >> ls[i].x1 >> ls[i].y1 >> ls[i].x2 >> ls[i].y2;

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(600, 600);
	glutCreateWindow("Liang Barsky");
	glutDisplayFunc(display);
	init();
	glutMainLoop();
	return 0;
}