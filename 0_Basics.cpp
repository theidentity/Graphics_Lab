#include <GL/glut.h>
#include <iostream>
#include <math.h>
using namespace std;


double points[10][2];

void Init()
{
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(600,600);
	glutInitWindowPosition(0,0);
	glutCreateWindow("Point Plotting");
	glClearColor(0,0,0,1);
	gluOrtho2D(0,600,0,600);
}

void InitPoints()
{
	points[0][0] = 50;
	points[0][1] = 50;

	points[1][0] = 300;
	points[1][1] = 50;

	points[2][0] = 450;
	points[2][1] = 175;

	points[3][0] = 300;
	points[3][1] = 300;

	points[4][0] = 50;
	points[4][1] = 300;

}
void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	// Plotting Points
	glPointSize(10);
	glColor3f(255,0,0);
	glBegin(GL_POINTS);
		for(int i=0;i<5;i++)
			glVertex2d(points[i][0],points[i][1]);
	glEnd();
	glFlush();

	//Line
	glLineWidth(5);
	glColor3f(0,255,0);
	glBegin(GL_LINES);
		glVertex2d(points[0][0],points[0][1]);
		glVertex2d(points[1][0],points[1][1]);
	glEnd();
	glFlush();

	//Line Loop
	glColor3f(0,0,255);
	glLineWidth(1);
	glBegin(GL_LINE_LOOP);
		for(int i=0;i<5;i++)
			glVertex2d(points[i][0],points[i][1]);
	glEnd();
	glFlush();

	//Filled Polygon
	glColor3f(255,127,0);
	glBegin(GL_POLYGON);
		for(int i=0;i<5;i++)
			glVertex2d(points[i][0],points[i][1]);
	glEnd();
	glFlush();

	//Circle
	glLineWidth(3);
	glColor3f(255,0,0);
	int num_seg = 1000;
	int r = 50;
	int cx = 400;
	int cy = 400;
	glBegin(GL_LINE_LOOP);
		for(int i=0;i<num_seg;i++)
		{
			float theta = (2*3.14*i)/(num_seg);
			float x = r * cosf(theta);
			float y = r * sinf(theta);
			glVertex2f(cx+x,cy+y);
		}
	glEnd();
	glFlush();

}
int main(int argc,char **argv)
{
	glutInit(&argc,argv);
	Init();
	InitPoints();
	glutDisplayFunc(display);
	glutMainLoop();
	return 0;
}