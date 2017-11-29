"""
This is a plotter that generates the trajectory for both knee and hip angle
with data stored in parameters.py. Most of the parameters are tunable.
"""
import build.hip as hip
import build.knee as knee
import matplotlib.pyplot as plt
import numpy as np
import parameters as par

sample_time = 0.001 # in seconds
halfTotalTime = 2

### left Hip
hip_traj_generator = hip.StepHipTraj()  # new object

hip_traj_generator.reset()
hip_traj_generator.set_max_hip_flexion( par._max_hip_flexion_() ) # degrees, default 36
hip_traj_generator.set_max_hip_flexion_time( par._max_hip_flexion_time_portion_() * halfTotalTime / sample_time)       # in ms
hip_traj_generator.set_step_time( halfTotalTime / sample_time ) # in ms, integer. 5000 here.
hip_traj_generator.set_walking_angle( par._walking_angle_() ) # offset, can vary
hip_traj_generator.set_swing_start( par._hip_swing_start_() ) # default -6.934
hip_traj_generator.set_step_range( par._step_range_() ) # step length in meter. example: 0.78m legLen 1.1m -> theta 41.8
hip_traj_generator.set_leg_length( par._leg_length_() )

### left Knee
knee_traj_generator = knee.StepKneeTraj()  # new object

knee_traj_generator.reset()
knee_traj_generator.set_max_hip_flexion_time( par._max_hip_flexion_time_portion_() * halfTotalTime / sample_time )       # in ms
knee_traj_generator.set_step_time( halfTotalTime / sample_time ) # in ms, integer. 5000 here.
knee_traj_generator.set_max_knee_flexion( par._max_knee_flexion_() ) # in degrees
knee_traj_generator.set_second_knee_flexion( par._second_knee_flexion_() )
knee_traj_generator.set_min_knee_flexion( par._min_knee_flexion_() )
knee_traj_generator.set_walking_angle( par._walking_angle_() ) 

hip_traj_generator.init() # set coordinates for interpolation
knee_traj_generator.init()

time_array = np.arange(0, hip_traj_generator.get_step_time() 
	* sample_time * 4, sample_time) 					# in seconds

hip_traj_values = []
knee_traj_values = []

for i,value in enumerate(time_array): # FIXME: what does i do? can get rid of it?
    done, hip_value = hip_traj_generator.Increment()
    done, knee_value = knee_traj_generator.Increment() # generate traj in next time step
    hip_traj_values.append(hip_value)
    knee_traj_values.append(knee_value)

knee_traj_values = np.array(knee_traj_values)
hip_traj_values = np.array(hip_traj_values)

fig, ax = plt.subplots()

plt.plot(time_array, hip_traj_values,  'r', label='raw')
plt.plot(time_array, knee_traj_values, 'b', label='raw')

plt.show()
