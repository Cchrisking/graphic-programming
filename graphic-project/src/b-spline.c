#include <stdio.h>
#include <stdlib.h>
#define MAX_CONTROL_POINTS 100
// Structure to represent a control point
typedef struct {
    double x;
    double y;
} ControlPoint;
// Array of control points
ControlPoint controlPoints[MAX_CONTROL_POINTS];
// Degree of the B-spline curve
int degree=4;
// Knot vector for the B-spline curve
double knots[106];//MAX_CONTROL_POINTS+degree+1
// Evaluate the B-spline curve at the specified parameter value
void deBoor(double t, double *x, double *y){
    int i, j;
    double tmp[MAX_CONTROL_POINTS];

    // Initialize the temporary array
    for (i = 0; i < degree + 1; i++) {
        tmp[i] = controlPoints[i].x;
    }
    // Compute the point on the curve
    for (j = 1; j <= degree; j++) {
        for (i = 0; i <= degree - j; i++) {
            double alpha = (t - knots[i + degree + 1 - j]) / (knots[i + degree + 1] - knots[i + degree + 1 - j]);
            tmp[i] = (1.0 - alpha) * tmp[i] + alpha * tmp[i + 1];
        }
    }
    // Store the result in x
    *x = tmp[0];

    // Repeat the process for the y coordinate
    for (i = 0; i < degree + 1; i++) {
        tmp[i] = controlPoints[i].y;
    }
    for (j = 1; j <= degree; j++) {
        for (i = 0; i <= degree - j; i++) {
            double alpha = (t - knots[i + degree + 1 - j]) / (knots[i + degree + 1] - knots[i + degree + 1 - j]);
            tmp[i] = (1.0 - alpha) * tmp[i] + alpha * tmp[i + 1];
        }
    }
    *y = tmp[0];
  }
int main(int argc, char *argv[]){
    int i;
    double t;
    double x, y;
    // Set the degree and control points
    degree = 3;
    for (i = 0; i < degree + 1; i++) {
        controlPoints[i].x = i;
        controlPoints[i].y = i;
    }
    // Set the knot vector
    for (i = 0; i < degree + 1; i++) {
        knots[i] = 0.0;
    }
    for (i = 0; i < degree + 1; i++) {
        knots[i + degree + 1] = (double)(degree + 1);
    }
    // Evaluate the curve
    ControlPoint p = evaluate(n, degree, points, knots, t);
    // Print the result
    printf("(%f, %f)\n", p.x, p.y);
    return 0;
}
