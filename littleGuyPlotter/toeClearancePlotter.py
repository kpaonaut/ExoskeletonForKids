# -*- coding: utf-8 -*-
import numpy as np
import pylab as pl
import matplotlib.collections  as mc
import matplotlib.pyplot as plt
import numpy as np

def main():
    # Points = np.array([[ 0.0    , 0.0   ],
    #                     [-0.172 , 0.149],
    #                     [ 0.154 , 0.526],
    #                     [ 0.434 , 0.851],
    #                     [ 0.577 , 1.661],
    #                     [ 0.675 , 0.496],
    #                     [ 0.622 , 0.   ],
    #                     [ 0.849 ,-0.024]])
    import PoseEstimator as pose
    from os import sys, path
    sys.path.append(path.abspath(path.join(path.dirname(__file__), '../py'))) # deal with import path issue
    import trajectory_generator as traj
    estimator = pose.PoseEstimator()
    generator = traj.TrajectoryGenerator() # np.array([walking angle, hip1, knee1, hip2, knee2])

    toe_clearance_values = []
    for i in range(0, 6000):
        angles = generator.generateTrajectory() # generate trajectory
        Points = estimator.CalculatePose(angles) # angles is obtained from increment()!
        toe_clearance = Points[0][1]
        toe_clearance_values.append(toe_clearance)

    fig, ax = plt.subplots()
    sample_time = 0.001
    time_array = np.arange(4, 6, sample_time) # in seconds
    plt.plot(time_array, toe_clearance_values[4000:6000],  'r', label='raw')
    plt.show()

if __name__ == "__main__":
    main()
