__author__ = 'Raghid Mardini'

import numpy as np #numpy
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


    def Update(self,array,color):
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
        self.__PlotLines(lines,color)
        
    def __PlotLines(self,lines,color):
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



def main():

    fig = plt.figure()
    exo_plotter_axis = fig.add_axes([0.75,0.1,0.2,0.3])
    plotter = ExoPlotter(exo_plotter_axis)

    Points = np.array([[ 0.0    , 0.0   ],
                        [-0.172 , 0.149],
                        [ 0.154 , 0.526],
                        [ 0.434 , 0.851],
                        [ 0.577 , 1.661],
                        [ 0.675 , 0.496],
                        [ 0.622 , 0.   ],
                        [ 0.849 ,-0.024]])

    colors = ("r","b")
    plotter.Update(Points,colors)
    plt.show()

if __name__ == "__main__":
    main()
