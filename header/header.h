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
void add_points(PointCloud *point, int x, int y){
  point->tabPos[point->tab_size][0]=x;
  point->tabPos[point->tab_size][1]=y;
  point->tab_size+=1;
}
void remove_points(PointCloud *point, int x, int y){
  if(point->tab_size>0){
    point->tab_size=(point->tab_size)-1;
  }
}
void window_reshape(int width, int height);
void render_scene();
void draw_lines();
void draw_pixel();
void window_display();
void mouse_click(int bouton, int state, int x, int y);
void keyboard_press (unsigned char key , int x , int y);
