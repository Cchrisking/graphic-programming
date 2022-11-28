#include "header/header.h"
#include "header/implement.h"
int cercle=1;
void window_reshape(int width, int height){
  glViewport(0,0,WIDTH,HEIGHT);
  glPointSize(2.0);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-WIDTH/2, WIDTH/2, -HEIGHT/2, HEIGHT/2, -250.0 , 250.0);
  glMatrixMode(GL_MODELVIEW);
}
void window_display(){
  glClear(GL_COLOR_BUFFER_BIT);
  glLoadIdentity();
  if(cercle==0){
    for(int i=1; i<point.tab_size; i++){
  if ((point.tab_size-i)==1|| ((point.tab_size-i)>1&&((point.tab_size-i)%2)!=0)) {
    segment_bresenham_general(
      point.tabPos[point.tab_size-i][0],
      point.tabPos[point.tab_size-i][1],
      point.tabPos[point.tab_size-(i+1)][0],
      point.tabPos[point.tab_size-(i+1)][1]);
  }
}
}else{
  point_milieu_cercle(point.tabPos[point.tab_size-1][0]);
}
  glFlush();
}
void segment_naif(int xa, int ya, int xb, int yb, float r, float g, float b){
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
    draw_pixel(x,partie_entiere(y),r,g,b);
  }
}
void segment_incrementale(int xa, int ya, int xb, int yb, float r, float g, float b){
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
    draw_pixel(x,partie_entiere(y),r,g,b);
    y=y+m;
  }
}
void point_milieu_cercle(float rayon, float r, float g, float b){
  float x = 0;
  float y = rayon;
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
  draw_pixel(x, y,r,g,b);
  draw_pixel(x, -y,r,g,b);
  draw_pixel(-x, y,r,g,b);
  draw_pixel(-x, -y,r,g,b);
  draw_pixel(y, x,r,g,b);
  draw_pixel(y, -x,r,g,b);
  draw_pixel(-y, x,r,g,b);
  draw_pixel(-y, -x,r,g,b);
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
  if(cercle==0){
    if(click_counter%2==0){
  }
}else{
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
