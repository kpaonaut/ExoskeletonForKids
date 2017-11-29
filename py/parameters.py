# these are relatively fixed paramenters. Other parameters change in trajectory_generator.py
# The value commented are default values (tuned values)
_max_hip_flexion_ = lambda : 36 # 36
_max_hip_flexion_time_portion_ = lambda : 0.8 # 0.8, _max_hip_flexion_time_ * halfTotalTime = max_hip_flexion_time_
_hip_swing_start_ = lambda : -12 # -12
_step_range_ = lambda : 0.42 # 0.42
_leg_length_ = lambda : 0.95 # 0.95
_max_knee_flexion_ = lambda : 52 # 50
_second_knee_flexion_ = lambda : 16 # 16
_min_knee_flexion_ = lambda : 5 # 5
_walking_angle_ = lambda : 5 # 5