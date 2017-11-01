import build.trajectory_template as trajectory_template
import matplotlib.pyplot as plt
import numpy as np

sample_time = 0.001									# in seconds

traj_generator = trajectory_template.StepHipTraj()  # new object

traj_generator.reset()
traj_generator.set_max_hip_flexion(50)				# degrees
traj_generator.set_step_time(int(7/sample_time))	# in ms


time_array = np.arange(0, traj_generator.get_step_time() 
	* sample_time, sample_time) 					# in seconds

traj_values = []

for i,value in enumerate(time_array): # FIXME: what does i do? can get rid of??
	done, value = traj_generator.Increment() # generate traj in next time step
	traj_values.append(value)

traj_values = np.array(traj_values)

fig, ax = plt.subplots()

plt.plot(time_array, traj_values, label='raw')

plt.show()
