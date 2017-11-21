# -*- coding: utf-8 -*-
__author__ = 'Raghid Mardini, Rui Wang'

import numpy as np
import pylab as pl
import matplotlib.collections  as mc
import matplotlib.pyplot as plt
import numpy as np

class ExoPlotter:
    def __init__(self,axis):
        # self.fig, self.ax = pl.subplots()
        self.ax = axis
        self.ax.spines['top'].set_visible(False)
        self.ax.spines['right'].set_visible(False)
        self.ax.spines['bottom'].set_visible(False)
        self.ax.spines['left'].set_visible(False)
        # self.ax.yaxis.set_ticks_position('left')
        # self.ax.xaxis.set_ticks_position('bottom')
        plt.setp( self.ax.get_xticklabels(), visible=False)
        plt.setp( self.ax.get_yticklabels(), visible=False)


    def Update(self,array,color, fig):
        array = np.asarray(array)
        if np.shape(array) != (8,2):
            raise Exception("invalid argument to ExoPlotter.Update()")
        lines = [[ array[0,:],array[1,:] ] , 
                [ array[1,:],array[2,:] ], 
                [ array[2,:],array[3,:] ] , 
                [ array[3,:],array[4,:] ] , 
                [ array[3,:],array[5,:] ] , 
                [ array[5,:],array[6,:] ], 
                [ array[6,:],array[7,:] ]]

        self.ax.clear()
        self.__PlotLines(lines,color, fig)
        
    def __PlotLines(self,lines,color, fig):
        lc = mc.LineCollection(lines[0:3],color=color[0], linewidths=2)
        self.ax.add_collection(lc)
        lc = mc.LineCollection(lines[3:4], linewidths=2)
        self.ax.add_collection(lc)
        lc = mc.LineCollection(lines[4:7],color=color[1],linewidths=2)
        self.ax.add_collection(lc)
        # lc = mc.LineCollection(lines[3], linewidths=2)
        # self.ax.add_collection(lc)
        # lc = mc.LineCollection(lines[4], linewidths=2)
        # self.ax.add_collection(lc)
        # self.ax.autoscale()
        self.ax.set_aspect('equal')
        self.ax.margins(0.1)
        # plt.show()
        # plt.draw()
        fig.canvas.draw() # FIXME this line is making the plotting VERY slow!

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
    sys.path.append(path.abspath(path.join(path.dirname(__file__), '../py')))
    import trajectory_generator as traj
    estimator = pose.PoseEstimator()
    generator = traj.TrajectoryGenerator() # np.array([walking angle, hip1, knee1, hip2, knee2])

    fig = plt.figure()
    exo_plotter_axis = fig.add_axes([0.75,0.1,0.2,0.3])
    plotter = ExoPlotter(exo_plotter_axis)
    colors = ("r", "b")
    plt.ion() # allow interactive plot!
    import time
    plt.show()

    for i in range(0, 1000):
        angles = generator.generateTrajectory() # generate trajectory
        Points = estimator.CalculatePose(angles) # angles is obtained from increment()!

        if i%10 == 0:
            print angles

        plotter.Update(Points, colors, fig) # too slow???
        # time.sleep(0.001)

if __name__ == "__main__":
    main()
