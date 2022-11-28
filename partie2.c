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
void  discretisationUP(int m, float a, float b, float t[]){
  float pas =(b-a)/m;
  t[0] = a;
  for (int i=1; i<=m ; i++){
    t[i] = t[i-1] + pas ;
  }
}
Point calcul_un_point_courbe_bezier( float t, int n, Point p){
  int x=0, y=0;
   for (i=0; i<n; i++){
   b = baseBernstein(i, n, t);
   x=x + b*p[i].abscisse;
   y=y+ b*p[i].ordonnee;
 }
   q.abscisse = x;
   q.ordonnee = y;
  return q;
}
void points_courbe_bezier(int m, int n, Point p, Point q[]){
   float a = 0;
   float b = 1;
   float tab[] =malloc(sizeof(m+1*float));
   float t;
   discretisationUP(m, a, b, t);
  for (j =0;< m; i++){
   t = tab[i]
   q[j] = calcul_un_point_courbe_bezier(t, n, p);
 }
  free(t);
}
