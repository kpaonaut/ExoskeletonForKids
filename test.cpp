#include <cstdio>
#include <cstdlib>
#include <vector>
#include "spline.h"

int main(int argc, char** argv)
{

    std::vector<double> X(4), Y(4);
    X[0]=0;
    X[1]=4200;
    X[2]=5000;
    X[3]=10000;
    
    Y[0]=-6.9;
    Y[1]=36;
    Y[2]=42;
    Y[3]=-6.9;

    tk::spline s;
    s.set_boundary(tk::spline::first_deriv, 0.0, tk::spline::first_deriv, 0.0, false);
    s.set_points(X,Y);    // currently it is required that X is already sorted

    double x=10000;

    printf("spline at %f is %f\n", x, s(x));

    return EXIT_SUCCESS;
}
