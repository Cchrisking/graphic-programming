#include "header/header.h"
#include "header/implement.h"
typedef struct bordure{
  float y;
  float x;
  float m;
  struct bordure* suivant;
}LCA;
typedef struct{
  LCA* tab;
  int tab_size;
}SI;
  //parametre translation
  int polygon[][2]={{-80,-120},{-80,-40},{0,0},{-80,40},{80,120}};
  int n=(sizeof(polygon)/sizeof(int))/2;
  int tx=30,ty=30;
  //parametre scaling
  float dX=2,dY=2.2;
  //parametre rotation
  float theta=300;
int main(int argc, char** argv){
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
  glutInitWindowSize(WIDTH, HEIGHT);
  glutCreateWindow("Fixed Rectangle");
  glutDisplayFunc(window_display);
  glutReshapeFunc(window_reshape);
  glutMainLoop();
  return 0;
}
void window_reshape(int width, int height){
  glViewport(0,0, WIDTH, HEIGHT);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-WIDTH/2, WIDTH/2, -HEIGHT/2, HEIGHT/2, -1.0 , 1.0);
  glMatrixMode(GL_MODELVIEW);
}
void window_display(){
  glClear(GL_COLOR_BUFFER_BIT);
  glLoadIdentity();
  render_scene();
  rotation(polygon,n,theta,0.0,1.0,0.0);
  scaling(polygon,n,2.0,2.0,0.0,0.0,1.0);
  translation(polygon,n,100.0,2.0,1.,0.0,0.0);
  glFlush();
}
void render_scene(){
  glBegin(GL_LINE_LOOP);
  glColor3f(1.0,0.8,0.9);
    glVertex2f(-80,-120);
    glVertex2f(-80,-40);
    glVertex2f(0,0);
    glVertex2f(-80,40);
    glVertex2f(80,120);
  glEnd();
}
void intersection(int xa, int ya, int xb, int yb,float r,float g,float b){
  float m;
  int x, y;
  int coordx[WIDTH];
  int coordy[HEIGHT];
  if(ya>yb){
    int t=xa;
    xa=xb;
    xb=t;
    t=ya;
    ya=yb;
    yb=t;
  }
  if(delta(yb,ya)==0){
    m=delta(xb, xa);
  }else{
    m=delta(xb,xa)/delta(yb, ya);
  }
  x=xa;
  for(y=ya; y<yb; y++){
    if(x<coordy[y]){
      coordy[y]=x;
    }
    if(x>coordx[y]){
      coordx[y]=x;
    }
    x+=m;
  }
}
//translation
void translation(int polygon[][2],int n,float dx,float dy, float r, float g, float b){
    float poly_final[n][2];
    for(int i=0;i<n;i++){
        poly_final[i][0]=polygon[i][0]+dx;
        poly_final[i][1]=polygon[i][1]+dy;
    }
    for(int i=0;i<n;i++){
    }
    for(int i=0;i<n;i++){
        if(i==n-1){
            segment_bresenham_general(poly_final[i][0],poly_final[i][1],poly_final[0][0],poly_final[0][1], r,g,b);
        }
        else{
            segment_bresenham_general(poly_final[i][0],poly_final[i][1],poly_final[i+1][0],poly_final[i+1][1],r,g,b);
        }
    }
}
//mise àl'échelle
void scaling(int polygon[][2],int n,float dX,float dY,float r, float g, float b){
    float poly_final[n][2];
    for(int i=0;i<n;i++){
        poly_final[i][0]=polygon[i][0]*dX;
        poly_final[i][1]=polygon[i][1]*dY;
    }
    for(int i=0;i<n;i++){
    }
    for(int i=0;i<n;i++){
        if(i==n-1){
            segment_bresenham_general(poly_final[i][0],poly_final[i][1],poly_final[0][0],poly_final[0][1],r,g,b);
        }
        else{
            segment_bresenham_general(poly_final[i][0],poly_final[i][1],poly_final[i+1][0],poly_final[i+1][1],r,g,b);
        }
    }
}
//rotation autour du premier point
void rotation(int polygon[][2],int n,float theta,float r,float g,float b){
   float poly_final[5][2];
   int nn=n;
    for(int i=0;i<nn;i++){
        if(i==0){
            poly_final[i][0]=polygon[i][0];
            poly_final[i][1]=polygon[i][i];
        }
        else{
            poly_final[i][0]=polygon[i][0]*cos(theta)-polygon[i][1]*sin(theta);
            poly_final[i][1]=polygon[i][0]*sin(theta)+polygon[i][1]*cos(theta);
        }
    }
    for(int i=0;i<nn;i++){
        if(i==nn-1){
            segment_bresenham_general(poly_final[i][0],poly_final[i][1],poly_final[0][0],poly_final[0][1],r,g,b);
        }
        else{
            segment_bresenham_general(poly_final[i][0],poly_final[i][1],poly_final[i+1][0],poly_final[i+1][1],r,g,b);
        }
    }
}
