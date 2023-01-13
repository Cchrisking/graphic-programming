#include "header/header2.h"
#include "header/implement2.h"
Point point_controls[4];
int main(int argc, char** argv){
  glutInit(&argc, argv);
  int j=0;
  point_controls[0].abscisse=-150;
  point_controls[0].ordonnee=-100;
  point_controls[1].abscisse=-50;
  point_controls[1].ordonnee=0;
  point_controls[2].abscisse=50;
  point_controls[2].ordonnee=0;
  point_controls[3].abscisse=150;
  point_controls[3].ordonnee=-100;
  glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
  glutInitWindowSize(WIDTH, HEIGHT);
  glutCreateWindow("fucked bezier");
  glutDisplayFunc(window_display);
  glutReshapeFunc(window_reshape);
  printf("Safe ?\n");
  glutMainLoop();
  printf("never here 3\n");
  return 0;
}
void window_reshape(int width, int height){
  glViewport(0,0, WIDTH, HEIGHT);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-WIDTH/2, WIDTH/2, -HEIGHT/2, HEIGHT/2, -250.0 , 250.0);
  glMatrixMode(GL_MODELVIEW);
}
void window_display(){
  glClear(GL_COLOR_BUFFER_BIT);
  glLoadIdentity();
  trassage_courbe_de_bezier(4,4,point_controls);
  glFlush();
}
//1
void  discretisation_espace_parametrique(int m, float a, float b, float t[]){
  float pas =(b-a)/m;
  t[0] = a;
  for (int i=1; i<m ; i++){
    t[i] = t[i-1] + pas ;
  }
}
//2
Point calcul_un_point_courbe_bezier( float t, int n, Point p[]){
  float x=0, y=0;
  Point q ;
  for (int i=0; i<n; i++){
  float b = base_bernstein(i, n, t);
   x+=b*(p[i].abscisse);
   y+=b*(p[i].ordonnee);
 }
   q.abscisse = x;
   q.ordonnee = y;
  return q;
}
void points_courbe_bezier(int m, int n, Point p[], Point q[]){
   float a = 0;
   float b = 1;
   float t;
   float* tab =(float*)malloc(m+1*sizeof(float));
   discretisation_espace_parametrique(m, a, b, tab);
  for (int j =0;j< m; j++){
   t = tab[j];
   q[j] = calcul_un_point_courbe_bezier(t, n, p);
 }
  free(tab);
}
float base_bernstein(int i, int n, float t){
  int factn=factoriel(n);
  int facti=factoriel(i);
  int factni =factoriel(n-i);
  float combinaison = factn/(facti*factni);
  return combinaison*pow(t,i)*pow((1-t),(n-i));
}
int factoriel(int n){
  if(n>=1){
    return n*factoriel(n-1);
  }else{
    return 1;
  }
}
void trassage_courbe_de_bezier(int n, int m, Point p[]){
   Point* q ;//=(Point*)malloc(m+1*sizeof(Point));
   points_courbe_bezier(m, n, p, q);
  for (int i = 0; i < m; i++) {
   draw_pixel(q[i].abscisse, q[i].ordonnee);
  }
}
