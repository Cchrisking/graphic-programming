#include<GL/glu.h>
#include<GL/glut.h>
#define MAX_POINT_ON_FRAME 1000
#define WIDTH 640
#define HEIGHT 520
typedef struct {
  GLfloat tabPos [MAX_POINT_ON_FRAME][2];
  int tab_size;
}PointCloud;
PointCloud point;
void init_point(PointCloud* point){
  point->tab_size=0;
}
void add_points(PointCloud *point, int x, int y);
void window_reshape(int width, int height);
void render_scene();
void draw_lines();
void window_display();
void mouse_click(int bouton, int state, int x, int y);
int main(int argc, char** argv){
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
  glutInitWindowSize(WIDTH, HEIGHT);
  glutCreateWindow("Fixed Rectangle");
  glutDisplayFunc(window_display);
  glutReshapeFunc(window_reshape);
  glutMouseFunc(mouse_click);
  glutMainLoop();
  return 0;
}
void window_reshape(int width, int height){
  glViewport(0,0, width, height);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-width/2, width/2, -height/2, height/2, -width,height);
  //glOrtho(axe x, axe y, axe z)
  glMatrixMode(GL_MODELVIEW);
}
void window_display(){
  glClear(GL_COLOR_BUFFER_BIT);
  glLoadIdentity();
  render_scene();
  draw_lines();
  glFlush();
}
void render_scene(){
    glColor3f(0.0, 0.2,0.0);
    glBegin(GL_POLYGON);
    glVertex2d(-128, -128);
    glVertex2d(128, -128);
    glVertex2d(128, 128);
    glVertex2d(-128, 128);
  glEnd();
}
void draw_lines(){
  glColor3f(0.3, 0.1,0.5);
  glBegin(GL_LINES);
  for (int i= 0; i < point.tab_size; i++) {
    glVertex2d(point.tabPos[i][0],point.tabPos[i][1]);
  }
  glEnd();
}
void mouse_click(int bouton, int state, int x, int y){
  int xprim=x-(WIDTH/2);
  int yprim=-1*(y-(HEIGHT/2));
  if(state==GLUT_DOWN && bouton ==GLUT_LEFT_BUTTON){
    add_points(&point, xprim, yprim);
  }
  glutPostRedisplay();
}
void add_points(PointCloud *point, int x, int y){
  point->tabPos[point->tab_size][0]=x;
  point->tabPos[point->tab_size][1]=y;
  point->tab_size+=1;
}
