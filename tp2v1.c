#include "header/header.h"
float delta(float pointFinal, float pointDepart){
  return pointFinal-pointDepart;
}
float penteDroite(float dy, float dx){
  printf("dy: %f\n", dy);
  printf("dx: %f\n", dx);
  float pente =dy/dx;
  printf("et m : %f\n",dy/dx );
  return pente;
}
int partie_entiere(float reel){
  float entier=0;
  modff(reel, &entier);
  int x=entier;
  return x;
}
void draw_octant(){
  glLineWidth(1);
  glColor3f(1.0, 1.0,1.0);
  glBegin(GL_LINES);
  glVertex2i(WIDTH/2,0);
  glVertex2i(WIDTH/2,HEIGHT);
  glVertex2i(0,HEIGHT/2);
  glVertex2i(WIDTH,HEIGHT/2);
  glVertex2i(0,0);
  glVertex2i(WIDTH,HEIGHT);
  glVertex2i(WIDTH,0);
  glVertex2i(0,HEIGHT);
  glEnd();
}
int point_depart=0;
int main(int argc, char** argv){
  init_point(&point);
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
  glViewport(0,0,WIDTH,HEIGHT);
  glPointSize(2.0);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-WIDTH/2, WIDTH/2, -HEIGHT/2, HEIGHT/2, -1.0 , 1.0);
  glMatrixMode(GL_MODELVIEW);
}
void window_display(){
  glClear(GL_COLOR_BUFFER_BIT);
  glLoadIdentity();
  if ((point.tab_size-1)==1|| ((point.tab_size-1)>1&&((point.tab_size-1)%2)!=0)) {
    segment_bresenham_general(
      point.tabPos[point.tab_size-1][0],
      point.tabPos[point.tab_size-1][1],
      point.tabPos[point.tab_size-2][0],
      point.tabPos[point.tab_size-2][1]);
  }
  /*if (point.tab_size>=1) {
    point_milieu_cercle(point.tabPos[point.tab_size-1][0]);
  }*/
  glFlush();
}
/*2 Dessiner avec souris glBegin(GL_POLYGON) pour Dessiner polygone GL_LINES pour ligne droit */
void draw_pixel(float x, float y){
  glColor3f(1.0, 1.0,1.0);
  glBegin(GL_POINTS);
    glVertex2f(x,y);
  glEnd();
}
void segment_naif(int xa, int ya, int xb, int yb){
  GLfloat m,b;
  float x,y;
  float dx=delta(xb, xa);
  float dy=delta(yb, ya);
  m=penteDroite(dy,dx);
  b=ya-(m*xa);
  printf("m: %f\n", m);
  printf("b: %f\n", b);
  for(x=xa; x<xb; x++){
    y=(m*x)+b;
    draw_pixel(x,partie_entiere(y));
  }
}
void segment_incrementale(int xa, int ya, int xb, int yb){
  GLfloat m,b;
  float x,y;
  int temp;
  float dx=delta(xb, xa);
  float dy=delta(yb, ya);
  m=dy/dx;
  b=(yb-ya)/(xb-xa);
  y=ya;
  printf("m: %f\n", m);
  printf("b: %f\n", b);
  for(x=xa; x<xb; x++){
    draw_pixel(x,partie_entiere(y));
    y=y+m;
  }
}
void segment_bresenham(int xa, int ya, int xb, int yb, int incrx, int incry, float dy, float dx, int inverse){
  float incr_est = 2*dy;
  float incr_nord_est= 2*(dy-dx);
  float dp = 2*(dy -dx);
  float y = ya;
  for (float x=xa; x!=xb; x+=incrx){
      if(inverse==1)
      draw_pixel(x, y);
      else{
      draw_pixel(y,x);
    }
      if(dp<=0){
          dp+=incr_est;
      }
      else{
          y+=incry;
          dp+=incr_nord_est;
      }
  }
}
void segment_bresenham_general(int xa, int ya, int xb, int yb){
  float dx=delta(xb, xa);
  float dy=delta(yb, ya);
  GLfloat incrx, incry;
  if (dx > 0){
    incrx =1;
  }else{
   incrx = -1;
   dx = -dx;
 }
 if(dy > 0){
   incry = 1;
 }else{
   incry = -1;
   dy = -dy;
 }
 if (dx >= dy){
   segment_bresenham(xa, ya, xb, yb,incrx, incry,dy,dx,1);
}else{
      /*Inverser x et y dans l’algorithme précédent */
      segment_bresenham(ya, xa, yb, xb,incry, incrx,dx,dy,0);
}
 }
void point_milieu_cercle(float r){
  float x = 0;
  float y = r;
  float d = 5/4 - r; // d / 1 - r
  while(y > x ){
    if (d < 0){
    d = d + 2*x + 3;
  }
  else{
    d = d + 2*x -2*y + 5;
    y = y-1;
  }
  x = x + 1;
  draw_pixel(x, y);
  draw_pixel(x, -y);
  draw_pixel(-x, y);
  draw_pixel(-x, -y);
  draw_pixel(y, x);
  draw_pixel(y, -x);
  draw_pixel(-y, x);
  draw_pixel(-y, -x);
}
}
void mouse_click(int bouton, int state, int x, int y){
  int click_counter=0;
  GLfloat xprim=x-WIDTH/2;
  GLfloat yprim=-(y-HEIGHT/2);
  if(state==GLUT_DOWN && bouton ==GLUT_LEFT_BUTTON){
    add_points(&point, xprim, yprim);
    click_counter++;
  }
  if(state==GLUT_DOWN && bouton == GLUT_RIGHT_BUTTON){
    remove_points(&point, xprim, yprim);
  }
  /*if(click_counter%2==0){
    glutPostRedisplay();
}*/
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
