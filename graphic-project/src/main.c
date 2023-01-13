#include "../header/header.h"
int main(int argc, char** argv) {
  PointCloud control_point;
  PointCloud points[100];
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
  glutInitWindowSize(WIDTH, HEIGHT);
  glutCreateWindow("Fixed Rectangle");
  glutDisplayFunc(window_display);
  glutReshapeFunc(window_reshape);
  glutMainLoop();
  return 0;
  }
  void window_reshape(){
    glViewport(0,0, WIDTH, HEIGHT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-WIDTH/2, WIDTH/2, -HEIGHT/2, HEIGHT/2, -250.0 , 250.0);
    glMatrixMode(GL_MODELVIEW);
  }
  void window_display(){
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    b_spline();
    glFlush();
  }
