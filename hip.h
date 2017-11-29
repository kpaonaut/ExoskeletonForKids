#ifndef TRAJECTORY_TEMPLATE_H_
#define TRAJECTORY_TEMPLATE_H_

#include <cstdio>
#include <cmath>
#include "spline.h"
#include <vector>


class StepHipTraj {
  public:
	StepHipTraj() {
	}
	void reset();
	int Increment(float* traj_value);
	void set_max_hip_flexion(float value);
    void set_max_hip_flexion_time(float value);
	void set_walking_angle(float value); // offest for the entire trajectory
	void set_swing_start(float value);
	void set_step_time(float value);
    void set_step_range(float value); // step length, in meter
    void set_leg_length(float);
    void init();
    void splineInterpolate();

	inline int get_step_time(){
		return step_time_;
    }

    inline float get_time(){
        return t_ * 0.001;
    }

    inline float get_initial_pos(){
        return s(0);
    }

  private:
	float swing_start_;
	float max_hip_flexion_;
    float max_hip_flexion_time_;
	float walking_angle_;
    float step_range_; // in meter
	float step_time_; // step time range, half the time of a cycle
    float t_;
	int numPiece, n; // which piece of spline the current point belongs to, starting from 0
    // n: the number of critical pts, for hip it's 4
    float leglen;
    float x[4];
    float y[4]; // spline points coordinates
    //float a[4], b[4], c[4], d[4];// spline function parameters y=d(x-xi)^3+c(x-xi)^2+b(x-xi)+a
    tk::spline s; // spline obj
    std::vector<double> X, Y; // spline interpolation critical pts sequence
};

#endif /* TRAJECTORY_TEMPLATE_H_ */
