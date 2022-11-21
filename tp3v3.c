#include "header/header.h"
int main(int argc, char** argv) {
  init_point(&point);
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
  glutInitWindowSize(WIDTH, HEIGHT);
  glutCreateWindow("Fixed Rectangle");
  glutDisplayFunc(window_display);
  glutReshapeFunc(window_reshape);
  glutMouseFunc(mouse_click);
  glutMainLoop();
  return 0 ;
}
void window_reshape(int width, int height){
  glViewport(0,0,WIDTH,HEIGHT);
  glPointSize(2.0);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-WIDTH/2, WIDTH/2, -HEIGHT/2, HEIGHT/2, -1.0 , 1.0);
  glMatrixMode(GL_MODELVIEW);
}
void window_display(){
  glClear(GL_COLOR_BUFFER_BIT);
  glLoadIdentity();
  segment_bresenham_general(-125, 125, 125, 125);
  segment_bresenham_general(125, 125, 125, -125);
  segment_bresenham_general(-125, 125, -125, -125);
  segment_bresenham_general(-125, -125, 125, -125);
  cohen_sutherland(-60, 180, 60, 180, -125, -125, 125, 125);
  cohen_sutherland(0, 10, 1, 180, -125, -125, 125, 125);
  /*for(int i=0; i < point.tab_size && point.tab_size >=i; i+=2){
      if(point.tab_size>=i+2)
          cohen_sutherland(
            point.tabPos[i][0],
            point.tabPos[i+1][0],
            point.tabPos[i][1],
            point.tabPos[i+1][1],
            -125, -125, 125, 125);
  }*/
  if ((point.tab_size-1)==1|| ((point.tab_size-1)>1&&((point.tab_size-1)%2)!=0)) {
    cohen_sutherland(
      point.tabPos[point.tab_size-1][0],
      point.tabPos[point.tab_size-1][1],
      point.tabPos[point.tab_size-2][0],
      point.tabPos[point.tab_size-2][1],
      -125, -125, 125, 125);
  }
  glFlush();
}
/*2 Dessiner avec souris glBegin(GL_POLYGON) pour Dessiner polygone GL_LINES pour ligne droit */
void draw_pixel(float x, float y){
  glColor3f(1.0, 1.0,1.0);
  glBegin(GL_POINTS);
    glVertex2f(x,y);
  glEnd();
}
float delta(float pointFinal, float pointDepart){
  return pointFinal-pointDepart;
}
codeSeg initCodeSeg(){
    codeSeg codeseg;
    codeseg.somme = 0;
    return codeseg;
}
bool and_bitwise(codeSeg a, codeSeg b){
  return a.somme&b.somme;
}
bool code_compare(codeSeg a, codeSeg b){
    return (a.somme == b.somme && a.droite == b.droite && a.gauche == b.gauche && a.superieur == b.superieur && a.superieur == b.superieur);
}
codeSeg calcul_code ( int x , int y , int xmin , int ymin , int xmax , int ymax) {
codeSeg code = initCodeSeg();
if( x < xmin ){
  code.somme += 1;
  code.gauche = true;
}
if( x > xmax){
  code.somme += 2;
  code.droite = true;
}
if( y < ymin ){
  code.somme += 4;
  code.inferieur = true;
}
if( y > ymax){
  code.somme += 8;
  code.superieur = true;
}
return code ;
}
int somme(codeSeg code){
  return code.somme;
}
bool superieur(codeSeg code){
  return code.superieur;
}
bool inferieur(codeSeg code){
  return code.inferieur;
}
bool gauche(codeSeg code){
  return code.gauche;
}
bool droite(codeSeg code){
  return code.inferieur;
}
void cohen_sutherland(int xa, int ya, int xb, int yb, int xmin, int ymin, int xmax, int ymax){
  int x;
  int y;
  int i=0;
  codeSeg codeA = calcul_code(xa, ya, xmin, ymin, xmax, ymax);
  codeSeg codeB = calcul_code(xb, yb, xmin, ymin, xmax, ymax);
  int m=delta(yb,ya)/delta(xb,xa);
  int accept = false;
  int fin = false;
  while (fin!=true){
    i++;
    printf("we are here in while: %d\n", i);
    /* Tester si le Segment est totalement visible */
    if(somme(codeA)==0 && somme(codeB)==0){
      accept=false;
      fin =true;
      printf("totalement visible: %d\n", i);
    }else if(and_bitwise(codeA,codeB)){
      /* Tester si le Segment est totalement invisible */
        fin=true;
        printf("totalement invisible: %d\n", i);
      }else{
        /* Segment peut être partiellement Visible */
        codeSeg codeExt = codeA;
        accept=true;
        fin=true;
        printf("partiellement visible: %d\n", i);
        if(somme(codeA)==0){
          codeExt = codeB;
        }
// Calcul l’Intersection avec les bords de la fenêtre
        // Déterminer l’intersection avec le côte supérieur de la fenêtre
        if(superieur(codeExt)){
          x = xa + (ymax-ya)/m;
          y = ymax;
        }
        // Déterminer l’intersection avec le côte inférieur de F
        if(inferieur(codeExt)){
          x = xa + (ymin-ya)/m;
          y = ymin;
        }
          // Déterminer l’intersection avec le côte droit de F
          if(droite(codeExt)){
            y = ya + (xmax-xa)*m;
          }
            // Déterminer l’intersection avec le côte gauche de F
            if (gauche(codeExt)){
              y = ya + (xmin-xa)*m;
              x = xmin;
            }
      // Calcul le code la nouvelle extrémité
      if (code_compare(codeExt, codeA)){
        xa=x;
        ya=y;
        codeA = calcul_code(xa, ya, xmin, ymin,xmax,ymax);
      }else{
        xb=x;
        yb=y;
        codeB = calcul_code(xb, yb, xmin, ymin,xmax, ymax);
      }
    }
      if(accept){
        segment_bresenham_general(xa,ya,xb,yb);
      }
    }
}
/* ############################################### */
void segment_bresenham(int xa, int ya, int xb, int yb, int incrx, int incry, float dy, float dx, int inverse){
  float incr_est = 2*dy;
  float incr_nord_est= 2*(dy-dx);
  float dp = 2*(dy -dx);
  float y = ya;
  for (float x=xa; x!=xb; x+=incrx){
      if(inverse==1)
      draw_pixel(x, y);
      else{
      draw_pixel(y,x);
    }
      if(dp<=0){
          dp+=incr_est;
      }
      else{
          y+=incry;
          dp+=incr_nord_est;
      }
  }
}
void segment_bresenham_general(int xa, int ya, int xb, int yb){
  float dx=delta(xb, xa);
  float dy=delta(yb, ya);
  GLfloat incrx, incry;
  if (dx > 0){
    incrx =1;
  }else{
   incrx = -1;
   dx = -dx;
 }
 if(dy > 0){
   incry = 1;
 }else{
   incry = -1;
   dy = -dy;
 }
 if (dx >= dy){
   segment_bresenham(xa, ya, xb, yb,incrx, incry,dy,dx,1);
}else{
      /*Inverser x et y dans l’algorithme précédent */
      segment_bresenham(ya, xa, yb, xb,incry, incrx,dx,dy,0);
}
 }
 void mouse_click(int bouton, int state, int x, int y){
   int click_counter=0;
   GLfloat xprim=x-WIDTH/2;
   GLfloat yprim=-(y-HEIGHT/2);
   if(state==GLUT_DOWN && bouton ==GLUT_LEFT_BUTTON){
     add_points(&point, xprim, yprim);
     click_counter++;
   }
   if(state==GLUT_DOWN && bouton == GLUT_RIGHT_BUTTON){
     remove_points(&point, xprim, yprim);
   }
   if(click_counter%2==0){
     glutPostRedisplay();
 }
}
