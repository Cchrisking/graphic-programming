#include "header/header.h"
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
void main(int argc, char** argv)
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
  glFlush();
}
void render_scene(){
  glBegin(GL_LINE_LOOP);
    glColor3f(1.0,0.8,0.9);
    glVertex2f(-80,-80);
    glVertex2f(-80,115);
    glVertex2f(115,180);
    glVertex2f(180,-80);
  glEnd();
}
void intersection(int xa, int ya, int xb, int yb){
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
    if(x<leftedge[y]){
      leftedge[y]=x;
    }
    if(x>rightedge[y]){
      rightedge[y]=x;
    }
    x+=m;
  }
}
