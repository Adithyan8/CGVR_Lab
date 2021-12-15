#include<stdlib.h>
#include<gl/glut.h>
#include<iostream>
#include<math.h>
#define PI 3.14159

using namespace std;

void drawSphere()
{
	double c = PI / 180, x, y, z, theta, phi;
	//Lower Latitudes
	for (phi = -80; phi <= 80; phi += 10)
	{
		glColor3f(0, 0, 1);
		glBegin(GL_QUAD_STRIP);
		for (theta = -180; theta <= 180; theta += 10)
		{
			x = sin(c * theta) * cos(c * phi);
			y = cos(c * theta) * cos(c * phi);
			z = sin(c * phi);
			glVertex3d(x, y, z);
			x = sin(c * theta) * cos(c * (phi+20));
			y = cos(c * theta) * cos(c * (phi+20));
			z = sin(c * (phi+20));
			glVertex3d(x, y, z);
		}
		glEnd();
	}

	//North Pole
	x = y = 0; z = 1;
	glColor3f(1, 0, 0);
	glBegin(GL_TRIANGLE_FAN);
	glVertex3f(x, y, z);
	z = sin(c * 80);
	for (theta = -180; theta <= 180; theta += 10)
	{
		x = sin(c * theta) * cos(c * 80);
		y = cos(c * theta) * cos(c * 80);
		glVertex3f(x, y, z);
	}
	glEnd();

	//South Pole
	x = y = 0; z = -1;
	glColor3f(1, 0, 0);
	glBegin(GL_TRIANGLE_FAN);
	glVertex3f(x, y, z);
	z = -1 * sin(c * 80);
	for (theta = -180; theta <= 180; theta += 10)
	{
		x = sin(c * theta) * cos(c * 80);
		y = cos(c * theta) * cos(c * 80);
		glVertex3f(x, y, z);
	}
	glEnd();
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // the quad doesn't get filled up and only boundary appears
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0.0, 0.0, -1);
	// change the below parameter to control the viewing angle
	glRotatef(60.0, 0.0, 1.0, 1.0); // rotate by how much angle and about which axis (angle,x,y,z)

	drawSphere();
	glFlush();
}

void init()
{
	glClearColor(1, 1, 1, 1);
	gluOrtho2D(-300, 300, -300, 300);
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE | GLUT_DEPTH);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(600, 600);
	glutCreateWindow("Spehere");
	glutDisplayFunc(display);
	//glEnable(GL_DEPTH_TEST);
	init();
	glutMainLoop();
	return 0;
}