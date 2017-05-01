#include <GL/glut.h>
#include <iostream>
#include <vector>
using namespace std;
const int TOP=8,BOTTOM=4,LEFT=2,RIGHT=1;
double xmin=100,ymin=100,xmax=400,ymax=400;

class Point{
public:
	double x,y;
	Point();
	Point(int a,int b){x=a;y=b;}
};

vector <Point> poly;
vector <Point> clippedPoly;

void InitPolygon()
{
	poly.push_back(Point(50,250));
	poly.push_back(Point(250,50));
	poly.push_back(Point(450,250));
	poly.push_back(Point(250,450));
}

Point getIntersection(Point S,Point E,int clipEdge)
{
	double m,x,y,c;
	m = (E.y-S.y)/(E.x-S.x);
	x = E.x;
	y = E.y;
	c = y - m*x;

	switch(clipEdge)
	{
		case LEFT:
			if(m==0)
				return Point(xmin,E.y);
			x = xmin;
			y = m*x+c;
			return Point(x,y);
			break;
		case RIGHT:
			if(m==0)
				return Point(xmax,E.y);
			x = xmax;
			y = m*x+c;
			return Point(x,y);
			break;
		case TOP:
		cout<<"***"<<endl;
		cout<<E.x<<"|"<<E.y<<endl;
		cout<<S.x<<"|"<<S.y<<endl;

			if(E.x-S.y==0)
				return Point(x,ymax);
			y = ymax;
			x = (y-c)/m;
		cout<<x<<"|"<<y<<endl;
		cout<<"***"<<endl;
			return Point(x,y);
			break;
		case BOTTOM:
			if(E.x-S.y==0)
				return Point(x,ymin);
			y = ymin;
			x = (y-c)/m;
			return Point(x,y);
			break;
	}
	return Point(x,y);
}

vector <Point> clipLeft(vector <Point> inputList)
{
	vector <Point> outputList;
	vector <Point> temp = inputList;
	temp.push_back(inputList[0]);
	for(int i=0;i<(int)temp.size()-1;i++)
	{
		Point A = temp[i];
		Point B = temp[i+1];
		if(A.x < xmin && B.x < xmin)
			continue;
		else if(A.x < xmin && B.x > xmin){
			outputList.push_back(getIntersection(A,B,LEFT));
			outputList.push_back(B);
		}
		else if(A.x > xmin && B.x > xmin)
			outputList.push_back(B);
		else if(A.x > xmin && B.x < xmin)
			outputList.push_back(getIntersection(A,B,LEFT));
	}
	return outputList;
}

vector <Point> clipRight(vector <Point> inputList)
{
	vector <Point> outputList;
	vector <Point> temp = inputList;
	temp.push_back(inputList[0]);
	for(int i=0;i<(int)temp.size()-1;i++)
	{
		Point A = temp[i];
		Point B = temp[i+1];
		if(A.x > xmax && B.x > xmax)
			continue;
		else if(A.x > xmax && B.x < xmax){
			outputList.push_back(getIntersection(A,B,RIGHT));
			outputList.push_back(B);
		}
		else if(A.x < xmax && B.x < xmax)
			outputList.push_back(B);
		else if(A.x < xmax && B.x > xmax)
			outputList.push_back(getIntersection(A,B,RIGHT));
	}
	return outputList;
}

vector <Point> clipBottom(vector <Point> inputList)
{
	vector <Point> outputList;
	vector <Point> temp = inputList;
	temp.push_back(inputList[0]);
	for(int i=0;i<(int)temp.size()-1;i++)
	{
		Point A = temp[i];
		Point B = temp[i+1];
		if(A.y < ymin && B.y < ymin)
			continue;
		else if(A.y < ymin && B.y > ymin){
			outputList.push_back(getIntersection(A,B,BOTTOM));
			outputList.push_back(B);
		}
		else if(A.y > ymin && B.y > ymin)
			outputList.push_back(B);
		else if(A.y > ymin && B.y < ymin)
			outputList.push_back(getIntersection(A,B,BOTTOM));
	}
	return outputList;
}

vector <Point> clipTop(vector <Point> inputList)
{
	vector <Point> outputList;
	vector <Point> temp = inputList;
	temp.push_back(inputList[0]);
	for(int i=0;i<(int)temp.size()-1;i++)
	{
		Point A = temp[i];
		Point B = temp[i+1];
		if(A.y > ymax && B.y > ymax)
			continue;
		else if(A.y > ymax && B.y < ymax){
			outputList.push_back(getIntersection(A,B,TOP));
			outputList.push_back(B);
		}
		else if(A.y < ymax && B.y < ymax)
			outputList.push_back(B);
		else if(A.y < ymax && B.y > ymax)
			outputList.push_back(getIntersection(A,B,TOP));
	}
	return outputList;
}

void print(vector <Point> points)
{
	for(int i=0;i<(int)points.size();i++)
		cout<<points[i].x<<"|"<<points[i].y<<endl;
	cout<<"----"<<endl;
}

void SutherlandHodgeman()
{
	// print(poly);
	clippedPoly = clipLeft(poly);	
	clippedPoly = clipRight(clippedPoly);	
	clippedPoly = clipBottom(clippedPoly);
	clippedPoly = clipTop(clippedPoly);	
}

void Init()
{
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(600,600);
	glutInitWindowPosition(50,50);
	glutCreateWindow("Polygon Clipping");
	gluOrtho2D(0,600,0,600);
	glClearColor(0,0,0,1);
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(255,0,0);
	glBegin(GL_LINE_LOOP);
		glVertex2d(xmin,ymin);
		glVertex2d(xmax,ymin);
		glVertex2d(xmax,ymax);
		glVertex2d(xmin,ymax);
	glEnd();
	glColor3f(0,255,0);
	glBegin(GL_LINE_LOOP);
		for(int i=0;i<(int)poly.size();i++)
			glVertex2d(poly[i].x,poly[i].y);
	glEnd();
	glColor3f(0,0,255);
	glBegin(GL_LINE_LOOP);
		for(int i=0;i<(int)clippedPoly.size();i++)
			glVertex2d(clippedPoly[i].x,clippedPoly[i].y);
	glEnd();
	glFlush();

}
int main(int argc,char**argv)
{
	glutInit(&argc,argv);
	InitPolygon();
	SutherlandHodgeman();
	Init();
	glutDisplayFunc(display);
	glutMainLoop();
	return 0;
}