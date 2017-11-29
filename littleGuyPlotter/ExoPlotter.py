# -*- coding: utf-8 -*-
__author__ = 'Rui Wang, Raghid Mardini'
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
        lines = [[ array[0,:],array[1,:] ], 
                [ array[1,:],array[2,:] ] , 
                [ array[2,:],array[3,:] ] , 
                [ array[3,:],array[4,:] ] , 
                [ array[3,:],array[5,:] ] , 
                [ array[5,:],array[6,:] ] , 
                [ array[6,:],array[7,:] ] ,
                [ np.array([-1.5, 0]), np.array([1.5, 0])]]

        self.ax.clear()
        self.__PlotLines(lines,color, fig)
        
    def __PlotLines(self,lines,color, fig):
        lc = mc.LineCollection(lines[0:3],color=color[0], linewidths=2)
        self.ax.add_collection(lc)
        lc = mc.LineCollection(lines[3:4], linewidths=2)
        self.ax.add_collection(lc)
        lc = mc.LineCollection(lines[4:7],color=color[1],linewidths=2)
        self.ax.add_collection(lc)
        lc = mc.LineCollection(lines[7:8],  color=color[2],linewidths=1) # ground
        self.ax.add_collection(lc)

        self.ax.set_aspect('equal')
        self.ax.margins(0.1)
        axes = plt.gca()
        axes.set_xlim([-1.5, 1.5]) # set axis scale fixed!
        axes.set_ylim([-0.1, 2])
        # plt.show()
        # plt.draw()
        fig.canvas.draw() # FIXME this line is making the plotting VERY slow!

import termios, fcntl, sys, os
global signal
def detectKeyboard():
    fd = sys.stdin.fileno()
    oldterm = termios.tcgetattr(fd)
    newattr = termios.tcgetattr(fd)
    newattr[3] = newattr[3] & ~termios.ICANON & ~termios.ECHO
    termios.tcsetattr(fd, termios.TCSANOW, newattr)
    oldflags = fcntl.fcntl(fd, fcntl.F_GETFL)
    fcntl.fcntl(fd, fcntl.F_SETFL, oldflags | os.O_NONBLOCK)
    global signal
    try:
        while 1:
            try:
                c = sys.stdin.read(1)
                if c == 'p':
                    signal = 1 - signal
                    if signal == 1:
                        print " The little guy is about to stop!"
                    else:
                        print " The little guy is about to resume!"
                return
            except IOError:
                        termios.tcsetattr(fd, termios.TCSAFLUSH, oldterm)
                        fcntl.fcntl(fd, fcntl.F_SETFL, oldflags)
                        return
    finally:
        termios.tcsetattr(fd, termios.TCSAFLUSH, oldterm)
        fcntl.fcntl(fd, fcntl.F_SETFL, oldflags)
        return

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

    fig = plt.figure()
    #exo_plotter_axis = fig.add_axes([0.75,0.1,0.2,0.3])
    exo_plotter_axis = fig.add_axes([0.1,0.1,0.8,0.8]) # specify plot location
    plotter = ExoPlotter(exo_plotter_axis)
    colors = ("r", "b", "g")
    plt.ion() # allow interactive plot!
    import time
    plt.show()

    # below is the code for listening to keyboard and pausing
    global signal
    signal = 0
    ims = []

    for i in range(0, 100000):
        angles = generator.generateTrajectory() # generate trajectory
        Points = estimator.CalculatePose(angles) # angles is obtained from increment()!

        if i%50 == 0:
            # print angles
            plotter.Update(Points, colors, fig) # too slow??? The step time is shrinked to allow smooth plot!
            # plt.savefig('anim/' + str(i) + '.png') - ENABLE this if you want to generate an animation
        
        detectKeyboard()
        if signal == 1:
            generator.stopTrigger()
        else:
            generator.resumeTrigger()

        time.sleep(0.001)

if __name__ == "__main__":
    main()
