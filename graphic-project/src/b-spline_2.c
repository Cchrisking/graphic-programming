#include <stdio.h>
#include <stdlib.h>
#include <math.h>
void deboor(int k, float* nodal, float t,float *basisValues);
// Struct for a point in 2D space
typedef struct {
  float x;
  float y;
}Point;
// Struct for a B-spline curve
typedef struct {
  int n; // Number of control points
  Point *points; // Control points
  int k; // Degree of the curve
  float *knots; // Knot vector
} BSplineCurve;
// Evaluate the B-spline curve at the given parameter value
Point evalBSplineCurve(BSplineCurve curve, float t){
  int i, j;
  float *basisValues;
  Point p, q;
  int n = curve.n;
  int k = curve.k;
  Point *points = curve.points;
  float *knots = curve.knots;
  //knots = curve.knots; //malloc((curve.n + curve.k + 1) * sizeof(float));
  //malloc((curve.n + curve.k + 1) * sizeof(float));//
  // Allocate space for the basis values
  basisValues = malloc((curve.n + curve.k + 1) * sizeof(float));
  if(basisValues == NULL) {
    printf("Failed to allocate memory\n");
    exit(1);
  }else{
    printf("size of basis: %ld\n", sizeof(basisValues));
  }
  // Initialize the point to (0, 0)
  p.x = 0;
  p.y = 0;
  printf("Hello break points 4 basisValues: %f et k %d\n", *basisValues, k);
// Compute the basis values using De Boor's algorithm
//  deboor(k,knots,t,basisValues);
//  printf("knots:  %f\n", knots[0]);
for (i = 0; i <= k; i++){
  printf("Hello break points 5 basisValues: %f et k %d\n", *basisValues, k);
    if (t >= knots[i] && t < knots[i + 1]){
      basisValues[i] = 1;
    } else {
      basisValues[i] = 0;
    }
    for (j = i - 1; j >= 0; j--) {
      float left = (t - knots[j]) / (knots[j + k - i + 1] - knots[j]);
      float right = (knots[j + k - i + 2] - t) / (knots[j + k - i + 2] - knots[j + 1]);
      if (basisValues[j] == 0) {
        basisValues[j] = left * basisValues[j + 1];
      } else {
        basisValues[j] = left * basisValues[j + 1] + right * basisValues[j];
      }
    }
  }
// Compute the point on the curve using the basis values and control points
  for (i = 0; i <= k; i++) {
    q.x = points[i].x * basisValues[i];
    q.y = points[i].y * basisValues[i];
    p.x += q.x;
    p.y += q.y;
  }
  // Free the basis values array
  free(basisValues);
  // Return the point on the curve
  return p;
}
void b_spline(){
  //Create a B-spline curve with four control points and degree 3
  BSplineCurve curve;
curve.n = 4;
curve.k = 3;
curve.points = malloc(5 * sizeof(Point));
curve.points[0] = (Point){15, 15};
curve.points[1] = (Point){45, 65};
curve.points[2] = (Point){85, 15};
curve.points[3] = (Point){105,25};
curve.points[4] = (Point){220, 35};
  printf("Hello break point 2\n");
  // Evaluate the curve at t = 0.5
  Point p;/* = evalBSplineCurve(curve, 0.001);*/
  printf("Hello break point 3\n");
  // Print the x, y, and z coordinates of the point on the curve
  float t;
  /*Creation de vecteurs nadales*/
  curve.knots = malloc((curve.n + curve.k + 1) * sizeof(float));
  printf("\nso everything worked out fine\n");
  for (int i = 0; i <= curve.n + curve.k; i++) {
    curve.knots[i] = (float)i;
    printf("Hello %f\n", curve.knots[i]);
  }
  //carefull of curve.knots[] may cause errors
  for(t=0; t<=curve.knots[curve.k+curve.n];t+=0.001){
    p=evalBSplineCurve(curve, t);
    printf("(%f, %f)\n", p.x, p.y);
  }
}
int main() {
  b_spline();
  return 0;
}
void deboor(int k, float* nodal, float t,float *basisValues){
  int i,j;
  for (i = 0; i <= k; i++){
    if (t >= nodal[i] && t < nodal[i + 1]){
      basisValues[i] = 1;
    } else {
      basisValues[i] = 0;
    }
    for (j = i - 1; j >= 0; j--) {
      float left = (t - nodal[j]) / (nodal[j + k - i + 1] - nodal[j]);
      float right = (nodal[j + k - i + 2] - t) / (nodal[j + k - i + 2] - nodal[j + 1]);
      if (basisValues[j] == 0) {
        basisValues[j] = left * basisValues[j + 1];
      } else {
        basisValues[j] = left * basisValues[j + 1] + right * basisValues[j];
      }
    }
  }
}
