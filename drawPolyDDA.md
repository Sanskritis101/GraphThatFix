```C++ 
#include<GL/glut.h>
#include<stdio.h>
#include<math.h>
#include<iostream>
using namespace std;
int n;
typedef struct{
 float x;
 float y;
}Point2D;
Point2D p1,p2,p3,p4,p5;
void init()
{
glClearColor(0.0,0.0,0.0,0.0);
glMatrixMode(GL_PROJECTION);
//glLoadIdentity();
gluOrtho2D(0,500,0,500);
}
void setPixel(GLint x,GLint y)
{
//glColor3f(0,1,1);
glBegin(GL_POINTS);
glVertex2f(x,y);
glEnd();
}
void LineWithDDA(int x0,int y0,int x1,int y1)
{
int dy=y1-y0;
int dx=x1-x0;
int steps,i;
float xinc,yinc,x=x0,y=y0;
if(abs(dx)>abs(dy))
{
steps=abs(dx);
}
else
{
steps=abs(dy);
}
xinc=(float)dx/(float)steps;
yinc=(float)dy/(float)steps;
setPixel(round(x),round(y));
for(i=0;i<steps;i++)
{
x+=xinc;
y+=yinc;
setPixel(round(x),round(y));
}
glutSwapBuffers();
}
int k=1;
int X[10],Y[10];
int first=0;
int i=1;
void mouseClick(int button, int state, int x, int y)
{
if(button==GLUT_LEFT_BUTTON)
 if(state==GLUT_DOWN)
 {
 switch(first)
 {
 case 0:
 p1.x=x;
 p1.y=(500-y);
 first=1;
 break;
 case 1:
 p2.x=x;
 p2.y=500-y;
 first=2;
 LineWithDDA(p1.x,p1.y,p2.x,p2.y);
 break;
 case 2:
 p3.x=x;
 p3.y=500-y;
 LineWithDDA(p2.x,p2.y,p3.x,p3.y);
 first=3;
 break;
 case 3:
 p4.x=x;
 p4.y=500-y;
 LineWithDDA(p3.x,p3.y,p4.x,p4.y);
 first=4;
 break;
 case 4:
 p5.x=x;
 p5.y=500-y;
 first=0;
 LineWithDDA(p4.x,p4.y,p5.x,p5.y);
 LineWithDDA(p1.x,p1.y,p5.x,p5.y);
 break;
 }
 }
}
void Display()
{
glClearColor(0,0,0,0);
glClear(GL_COLOR_BUFFER_BIT);
//LineWithDDA(0,0,50,50);
glFlush();
}
int main(int argc,char** argv)
{
glutInit(&argc,argv);
glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
glutInitWindowPosition(50,50);
glutInitWindowSize(500,500);
glutCreateWindow("polygon...");
init();
glutDisplayFunc(Display);
glutMouseFunc(mouseClick);
glutMainLoop();
return 0;
}
```

