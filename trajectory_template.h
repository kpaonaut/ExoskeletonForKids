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
	bool Increment(float* traj_value);
	void set_max_hip_flexion(float value);
    void set_max_hip_flexion_time(int value);
	void set_walking_angle(float value); // offest for the entire trajectory
	void set_swing_start(float value);
	void set_step_time(int value);
    void set_step_range(float value); // step length, in meter
    void set_leg_length(float);
    void init();
    void splineInterpolate();

	inline int get_step_time(){
		return step_time_;
	}

  private:
	float swing_start_;
	float max_hip_flexion_;
    int max_hip_flexion_time_;
	float walking_angle_;
    float step_range_; // in meter
	int step_time_; // step time range, half the time of a cycle
	int t_, numPiece, n; // which piece of spline the current point belongs to, starting from 0
    // n: the number of critical pts, for hip it's 4
    float leglen;
    float x[4], y[4]; // spline points coordinates
    float A0, A1, A2, A3, A4, B0, B1, B2, B3, C0, C1, C2, C3; // coefficients for spline
    //tk::spline s; // spline obj
    //std::vector<double> X, Y; // spline interpolation critical pts sequence
};

#endif /* TRAJECTORY_TEMPLATE_H_ */
