#include "header/header.h"
typedef struct{
  PointCloud pointA;
  PointCloud pointB;
}Segment;
typedef struct{
  Segment* segment;
  int tab_size;
}SegmentList;
/*
@pointFinal xb ou xa
@pointDepart yb ou ya
*/
PointCloud pointA(Segment segment){
  return segment.pointA;
}
PointCloud pointB(Segment segment){
  return segment.pointB;
}
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
  glViewport(0,0, WIDTH, HEIGHT);
  glPointSize(10.0);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-WIDTH/2, WIDTH/2, -HEIGHT/2, HEIGHT/2, -250.0 , 250.0);
  //glOrtho(left x,right x, top y, bottom y, near -z, far z)
  glMatrixMode(GL_MODELVIEW);
}
void window_display(){
  glClear(GL_COLOR_BUFFER_BIT);
  glLoadIdentity();
  //draw_octant();
  /*if((point.tab_size-1)==1|| ((point.tab_size-1)>1&&((point.tab_size-1)%2)!=0)){
    int xa=point.tabPos[point.tab_size-2][0];
    int ya=point.tabPos[point.tab_size-2][1];
    int xb=point.tabPos[point.tab_size-1][0];
    int yb=point.tabPos[point.tab_size-1][1];
    segment_naif(xa,ya,xb,yb);
  }*/
  //point_milieu_cercle(WIDTH/2);
  if((point.tab_size-1)==1|| ((point.tab_size-1)>1&&((point.tab_size-1)%2)!=0)){
    int xa=point.tabPos[point.tab_size-2][0];
    int ya=point.tabPos[point.tab_size-2][1];
    int xb=point.tabPos[point.tab_size-1][0];
    int yb=point.tabPos[point.tab_size-1][1];
    segment_incrementale(xa,ya,xb,yb);
  }
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
  int x,y;
  float dx=delta(xb, xa);
  float dy=delta(yb, ya);
  m=penteDroite(dy,dx);
  b=ya-(m*xa);
  printf("m: %f\n", m);
  printf("b: %f\n", b);
  for(x=xa; x<xb; x++){
    y=(m*x)+b;
    draw_pixel(x,(int)y);
  }
}
void segment_incrementale(int xa, int ya, int xb, int yb){
  GLfloat m,b;
  int x,y;
  int temp;
  float dx=delta(xb, xa);
  float dy=delta(yb, ya);
  m=dy/dx;
  b=(yb-ya)/(xb-xa);
  y=ya;
  printf("m: %f\n", m);
  printf("b: %f\n", b);
  for(x=xa; x<xb; x++){
    draw_pixel(x,y);
    y=y+m;
  }
}
void segment_bresenham(int xa, int ya, int xb, int yb){
  int x,y;
  float dx=delta(xb, xa);
  float dy=delta(yb, ya);
  int incr_est = 2*dy;
  int incr_nord_est = 2*(dy-dx);
  int dp = 2*dy-dx;
  y=ya;
  for(x=xa; x<xb; x++){
    draw_pixel(x,y);
    if(dp <= 0){
      dp=dp + incr_est;
    }else{
      y+= 1;
      dp=dp+incr_nord_est; /*On choisit le pixel Nord Est NE */
    }
  }
}
void segment_bresenham_general(int xa, int ya, int xb, int yb){
  int x,y;
  int temp;
  float dx=delta(xb, xa);
  float dy=delta(yb, ya);
  int incrx, incry;
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
   /* Algorithme précédent */
}else{
      /*Inverser x et y dans l’algorithme précédent */
}
 }
void point_milieu_cercle(int r){
  /*Paramètre formels :
  r : rayon du cercle. Entier(E).
  C : couleur du traçage. Entier (E).
  Variables intermédiaires :
  x, y : Entiers
  d : réel*/
  int x = WIDTH/2;
  int y = HEIGHT/3;
  float d = 5/4 - r; // d / 1 - r
  //draw_pixel(x, y);
  while(y > x ){
    // faire  Octant 2
    if (d < 0){
    d = d + 2*x + 3;
  }
  else{
    d = d + 2*x -2*y + 5;
    y = y-1;
  }
}
  x = x + 1;
  draw_pixel(x, y);
  draw_pixel(x, y);
  draw_pixel(x, -y);
  draw_pixel(-x, y);
  draw_pixel(-x, -y);
  draw_pixel(y, x);
  draw_pixel(y, -x);
  draw_pixel(-y, x);
  draw_pixel(-y, -x);
}
void mouse_click(int bouton, int state, int x, int y){
  /*ajoute un point dans structure de donnee*/
  x=x-(WIDTH/2);
  y=-1*(y-(HEIGHT/2));
  if(state==GLUT_DOWN && bouton ==GLUT_LEFT_BUTTON){
    add_points(&point, x, y);
    printf("X:%d, Y:%d\n",x,y);
  }
  if(state==GLUT_UP && bouton==GLUT_LEFT_BUTTON){
    add_points(&point, x, y);
    printf("up X:%d, Y:%d\n",x,y);
  }
  /*click droit supprime le derniere point dans la structure*/
  if(state==GLUT_DOWN && bouton == GLUT_RIGHT_BUTTON){
    remove_points(&point, x, y);
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
