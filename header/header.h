#include<GL/glu.h>
#include<GL/glut.h>
#include<stdio.h>
#define MAX_POINT_ON_FRAME 1000
#define WIDTH 500
#define HEIGHT 500
typedef struct{
  GLfloat tabPos [MAX_POINT_ON_FRAME][2];
  int tab_size;
}PointCloud;
PointCloud point;
void init_point(PointCloud* point){
  point->tab_size=0;
}
void add_points(PointCloud *point, int x, int y){
  if (point->tab_size<MAX_POINT_ON_FRAME){
    point->tabPos[point->tab_size][0]=x;
    point->tabPos[point->tab_size][1]=y;
    point->tab_size+=1;
  }else{
    printf("\t maximum de point eteint\n");
  }
}
void remove_points(PointCloud *point, int x, int y){
  if(point->tab_size>0){
    point->tab_size=(point->tab_size)-1;
  }
}
void point_milieu_cercle(int r);
void segment_naif(int xa, int ya, int xb, int yb);
void segment_incrementale(int xa, int ya, int xb, int yb);
void segment_bresenham(int xa, int ya, int xb, int yb);
void window_reshape(int width, int height);
void render_scene();
void draw_lines();
void draw_pixel(float x, float y);
void window_display();
void mouse_click(int bouton, int state, int x, int y);
void keyboard_press (unsigned char key , int x , int y);
int calcule_code ( int x , int y , int xmin , int ymin , int xmax , int ymax);
