#include <stdio.h>
#include <stdlib.h>
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
  // Allocate space for the basis values
  basisValues = malloc((n + k + 1) * sizeof(float));
  if(basisValues == NULL) {
    printf("Failed to allocate memory\n");
    exit(1);
  }
  // Initialize the point to (0, 0)
  p.x = 0;
  p.y = 0;
  // Compute the basis values using De Boor's algorithm
  for (i = 0; i <= k; i++){
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
  /**
  Create a B-spline curve with four control points and degree 3
  Here is an example of how to create a B-spline curve with four control points and degree 3 in C:
  **/
//Create a B-spline curve with four control points and degree 3
BSplineCurve curve;
curve.n = 4;
curve.k = 3;
curve.points = malloc(5 * sizeof(Point));
curve.points[0] = (Point){0, 0};
curve.points[1] = (Point){1, 1};
curve.points[2] = (Point){2, 0};
curve.points[3] = (Point){3, 1};
curve.points[4] = (Point){4, 0};
}
/*In this example, we are creating a B-spline curve with 4 control points and a degree of 3. The control points are defined as Point structs, with x and y coordinates. The malloc function is used to allocate memory for the control points, with the size of the memory block being 5 Point structs.
The value of the knots vector depends on the degree, the number of control points, and the type of the spline. The most common types of knots are the open uniform knots, and the closed uniform knots.
You can use the following code snippet to create the knots vector for an open uniform spline.
*/
  curve.knots = malloc((curve.n + curve.k + 1) * sizeof(float));
  for (i = 0; i <= curve.n + curve.k; i++) {
    curve.knots[i] = (float)i;
  }
/*You can use the following code snippet to create the knots vector for a closed uniform spline.*/
curve.knots = malloc((curve.n + curve.k + 1) * sizeof(float));
  for (i = 0; i <= curve.n + curve.k; i++) {
    curve.knots[i] = (float)(i - curve.k);
  }
/*You can then use the evalBSplineCurve function to evaluate the B-spline curve
at a given parameter value and get the corresponding point on the curve.*/
//function pour afficher B-spline_3
for(int t=0; t<knots[N+K];t+=0.001){
  p=deboor(n,k,t);
  glVertex2f(p.x, p.y);
  glEnd;
}
