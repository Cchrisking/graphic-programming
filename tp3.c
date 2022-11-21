#include <stdio.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdbool.h>
#define MAX_POINTS_ON_FRAME 1000
typedef struct{
    GLfloat tabPos[MAX_POINTS_ON_FRAME][2];
    int tab_size;
}PointCloud;
typedef struct{
    int somme;
    bool gauche;
    bool droite;
    bool inferieur;
    bool superieur;
}codeSeg;
PointCloud pc;
int height = 500;
int width = 500;
int click=0;
void initPointCloud (PointCloud *pc){
    pc->tab_size = 0;
}
codeSeg initCodeSeg(){
    codeSeg codeseg;
    codeseg.somme = 0;
    return codeseg;
}
bool indentiqueCodeSeg(codeSeg a, codeSeg b){
    return (a.somme == b.somme && a.droite == b.droite && a.gauche == b.gauche && a.superieur == b.superieur && a.superieur == b.superieur);
}
void insererPoint(PointCloud *p, float x, float y){
    p->tabPos[p->tab_size][0]=x;
    p->tabPos[p->tab_size][1]=y;
    p->tab_size++;
}
void window_reshape(int width, int height) {
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-width/2, width/2,-height/2, height/2, -1.0 , 1.0);
    glMatrixMode(GL_MODELVIEW);
}
void draw_pixel(float x, float y){
    glBegin(GL_POINTS);
    glVertex2f(x,y);
    glEnd();
}
void bresenham(GLfloat x1, GLfloat x2, GLfloat y1, GLfloat y2, int IncrX,int IncrY, float dx, float dy, int inversion){
    float IncreE = 2*dy;
    float IncreNE= 2*(dy-dx);
    float dp = 2*(dy -dx);
    float y = y1;
    for (float x=x1; x!=x2; x+=IncrX){
        (inversion==1)?draw_pixel(x, y) :draw_pixel(y,x);
        if(dp<=0){
            dp+=IncreE;
        }
        else{
            y+=IncrY;
            dp+=IncreNE;
        }
    }
}
void bresenhamGeneral(GLfloat x1, GLfloat x2, GLfloat y1, GLfloat y2){
    float dy= y2-y1;
    float dx= x2-x1;
    float Incry, Incrx;
    if(dx>0){
        Incrx= 1;
    }
    else{
        Incrx=-1;
        dx=-dx;
    }
    if(dy>0){
        Incry= 1;
    }
    else{
        dy=-dy;
        Incry=-1;
    }
    if(dx>=dy){
        bresenham(x1,x2,y1,y2,Incrx,Incry, dx, dy, 1);
    }
    else{

        bresenham(y1,y2,x1,x2,Incry,Incrx,dy, dx, 0);
    }
}
codeSeg calcule_code (int x, int y, int xmin, int ymin, int xmax, int ymax){
    codeSeg codeSeg = initCodeSeg();
    if (x < xmin){
        codeSeg.somme += 1;
        codeSeg.gauche = true;
    }
    if (x > xmax){
        codeSeg.somme += 2;
        codeSeg.droite = true;
    }
    if ( y < ymin){
        codeSeg.somme += 4;
        codeSeg.inferieur = true;
    }
    if ( y > ymax){
        codeSeg.somme += 8;
        codeSeg.superieur = true;
    }
    return codeSeg;
}
void cohen_sutherland (int Xa, int Ya, int Xb, int Yb, int Xmin, int Ymin, int Xmax, int Ymax){
    int x;
    int y;
    codeSeg codeA = calcule_code(Xa, Ya, Xmin, Ymin, Xmax, Ymax);
    codeSeg codeB = calcule_code(Xb, Yb, Xmin, Ymin, Xmax, Ymax);
    float m = (Yb - Ya)/(Xb - Xa);
    bool accept = false;
    bool fin = false;
    while (fin != true){
        if ((codeA.somme == 0) && (codeB.somme == 0)){
            accept = true;
            fin = true;
        }
        else if (codeA.somme & codeB.somme){
            fin = true;
        }
        else {
            codeSeg codeExt = codeA;
            if (codeA.somme == 0){
                codeExt = codeB;
            }
            if (codeExt.superieur) {
                x = Xa + (Ymax - Ya)/m;
                y = Ymax;
            }
            else {
                if (codeExt.inferieur){
                    x = Xa + (Ymin - Ya)/m;
                    y = Ymin;
                }
                else {
                    if (codeExt.droite){
                        y = Ya + (Xmax - Xa)*m;
                        x = Xmax;
                    }
                    else{
                        if (codeExt.gauche){
                            y = Ya + (Xmin - Xa)*m;
                            x = Xmax;
                        }
                    }
                }
            }
            if (indentiqueCodeSeg(codeExt, codeA)){
                Xa = x;
                Ya = y;
                codeA = calcule_code(Xa, Ya, Xmin, Ymin, Xmax, Ymax);
            }
            else {
                Xb = x;
                Yb = y;
                codeB = calcule_code(Xb, Yb, Xmin, Ymin, Xmax, Ymax);
            }
        }
    }
    if (accept){
        bresenhamGeneral(Xa, Ya, Xb, Yb);
    }
}
void window_display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    bresenhamGeneral(-125, 125, 125, 125);
    bresenhamGeneral(125, 125, 125, -125);
    bresenhamGeneral(-125, 125, -125, -125);
    bresenhamGeneral(-125, -125, 125, -125);
    cohen_sutherland(-60, 180, 60, 180, -125, -125, 125, 125);
    cohen_sutherland(0, 10, 1, 180, -125, -125, 125, 125);
    for(int i=0; i < pc.tab_size && pc.tab_size >=i; i+=2){
        if(pc.tab_size>=i+2)
            cohen_sutherland(pc.tabPos[i][0], pc.tabPos[i+1][0], pc.tabPos[i][1], pc.tabPos[i+1][1], -125, -125, 125, 125);
    }
    glFlush();
}
void mouse_click(int button, int state, int x, int y){
    float x2= x-width/2;
    float y2= -(y-height/2);
    if (button==GLUT_LEFT_BUTTON && state==GLUT_DOWN) {
        insererPoint(&pc, x2, y2);
        click++;
    }
    if(click%2==0)
            glutPostRedisplay();
}
int main(int argc, char** argv) {
    initPointCloud(&pc);
    glutInit (&argc , argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE );
    glutInitWindowSize (height , width) ;
    glutCreateWindow("Fixed Rectangle") ;
    glColor3f(1.0, 1.0, 1.0);
    glutDisplayFunc(window_display);
    glutReshapeFunc(window_reshape);
    glutMouseFunc(mouse_click);
    glutMainLoop();
    return 0 ;
}
