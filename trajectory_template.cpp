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
    if (t_ < x[1]){
        *traj_value = A4 * t_ * (t_ * (t_ * (t_ + A3/A4) + A2/A4) + A1/A4) + A0;
    } else
    if (t_ < x[2]){
        float x_ = t_ - x[1];
        *traj_value = B3 * x_ * (x_ * (x_ + B2/B3) + B1/B3) + B0;
    } else{
        float x_ = t_ - x[2];
        *traj_value = C3 * x_ * (x_ * (x_ + C2/C3) + C1/C3) + C0;
    }

    *traj_value += walking_angle_;

	if (t_ >= 2*step_time_) {
		return true;
	}else{
		t_ ++; // Incrementing current time by one time unit
		return false;
	}
}

#define PI 3.14159265

void StepHipTraj::init() // the generation of spline
{
    x[0] = 0;
    x[1] = max_hip_flexion_time_;
    x[2] = step_time_;
    x[3] = 2*step_time_;
    y[0] = swing_start_;
    y[1] = max_hip_flexion_;
    y[2] = 2 * asin(step_range_ / 2.0 / leglen) * 180 / PI;
    y[3] = swing_start_;

    splineInterpolate();
}

void StepHipTraj::splineInterpolate()
{
    // X = std::vector<double>(9);
    // Y = std::vector<double>(9);
    // X[0] = double(x[0]); X[3] = double(x[1]); X[6] = double(x[2]); X[8] = double(x[3]);
    // X[1] = 0.333*x[0] + 0.667*x[1]; X[5] = 0.333*x[1] + 0.667*x[2]; X[7] = 0.667*x[2] + 0.333*x[3];
    // Y[0] = double(y[0]); Y[3] = double(y[1]); Y[6] = double(y[2]); Y[8] = double(y[3]);
    // Y[1] = 0.5*y[0] + 0.5*y[1]; Y[5] = 0.1*y[1] + 0.9*y[2]; Y[7] = 0.5*y[2] + 0.5*y[3];
    // // Next, add points next to x[1] to make its first derivative 0
    // X[2] = double(x[1]-1); Y[2] = y[1]; X[4] = double(x[1]+1); Y[4] = y[1];

    // s.set_boundary(tk::spline::first_deriv, 0.0, tk::spline::first_deriv, 0.0, false);
    // s.set_points(X, Y);
    A0 = y[0]; A1 = 0;
    B0 = y[1]; B1 = 0;
    C0 = y[2]; C1 = 0;

    float k1, k2; // set for temporary use, to solve the curve function!
    k1 = x[3] - x[2];
    k2 = y[3] - y[2];
    C3 = -2.0*k2/k1/k1/k1;
    C2 = 3.0*k2/k1/k1;

    k1 = x[2] - x[1];
    k2 = y[2] - y[1];
    B3 = -2.0*k2/k1/k1/k1;
    B2 = 3.0*k2/k1/k1;

    k1 = 2*(y[1] - y[0])/x[1]/x[1];
    k2 = 2*B2;
    A2 = (6*k1 + k2)/2.0;
    A3 = (-4*k1 - k2)/x[1];
    A4 = (3*k1 + k2)/2.0/x[1]/x[1];

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

void StepHipTraj::set_leg_length(float value) {
    leglen = value;
}