#include "trajectory_template.h"

void StepHipTraj::reset() {
	t_ = 0;
	/* You might have other variables
	 * to reset.
	 */
}

bool StepHipTraj::Increment(float* traj_value ) {
	/*
	 * All your calculations will go here.
	 */
    printf("%f", *traj_value); // DEBUG
	*traj_value = max_hip_flexion_ * sin(t_ * 0.001); // Sample calculation

	if (t_ >= step_time_) {
		return true;
	}else{
		t_++; // Incrementing current time by one time unit
		return false;
	}
}

void StepHipTraj::set_max_hip_flexion(float value) {
	max_hip_flexion_ = value;
}

void StepHipTraj::set_walking_angle(float value) {
	walking_angle_ = value;
}

void StepHipTraj::set_swing_start(float value) {
	swing_start_ = value;
}


void StepHipTraj::set_step_time(int value) {
	step_time_ = value;
	/* You might have other timing parameters to be
	 * set here.
	 */
}
