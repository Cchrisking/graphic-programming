#include <stdio.h>
int partie_entiere(float x){
  int i=(int)x;
  /*if(i>x){
    i-=1;
  }*/
  return i;
}
int main(int argc, char const *argv[]) {
  printf("Partie entienere 3.2 %d\n", partie_entiere(3.2));
  printf("Partie entienere 3.5 %d\n", partie_entiere(3.5));
  printf("Partie entienere 3.7 %d\n", partie_entiere(3.7));
  printf("Partie entienere 3.2 %d\n", partie_entiere(-3.2));
  return 0;
}
