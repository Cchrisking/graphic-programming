#include "header/header.h"
#include "header/implement.h"
//translation
void translation(int poly[][2],int n,float dx,float dy){
    float new_poly[n][2];
    for(int i=0;i<n;i++){
        new_poly[i][0]=poly[i][0]+dx;
        new_poly[i][1]=poly[i][1]+dy;
    }
    for(int i=0;i<n;i++){
    }
    for(int i=0;i<n;i++){
        if(i==n-1){
            segment_bresenham_general(new_poly[i][0],new_poly[i][1],new_poly[0][0],new_poly[0][1]);
        }
        else{
            segment_bresenham_general(new_poly[i][0],new_poly[i][1],new_poly[i+1][0],new_poly[i+1][1]);
        }
    }
}
//mise � l'�chelle
void scaling(int poly[][2],int n,float dX,float dY){
    float new_poly[n][2];
    for(int i=0;i<n;i++){
        new_poly[i][0]=poly[i][0]*dX;
        new_poly[i][1]=poly[i][1]*dY;
    }
    for(int i=0;i<n;i++){
    }
    for(int i=0;i<n;i++){
        if(i==n-1){
            segment_bresenham_general(new_poly[i][0],new_poly[i][1],new_poly[0][0],new_poly[0][1]);
        }
        else{
            segment_bresenham_general(new_poly[i][0],new_poly[i][1],new_poly[i+1][0],new_poly[i+1][1]);
        }
    }
}
//rotation autour du premier point
void rotation(int poly[][2],int n,float alpha){
   float new_poly[n][2];
    for(int i=0;i<n;i++){
        if(i==0){
            new_poly[i][0]=poly[i][0];
            new_poly[i][1]=poly[i][i];
        }
        else{
            new_poly[i][0]=poly[i][0]*cos(alpha)-poly[i][1]*sin(alpha);
            new_poly[i][1]=poly[i][0]*sin(alpha)+poly[i][1]*cos(alpha);
        }
    }
    for(int i=0;i<n;i++){
        if(i==n-1){
            segment_bresenham_general(new_poly[i][0],new_poly[i][1],new_poly[0][0],new_poly[0][1]);
        }
        else{
            segment_bresenham_general(new_poly[i][0],new_poly[i][1],new_poly[i+1][0],new_poly[i+1][1]);
        }
    }
}
void window_reshape(int width, int height){
  glViewport(0,0,WIDTH,HEIGHT);
  glPointSize(2.0);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-WIDTH/2, WIDTH/2, -HEIGHT/2, HEIGHT/2, -250.0 , 250.0);
  glMatrixMode(GL_MODELVIEW);
}
//translation
int poly[][2]={{5,10},{10,90},{90,5}};
int n=(sizeof(poly)/sizeof(int))/2;
int tx=30,ty=30;
//scaling
float dX=2,dY=2.2;
//rotation
float alpha=300;
void window_display(){
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    glBegin(GL_LINE_LOOP);
    glVertex2d(5,10);
    glVertex2d(10,90);
    //glVertex2d(100,100);
    glVertex2d(90,5);
    glEnd();
    //translation(poly,n,tx,ty);
    //scaling(poly,n,deltaX,deltaY);
    rotation(poly,n,alpha);
    glFlush();
}
int main(int argc, char** argv){
  init_point(&point);
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
  glutInitWindowSize(WIDTH, HEIGHT);
  glutCreateWindow("Fixed Rectangle");
  glutDisplayFunc(window_display);
  glutReshapeFunc(window_reshape);
  glutMainLoop();
  return 0;
}
