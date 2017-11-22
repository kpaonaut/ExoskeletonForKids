#ifndef _KNEE_H_
#define _KNEE_H_

#include <cstdio>
#include <cmath>
#include "spline.h"
#include <vector>


class StepKneeTraj {
  public:
    StepKneeTraj() {
    }
    void reset();
    int Increment(float* traj_value);
    void set_max_hip_flexion_time(float value);
    void set_walking_angle(float value); // offest for the entire trajectory
    void set_step_time(float value);
    void set_max_knee_flexion(float value);
    void set_second_knee_flexion(float value);
    void set_min_knee_flexion(float value);

    void init();
    void splineInterpolate();

    inline int get_step_time(){
        return step_time_;
    }

  private:
    float walking_angle_, max_knee_flexion, second_knee_flexion, min_knee_flexion;
    float max_hip_flexion_time_, step_time_, t_, starting_time_;
    int numPiece, n; // which piece of spline the current point belongs to, starting from 0
    // n: the number of critical pts, for hip it's 4
    tk::spline s; // spline obj
    std::vector<double> X, Y; // spline interpolation critical pts sequence
};

#endif /* _KNEE_H_ */