#include<GL/glu.h>
#include<GL/glut.h>
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<math.h>
#include<float.h>
#define MAX_POINT_ON_FRAME 1000
#define WIDTH 500
#define HEIGHT 500
typedef struct{
  GLfloat tabPos [MAX_POINT_ON_FRAME][2];
  int tab_size;
}PointCloud;
// Struct for a point in 2D space
typedef struct {
  float x;
  float y;
}Point;
// Struct for a B-spline curve
typedef struct {
  int n; // Number of control points
  Point *points; // Control points
  int k; // Degree of the curve
  float *knots; // Knot vector
} BSplineCurve;
void window_reshape();
void render_scene();
void render_line();
void draw_lines();
void draw_pixel(float x, float y);
void window_display();
int factoriel(int n);
void deboor(int k, float* nodal, float t,float *basisValues);
Point evalBSplineCurve(BSplineCurve curve, float t);
void b_spline();
/*--- BEZIER ------*/
float base_bernstein(int i, int n, float t);
//1
void  discretisation_espace_parametrique(int m, float a, float b, float t[]);
//2
PointCloud calcul_un_point_courbe_bezier( float t, int n, PointCloud p[]);
//3
void points_courbe_bezier(int m, int n, PointCloud p[], PointCloud q[]);
//4
void trassage_courbe_de_bezier(int n, int m, PointCloud p[]);
