#include "trajectory_template.h"
#include "spline.h"
#include <iostream> // debug
#include <cstdio>
#include <cstdlib>
#include <vector>
//using namespace std; //debug

void StepHipTraj::reset() {
	t_ = 0;
    numPiece = 0;
    n = 4;
}

bool StepHipTraj::Increment(float* traj_value ) {
	//*traj_value = max_hip_flexion_ * sin(t_ * 0.001); // Sample calculation

    if (numPiece < n-1 && t_ > x[numPiece+1]) numPiece++;
    // t_ is current time
    //int dt_ = t_ - x[numPiece];
    //*traj_value = a[numPiece] + b[numPiece]*dt_+ c[numPiece]*pow(dt_, 2) + d[numPiece]*pow(dt_, 3);

    *traj_value = s(t_) + walking_angle_;

	if (t_ >= 2*step_time_) {
		return true;
	}else{
		t_++; // Incrementing current time by one time unit
		return false;
	}
}

#define PI 3.14159265

void StepHipTraj::init() // the generation of spline
{
    float leglen = 1.1; // leg length, for an approximation fo y[2]
    x[0] = 0;
    x[1] = max_hip_flexion_time_;
    x[2] = step_time_;
    x[3] = 2*step_time_;
    y[0] = swing_start_;
    y[1] = max_hip_flexion_;
    y[2] = 2 * asin(step_range_ / 2.0 / leglen) * 180 / PI;
    y[3] = swing_start_;
    double offset = walking_angle_; // offset for the entire trajectory

    splineInterpolate();
}

void StepHipTraj::splineInterpolate()
{
    // n--; // x_0, x_1, ..., x_n-1, n-1 pieces of splines in total
    // float l[n+1], u[n+1], z[n+1]; // a, b, c, d are class members, alr defined
    // int h[n+1];

    // l[0] = 1;
    // u[0] = 0;
    // z[0] = 0;
    // h[0] = x[1] - x[0];

    // for (int i = 1; i < n; i++) {
    //     h[i] = x[i+1] - x[i];
    //     l[i] = 2.0 * (x[i+1] - x[i-1]) - h[i-1] * u[i-1];
    //     u[i] = h[i] / l[i];
    //     a[i] = 3.0 / h[i] * (y[i+1] - y[i]) - 3.0 / h[i-1] * (y[i] - y[i-1]);
    //     z[i] = (a[i] - h[i-1] * z[i-1]) / l[i];
    // }

    // l[n] = 1.0;
    // z[n] = c[n] = 0;

    // for (int j = n-1; j >= 0; j--) {
    //     c[j] = z[j] - u[j] * c[j+1];
    //     b[j] = (y[j+1] - y[j]) / h[j] - (h[j] * (c[j+1] + 2 * c[j])) / 3.0;
    //     d[j] = (c[j+1] - c[j]) / (3.0 * h[j]);
    // }
    // for (int i = 0; i < n; i++) a[i] = y[i];
    // printf("%d %d %d %d\n", x[0], x[1], x[2], x[3]);//debug
    // printf("%f %f %f %f\n", y[0], y[1], y[2], y[3]);//debug
    // cout<<d[0]<<" "<<c[0]<<" "<<b[0]<<" "<<a[0]<<endl;
    // cout<<d[1]<<" "<<c[1]<<" "<<b[1]<<" "<<a[1]<<endl;
    // cout<<d[2]<<" "<<c[2]<<" "<<b[2]<<" "<<a[2]<<endl;
    // n++; // won't let this function mess n up. n still means number of critical pts


    //const std::vector<double> X(x, x + sizeof x / sizeof x[0]);
    //const std::vector<double> Y(y, y + sizeof y / sizeof y[0]);
    std::vector<double> X(n), Y(n);
    for (int i = 0; i < n; i++){
        X[i] = double(x[i]);
        Y[i] = double(y[i]);
        //std::cout<<x[i]<<" "<<y[i]<<std::endl;//debug
    }
    s.set_boundary(tk::spline::first_deriv, 0.0, tk::spline::first_deriv, 0.0, false);
    s.set_points(X, Y);
}

void StepHipTraj::set_max_hip_flexion(float value) {
    max_hip_flexion_ = value;
}

void StepHipTraj::set_max_hip_flexion_time(int value) {
    max_hip_flexion_time_ = value; // in ms
}

void StepHipTraj::set_walking_angle(float value) {
	walking_angle_ = value;
}

void StepHipTraj::set_swing_start(float value) {
	swing_start_ = value;
}

void StepHipTraj::set_step_time(int value) {
	step_time_ = value; // in ms
}

void StepHipTraj::set_step_range(float value) {
    step_range_ = value; // in meters, need to be converted
}