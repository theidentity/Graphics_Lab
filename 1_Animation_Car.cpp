#include <GL/glut.h>
#include <iostream>
#include <unistd.h>
#include <math.h>
using namespace std;
#define PI 3.142

void Init()
{
  glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
  glutInitWindowSize(600,600);
  glutInitWindowPosition(50,50);
  glutCreateWindow("Car");
  gluOrtho2D(0,600,0,600);
  glClearColor(0,0,0,1);
}

void DrawCar(int tx,int ty,int r)
{
  // Car
  glBegin(GL_LINE_LOOP);
    glVertex2d(0+tx,0+ty);
    glVertex2d(0+tx,40+ty);
    glVertex2d(80+tx,80+ty);
    glVertex2d(180+tx,80+ty);
    glVertex2d(220+tx,40+ty);
    glVertex2d(260+tx,40+ty);
    glVertex2d(260+tx,0+ty);
  glEnd();
  // Wheel Left
  int radius = 20;
  int num_seg = 200;
  int cx=40, cy=0;
  glBegin(GL_LINE_LOOP);
    for(int i=0;i<num_seg;i++){
      double theta = 2*PI*i/num_seg;
      double x,y;
      x = radius*cosf(theta);
      y = radius*sinf(theta);
      glVertex2d(x+cx+tx,y+cy+ty);
    }
  glEnd();
  // Wheel Right
  radius = 20;
  num_seg = 200;
  cx = 200;cy=0;
  glBegin(GL_LINE_LOOP);
    for(int i=0;i<num_seg;i++){
      double theta = 2*PI*i/num_seg;
      double x,y;
      x = radius*cosf(theta);
      y = radius*sinf(theta);
      glVertex2d(x+cx+tx,y+cy+ty);
    }
  glEnd();
  // Spoke Left
  radius = 20;
  num_seg = 3;
  cx = 40,cy = 0;
  glBegin(GL_LINES);
    for(int i=0;i<num_seg;i++){
      double theta = 2*PI*i/num_seg;
      double x,y;
      x = radius*cosf(theta+r);
      y = radius*sinf(theta+r);
      glVertex2d(cx+x+tx,cy+y+ty);
      glVertex2d(cx-x+tx,cy-y+ty);
    }
  glEnd();
  // Spoke Right
  radius = 20;
  num_seg = 3;
  cx = 200,cy = 0;
  glBegin(GL_LINES);
    for(int i=0;i<num_seg;i++){
      double theta = 2*PI*i/num_seg;
      double x,y;
      x = radius*cosf(theta+r);
      y = radius*sinf(theta+r);
      glVertex2d(cx+x+tx,cy+y+ty);
      glVertex2d(cx-x+tx,cy-y+ty);
    }
  glEnd();

}
void display(void)
{
  glClear(GL_COLOR_BUFFER_BIT);
  int rot = 10;
  for(int i=0;i<10000;i++,rot+=10){
    glClear(GL_COLOR_BUFFER_BIT);
    DrawCar(i,100,rot);
    usleep(100000);
    glFlush();
  }
}
int main(int argc,char **argv)
{
  glutInit(&argc,argv);
  Init();
  glutDisplayFunc(display);
  glutMainLoop();
  return 0;
}
