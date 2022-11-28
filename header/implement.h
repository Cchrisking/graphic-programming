void draw_pixel(float x, float y, float r, float g, float b){
  glColor3f(r,g,b);
  glBegin(GL_POINTS);
    glVertex2f(x,y);
  glEnd();
}
float delta(float b, float a){
  return b-a;
}
float penteDroite(float dy, float dx){
  printf("dy: %f\n", dy);
  printf("dx: %f\n", dx);
  float pente =dy/dx;
  printf("et m : %f\n",dy/dx );
  return pente;
}
int partie_entiere(float reel){
  float entier=0;
  modff(reel, &entier);
  int x=entier;
  return x;
}
void segment_bresenham(int xa, int ya, int xb, int yb, int incrx, int incry, float dy, float dx, int inverse, float r, float g, float b){
  float incr_est = 2*dy;
  float incr_nord_est= 2*(dy-dx);
  float dp = 2*(dy -dx);
  float y = ya;
  for (float x=xa; x!=xb; x+=incrx){
      if(inverse==1)
      draw_pixel(x, y,r,g,b);
      else{
      draw_pixel(y,x,r,g,b);
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
void segment_bresenham_general(int xa, int ya, int xb, int yb, float r, float g, float b){
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
   segment_bresenham(xa, ya, xb, yb,incrx, incry,dy,dx,1,r,g,b);
}else{
      /*Inverser x et y dans l’algorithme précédent */
      segment_bresenham(ya, xa, yb, xb,incry, incrx,dx,dy,0,r,g,b);
}
 }
