#ifndef TRAJECTORY_TEMPLATE_H_
#define TRAJECTORY_TEMPLATE_H_

#include "stdio.h"
#include <math.h>


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
	bool Increment(float* traj_value );

	/** Sets the max hip flexion angle
	 * @param value, the max hip flexion angle
	 *
	 */
	void set_max_hip_flexion(float value);

	/** Sets the max hip flexion angle
	 * @param value, the max hip flexion angle
	 */
	void set_walking_angle(float value);

	/** Sets the swing start angle
	 * @param value, the swing start angle
	 */
	void set_swing_start(float value);

	/** Sets the step time
	 * @param value, the step time value in time unit
	 */
	void set_step_time(int value);

	/* You might have other setter
	 * functions.
	 */

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

	/**
	 * Walking angle
	 */
	float walking_angle_;

	/**
	 * Step time in time units, total time e.g. 7000 ms
	 */
	int step_time_;

	/**
	 * Current time unit
	 */
	int t_;
};

#endif /* TRAJECTORY_TEMPLATE_H_ */
