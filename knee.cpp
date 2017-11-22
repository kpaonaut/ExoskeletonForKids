#include "knee.h"
#include "spline.h"
#include <iostream> // debug
#include <cstdio>
#include <cstdlib>
#include <vector>
//using namespace std; //debug

void StepKneeTraj::reset() {
    t_ = 0;
    numPiece = 0;
    n = 5;
}

int StepKneeTraj::Increment(float* traj_value ) {

    if (t_ < (2*step_time_ + starting_time_)) // there is an x-offset as well!
        *traj_value = s(t_); // no walking angle offset for knee relative angle
    else
        *traj_value = s(t_ - 2*step_time_);

    if (t_ >= 2*step_time_) {
        t_ -= 2*step_time_;
        return 1;
    }else{
        t_++; // Incrementing current time by one time unit
        return 0;
    }
}

#define PI 3.14159265

void StepKneeTraj::init() // the generation of spline
{
    splineInterpolate();
}

void StepKneeTraj::splineInterpolate()
{
    X = std::vector<double>(7);
    Y = std::vector<double>(7);
    starting_time_ =  -0.24 * step_time_; // the starting time, x offset
    X[0] = starting_time_; Y[0] = min_knee_flexion;
    X[1] = 0; Y[1] = 0.3 * max_knee_flexion + 0.7 * min_knee_flexion;
    X[2] = X[0] + 0.5*max_hip_flexion_time_; Y[2] = max_knee_flexion;
    X[3] = step_time_ - 0.01*step_time_; X[4] = step_time_ + 0.01*step_time_; Y[3] = Y[0]; Y[4] = Y[0];
    X[5] = 1.24 * step_time_; Y[5] = second_knee_flexion;
    X[6] = X[0] + 2*step_time_; Y[6] = Y[0];
    s.set_boundary(tk::spline::first_deriv, 0.0, tk::spline::first_deriv, 0.0, false);
    s.set_points(X, Y);

}

void StepKneeTraj::set_max_hip_flexion_time(float value) {
    max_hip_flexion_time_ = value; // in ms
}

void StepKneeTraj::set_walking_angle(float value) {
    walking_angle_ = value;
}

void StepKneeTraj::set_step_time(float value) {
    step_time_ = value; // in ms
}

void StepKneeTraj::set_max_knee_flexion(float value) {
    max_knee_flexion = value;
}

void StepKneeTraj::set_second_knee_flexion(float value) {
    second_knee_flexion = value;
}

void StepKneeTraj::set_min_knee_flexion(float value) {
    min_knee_flexion = value;
}