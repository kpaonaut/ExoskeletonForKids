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

    *traj_value = s[numPiece](t_) + walking_angle_;

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
    y[2] = 1.1 * asin(step_range_ / 2.0 / leglen) * 180 / PI;
    y[3] = swing_start_;
    double offset = walking_angle_; // offset for the entire trajectory

    splineInterpolate();
}

void StepHipTraj::splineInterpolate()
{
    //const std::vector<double> X(x, x + sizeof x / sizeof x[0]);
    //const std::vector<double> Y(y, y + sizeof y / sizeof y[0]);
    // std::vector<double> X(n), Y(n);
    // for (int i = 0; i < n; i++){
    //     X[i] = double(x[i]);
    //     Y[i] = double(y[i]);
    //     //std::cout<<x[i]<<" "<<y[i]<<std::endl;//debug
    // }
    // s.set_boundary(tk::spline::first_deriv, 0.0, tk::spline::first_deriv, 0.0, false);
    // s.set_points(X, Y);
    std::vector<double> X(2), Y(2);
    X[0] = double(x[0]); X[1] = double(x[1]);
    Y[0] = double(y[0]); Y[1] = double(y[1]);
    s[0].set_boundary(tk::spline::first_deriv, 0.0, tk::spline::first_deriv, 0.0, false);
    s[0].set_points(X, Y);

    X[0] = double(x[1]); X[1] = double(x[2]);
    Y[0] = double(y[1]); Y[1] = double(y[2]);
    s[1].set_boundary(tk::spline::first_deriv, 0.0, tk::spline::first_deriv, 0.0, false);
    s[1].set_points(X, Y);

    X[0] = double(x[2]); X[1] = double(x[3]);
    Y[0] = double(y[2]); Y[1] = double(y[3]);
    s[2].set_boundary(tk::spline::first_deriv, 0.0, tk::spline::first_deriv, 0.0, false);
    s[2].set_points(X, Y);
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