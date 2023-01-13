void draw_pixel(float x, float y){
  glColor3f(1.0,0.7,0.7);
  glBegin(GL_POINTS);
    glVertex2f(x,y);
  glEnd();
  printf("detective 8\n");
}
