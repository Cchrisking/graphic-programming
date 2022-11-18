#include <header.h>
int main(int argc, char const *argv[]) {

  return 0;
}
int calcule_code ( int x , int y , int xmin , int ymin , int xmax , int ymax) {
int code = 0 ;
if( x < xmin )
code += 1 ;
if( x > xmax)
code += 2 ;
if( y < ymin )
code += 4 ;
if( y > ymax)
code += 8 ;
return code ;
}
void cohen_sutherland(int xa, int ya, int xb, int yb, int xmin, int ymin, int xmax, int ymax){
  int codeA=calcule_code(xa, ya);
  int codeB=calcule_code(xb, yb);
  int m=;
  int accept = 0;
  int fin = 0;
  while (!fin) {
    if(codeA==0 && codeB==0){
      accept=1;
      fin =1;
    }else{
      if((codeA && codeB)==0){
        fin=1;
      }else{
        codeExt = codeA
        if(somme(codeA)==0){
          codeExt = codeB
        }
        if(superieur(codeExt)){
          x = Xa + ( Ymax – Ya)/m;
          y = Ymax;
        }
        // Déterminer l’intersection avec le côte inférieur de F
        if inferieur(codeExt){
          x = xa + ( Ymin– Ya)/m;
          y = Ymin;
        }else{
          if(droite(codeExt)){
            y = Ya + ( Xmax– Xa)*m;
          }else{
            if gauche(codeExt){
              y = Ya + ( Xmin– Xa)*m;
              x = Xmin;
            }
          }
        }
      }
      // Calcul le code la nouvelle extrémité
      if (codeExt == codeA){
        xa=x;
        ya=y;
        codeA = CalculCode(Xa, Ya, Xmin, Ymin,Xmax, Ymax);
      }else{
        CodeB = CalculCode(Xb, Yb, Xmin, Ymin,Xmax, Ymax);
      }
      if(accept){
        AfficheSegment(Xa, Ya, Xb, Yb, attribut);
      }
    }
  }
}
