//*****      BEZIER***** /
#include "../header/header.h"
#include <math.h>
//1
void  discretisation_espace_parametrique(int m, float a, float b, float t[]){
  float pas =(b-a)/m;
  t[0] = a;
  for (int i=1; i<m ; i++){
    t[i] = t[i-1] + pas ;
  }
}
//2
PointCloud calcul_un_point_courbe_bezier( float t, int n, PointCloud p[]){
  float x=0, y=0;
  PointCloud q ;
  for (int i=0; i<n; i++){
  float b = base_bernstein(i, n, t);
   x+=b*p->tabPos[i][0];
   y+=b*p->tabPos[i][1];
 }
   q.tabPos[0][0]= x;
   q.tabPos[0][1]= y;
  return q;
}
void points_courbe_bezier(int m, int n, PointCloud p[], PointCloud q[]){
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
void trassage_courbe_de_bezier(int n, int m, PointCloud p[]){
   PointCloud* q ;//=(Point*)malloc(m+1*sizeof(Point));
   points_courbe_bezier(m, n, p, q);
  for (int i = 0; i < m; i++) {
   printf("x %f, y %f",q->tabPos[i][0],q->tabPos[i][1]);
  }
}
