#include<GL/glu.h>
#include<GL/glut.h>
#include<stdio.h>
#include<stdbool.h>
#include<math.h>
#include<float.h>
#define MAX_POINT_ON_FRAME 9000000
#define WIDTH 500
#define HEIGHT 500
typedef struct{
  GLfloat tabPos [MAX_POINT_ON_FRAME][2];
  int tab_size;
}PointCloud;
typedef struct{
  float abscisse;
  float ordonnee;
}Point;
PointCloud point;
void init_point(PointCloud* point){
  point->tab_size=0;
}
typedef struct{
    int somme;
    bool gauche;
    bool droite;
    bool inferieur;
    bool superieur;
}codeSeg;
void add_points_control(Point *point, float x, float y,int n);
void remove_points_control();
float delta(float pointFinal, float pointDepart);
void point_milieu_cercle(float rayon, float r, float g, float b);
void segment_naif(int xa, int ya, int xb, int yb, float r, float g, float b);
void segment_incrementale(int xa, int ya, int xb, int yb, float r, float g, float b);
void segment_bresenham(int xa, int ya, int xb, int yb, int incrx, int incry, float dy, float dx, int inverse, float r, float g, float b);
void segment_bresenham_general(int xa, int ya, int xb, int yb, float r, float g, float b);
void window_reshape(int width, int height);
void draw_pixel(float x, float y);
void window_display();
void mouse_click(int bouton, int state, int x, int y);
/**
Partie 2 courbe de Bezier
**/
int factoriel(int n);
float base_bernstein(int i, int n, float t);
//1
void  discretisation_espace_parametrique(int m, float a, float b, float t[]);
//2
Point calcul_un_point_courbe_bezier( float t, int n, Point p[]);
//3
void points_courbe_bezier(int m, int n, Point p[], Point q[]);
//4
void trassage_courbe_de_bezier(int n, int m, Point p[]);
