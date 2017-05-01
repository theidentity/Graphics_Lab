#include <GL/glut.h>
#include <iostream>
using namespace std;


// double x1=50,y1=200,x2=500,y2=300;
double x1=200,y1=50,x2=500,y2=300;
// double px1 = 50,py1=200,px2=500,py2=300;
double px1 = 200,py1=50,px2=500,py2=300;
double xmin=100,ymin=100,xmax=400,ymax=400;

void Init()
{
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(50,50);
	glutInitWindowSize(600,600);
	glutCreateWindow("Line Clipping");
	gluOrtho2D(0,600,0,600);
	glClearColor(0,0,0,1);
}

int getCode(double x,double y)
{
	int code = 0;
	if(y>ymax)
		code = code | 8;
	if(y<ymin)
		code = code | 4;
	if(x>xmax)
		code = code | 2;
	if(x<xmin)
		code = code | 1;
	return code;
}


void clip()
{
	int c1 = getCode(px1,py1);
	int c2 = getCode(px2,py2);
	double m = (py2-py1)/(px2-px1);
	double c = py1 - m*px1;

	while((c1|c2)>0)
	{
		if((c1&c2)>0){
			px1 = px2 = py1 = py2 = 0;
			return;
		}

		double x = px1;
		double y = py1;
		int code = c1;
		cout <<c1<<"|"<<c2<<"|"<<code<<endl;

		if(code==0){
			x = px2;
			y = py2;
			code = c2;
		}
		if((code & 8) > 0){
			y = ymax;
			x = (y-c)/m;
		}
		else if((code & 4) > 0){
			y = ymin;
			x = (y-c)/m;
		}
		else if((code & 2) > 0){
			x = xmax;
			y = m*x+c;
		}
		else if((code & 1) > 0){
			x = xmin;
			y = m*x+c;
		}

		if(code==c1){
			px1 = x;
			py1 = y;
			c1 = getCode(px1,py1);
			x = px2;
			y = py2;
			c = y - m*x;
		}
		else if (code==c2){
			px2 = x;
			py2 = y;
			c2 = getCode(px2,py2);
			return;
		}
	}


}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(255,0,0);
	glBegin(GL_LINE_LOOP);
		glVertex2d(100,100);
		glVertex2d(400,100);
		glVertex2d(400,400);
		glVertex2d(100,400);
	glEnd();
	glFlush();
	// glColor3f(0,255,0);
	// glLineWidth(2);
	// glBegin(GL_LINES);
	// 	glVertex2d(x1,y1);
	// 	glVertex2d(x2,y2);
	// glEnd();
	// glFlush();
	glColor3f(0,0,255);
	glLineWidth(1);
	glBegin(GL_LINES);
		glVertex2d(px1,py1);
		glVertex2d(px2,py2);
	glEnd();
	glFlush();
}

int main(int argc,char **argv)
{
	glutInit(&argc,argv);
	Init();
	clip();
	glutDisplayFunc(display);
	glutMainLoop();
	return 0;
}