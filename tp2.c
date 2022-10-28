#include "header/header.h"
int point_depart=0;
PointCloud droite;
int main(int argc, char** argv){
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
  glutInitWindowSize(WIDTH, HEIGHT);
  glutCreateWindow("Fixed Rectangle");
  glutDisplayFunc(window_display);
  glutReshapeFunc(window_reshape);
  glutMouseFunc(mouse_click);
  glutKeyboardFunc(keyboard_press);
  glutMainLoop();
  return 0;
}
void window_reshape(int width, int height){
  glViewport(0,0, width, height);
  glPointSize(15.0);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0, WIDTH, HEIGHT, 0, -1.0,1.0);
  //glOrtho(axe x, axe y, axe z)
  glMatrixMode(GL_MODELVIEW);
}
void window_display(){
  glClear(GL_COLOR_BUFFER_BIT);
  glLoadIdentity();
  draw_pixel();
  glFlush();
}
/*2 Dessiner avec souris glBegin(GL_POLYGON) pour Dessiner polygone GL_LINES pour ligne droit */
void draw_pixel(){
  glColor3f(1.0, 1.0,1.0);
  glPointSize(25.0f);
  glBegin(GL_POINTS);
  for (int i= point_depart; i < point.tab_size; i++) {
    glVertex2i(point.tabPos[i][0],point.tabPos[i][1]);
  }
  glEnd();
}
void draw_lines(){
  glBegin(GL_LINES);
  glEnd;
}
/*void segment(GLfloat xa, GLfloat xb, GLfloat ya, GLfloat yb){
  GLfloat m= (yb - ya) / (xb - xa);
  GLfloat b=  ya - m*xa ;
  int x,y;
  glBegin(GL_POINTS);
  for(x=xa; x<xb; x++){
    y=(m*x+b);
    //AffichePixel(x, y, c)
    draw_lines();
  }
}*/
void mouse_click(int bouton, int state, int x, int y){
  int xprim=x;//-(WIDTH/2);
  int yprim=y;//-1*(y-(HEIGHT/2));
  /*ajoute un point dans structure de donnee*/
  if(state==GLUT_DOWN && bouton ==GLUT_LEFT_BUTTON){
    add_points(&point, xprim, yprim);
  }
  /*click droit supprime le derniere point dans la structure*/
  if(state==GLUT_DOWN && bouton == GLUT_RIGHT_BUTTON){
    remove_points(&point, xprim, yprim);
  }
  glutPostRedisplay();
}
/*ajoute un poit si o click sur espace*/
void keyboard_press (unsigned char key , int x , int y ){
  int xprim=x-(WIDTH/2);
  int yprim=-1*(y-(HEIGHT/2));
  if(key==32||key==112||key==80){
    add_points(&point, xprim, yprim);
  }
  glutPostRedisplay();
}
