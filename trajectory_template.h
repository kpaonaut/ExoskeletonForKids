#ifndef TRAJECTORY_TEMPLATE_H_
#define TRAJECTORY_TEMPLATE_H_

#include "stdio.h"
#include <cmath>
#include "spline.h"


class StepHipTraj {
  public:
	StepHipTraj() {
	}

	/** Resets the trajectory to the start point
	 *
	 */
	void reset();

	/** Increments the trajectory by one time unit.
	 * @param traj_value the value of the trajectory at the current
	 *   time unit. Passed by reference
	 * @return flag, true if the trajectory is over
	 */
	bool Increment(float* traj_value);

	/** Sets the max hip flexion angle
	 * @param value, the max hip flexion angle
	 *
	 */
	void set_max_hip_flexion(float value);

	/** Sets the max hip flexion angle
	 * @param value, the max hip flexion angle
	 */

    void set_max_hip_flexion_time(int value);

	void set_walking_angle(float value); // offest for the entire trajectory

	/** Sets the swing start angle
	 * @param value, the swing start angle
	 */
	void set_swing_start(float value);

	/** Sets the step time
	 * @param value, the step time value in time unit, half the time of a cycle
	 */
	void set_step_time(int value);
    void set_step_range(float value); // step length, in meter

    void init();

    void splineInterpolate();

	inline int get_step_time(){
		return step_time_;
	}

  private:
	/**
	 * Swing start angle
	 */
	float swing_start_;

	/**
	 * Max hip flexion angle
	 */
	float max_hip_flexion_;
    int max_hip_flexion_time_;

	/**
	 * Walking angle
	 */
	float walking_angle_;
    float step_range_; // in meter

	/**
	 * Step time in time units, total time e.g. 7000 ms
	 */
	int step_time_;

	/**
	 * Current time unit
	 */
	int t_, numPiece, n; // which piece of spline the current point belongs to, starting from 0
    // n: the number of critical pts

    int x[4];
    float y[4]; // spline points coordinates
    float a[4], b[4], c[4], d[4];// spline function parameters y=d(x-xi)^3+c(x-xi)^2+b(x-xi)+a
    tk::spline s[3]; // spline obj
};

#endif /* TRAJECTORY_TEMPLATE_H_ */
