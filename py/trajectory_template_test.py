import build.trajectory_template as trajectory_template
import matplotlib.pyplot as plt
import numpy as np

sample_time = 0.001									# in seconds

traj_generator = trajectory_template.StepHipTraj()  # new object

traj_generator.reset()
traj_generator.set_max_hip_flexion(36.202)			# degrees
traj_generator.set_max_hip_flexion_time(4200)
traj_generator.set_step_time(int(5/sample_time))	# in ms, integer
traj_generator.set_walking_angle(0)                 # offset, can vary
traj_generator.set_swing_start(-6.934)
traj_generator.set_step_range(0.78) # step length in meter. example: 0.78m legLen 1.1m -> theta 41.8

traj_generator.init(); # set coordinates for interpolation

time_array = np.arange(0, traj_generator.get_step_time() 
	* sample_time * 2, sample_time) 					# in seconds

traj_values = []

for i,value in enumerate(time_array): # FIXME: what does i do? can get rid of it?
	done, value = traj_generator.Increment() # generate traj in next time step
	traj_values.append(value)

traj_values = np.array(traj_values)

fig, ax = plt.subplots()

plt.plot(time_array, traj_values, label='raw')

plt.show()
