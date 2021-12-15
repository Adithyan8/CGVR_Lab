#include<stdlib.h>
#include<gl/glut.h>
#include<iostream>

const int RIGHT = 2;
const int LEFT = 1;
const int TOP = 8;
const int BOTTOM = 4;

using namespace std;

int n;
float xmin, xmax, ymin, ymax, xvmin, yvmin, xvmax, yvmax;

struct line
{
	float x1, y1, x2, y2;
};
line ls[10];

int computeregcode(float x1, float y1)
{
	int regcode=0;
	if (x1 > xmax) regcode |= RIGHT;
	if (x1 < xmin) regcode |= LEFT;
	if (y1 > ymax) regcode |= TOP;
	if (y1 < ymin) regcode |= BOTTOM;
	return regcode;
}

void cohensutherland(float x1, float y1, float x2, float y2)
{
	int regcode1 = computeregcode(x1, y1), regcode2 = computeregcode(x2, y2), regcodeout;
	bool accept = false, done = false;

	while (!done)
	{
		if (regcode1 == 0 && regcode2 == 0)
		{
			accept = true;
			done = true;
		}
		else if (regcode1 & regcode2)
		{
			done = true;
		}
		else
		{
			float x, y;
			regcodeout = regcode1 != 0 ? regcode1 : regcode2;
			if (regcodeout & TOP)
			{
				y = ymax;
				x = x1 + (ymax - y1) * (x2 - x1) / (y2 - y1);
			}
			else if(regcodeout & BOTTOM)
			{
				y = ymin;
				x = x1 + (ymin - y1) * (x2 - x1) / (y2 - y1);
			}
			else if (regcodeout & RIGHT)
			{
				x = xmax;
				y = y1 + (xmax - x1) * (y2 - y1) / (x2 - x1);
			}
			else if (regcodeout & LEFT)
			{
				x = xmin;
				y = y1 + (xmin - x1) * (y2 - y1) / (x2 - x1);
			}

			if (regcodeout == regcode1)
			{
				x1 = x;
				y1 = y;
				regcode1 = computeregcode(x1, y1);
			}
			else 
			{
				x2 = x;
				y2 = y;
				regcode2 = computeregcode(x2, y2);
			}
		}
	}

	if (accept)
	{
		float sx = (xvmax - xvmin) / (xmax - xmin);
		float sy = (yvmax - yvmin) / (ymax - ymin);
		float vx1 = xvmin + (x1 - xmin) * sx;
		float vy1 = yvmin + (y1 - ymin) * sy;
		float vx2 = xvmin + (x2 - xmin) * sx;
		float vy2 = yvmin + (y2 - ymin) * sy;

		glColor3f(1, 0, 0);
		glBegin(GL_LINE_LOOP);
		glVertex2f(xvmin, yvmin);
		glVertex2f(xvmax, yvmin);
		glVertex2f(xvmax, yvmax);
		glVertex2f(xvmin, yvmax);
		glEnd();

		cout << vx1 << " " << vy1 << " " << vx1 << " " << vy2 << endl;
		glColor3f(1, 0, 0);
		glBegin(GL_LINES);
		glVertex2f(vx1, vy1);
		glVertex2f(vx2, vy2);
		glEnd();
	}
}

void display()
{
	cout << "display" << endl;
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
		cohensutherland(ls[i].x1, ls[i].y1, ls[i].x2, ls[i].y2);
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
	glutCreateWindow("Cohen Sutherland");
	glutDisplayFunc(display);
	init();
	glutMainLoop();
	return 0;
}