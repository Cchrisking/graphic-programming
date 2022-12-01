#include "header/header2.h"
#include "header/implement2.h"
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
//1
void  discretisation_espace_parametrique(int m, float a, float b, float t[]){
  float pas =(b-a)/m;
  t[0] = a;
  for (int i=1; i<=m ; i++){
    t[i] = t[i-1] + pas ;
  }
}
//2
Point calcul_un_point_courbe_bezier( float t, int n, Point p[]){
  int x=0, y=0;
   for (i=0; i<n; i++){
   b = base_bernstein(i, n, t);
   x=x+b*p[i].abscisse;
   y=y+b*p[i].ordonnee;
 }
   q.abscisse = x;
   q.ordonnee = y;
  return q;
}
void points_courbe_bezier(int m, int n, Point p[], Point q[]){
   float a = 0;
   float b = 1;
   float t;
   float* tab =(float*)malloc(sizeof(m+1*float));
   discretisation_espace_parametrique(m, a, b, t);
  for (j =0;< m; i++){
   t = tab[i];
   q[j] = calcul_un_point_courbe_bezier(t, n, p);
 }
  free(t);
}
void trassage_courbe_de_bezier(int n, int m, Point p[]){
   Point* q =(Point*)malloc(sizeof(m+1*Point));
   points_courbe_bezier(m, n, p, q)
   afficheCourbe(m,q);
 free(q);
}
