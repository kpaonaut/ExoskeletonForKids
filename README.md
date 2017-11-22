## Exoskeleton Control
#### By [Rui Wang](http://www.aray.pub), Dept. MechE, Tsinghua University 11/21/2017 @ UC Berkeley
### Introduction
This repository contains all codes for exoskeleton control for children with *cerebral palsy* (CP). We have an exoskeleton designed with two actuators, for the hip and the knee joint, respectively. The task is to control both two joints and let them follow desirable trajectories and/or generate desirable torque.

### See it Running!
We use C++ to carry out the calculation(for **speed**) while python to do the plotting(for **convenience**). An interface between two languages is established using [swig](www.swig.org).

The package comes with source codes already built. You can see it running without doing extra building. However if you do modify the code, you may have to rebuild the project. This requires that **[swig](www.swig.org), python, matplotlib, numpy, and pynput** be installed properly on your computer. Also, this works for a UNIX-based system(LINUX, Mac OS). For windows there will be problems as I used some UNIX-specific commands for python programs and shell scripts.

To see it running directly, go to ```/littleGuyPlotter``` and type in commandline(note that your computer should be using python 2.7)

	python ExoPlotter.py
	
Note that you can now press "p" on keyboard to stop the little guy and press "p" again to resume.

To build the project, first go to ```/py``` then use command ```make```. This will generate a folder ```/build``` where warped C++ files for python will be created.

In folder ```/py``` run

```
python trajectory_template_test.py
```
to see a plot of two trajectories, of the hip angle and knee angle, respectively. The x-axis is time while y-axis is the angle of two joints.

For better illustration, apart from the trajectory, we also included a file that plots a little guy who walks according to the trajectory we generated for his both two joints.

Go to /littleGuyPlotter, run

```
python ExoPlotter.py
```
This will generate a dynamic graph where a little guy is walking according to the parameters we assigned him.

If you have changed the C++ file, you will need to rebuild the project. Under ```/littleGuyPlotter```, use command

	source build.sh
to build the project and automatically run the ```ExoPlotter.py```.

### Architecture & Explanation
The major architecture for the folder and their functions explained (irrelevent files are omitted):

```
.
├── README.md                           # readme
├── hip.h, knee.h, hip.cpp, knee.cpp    # knee & hip trajctory
├── littleGuyPlotter
│   ├── ExoPlotter.py                   # plot the little walking man
│   ├── PoseEstimator.py                # calculate coordinates used by ExoPlotter.py
│   └── build.sh                        # for code
├── py
│   ├── Makefile                        # Makefile
│   ├── build                           # swig-warped c++ files for python
│   │   └──...
│   ├── hip/knee.i, setup_knee/hip.py   # swig file
│   ├── parameters.py                   # define key parameters
│   ├── trajectory_generator.py         # generate trajectory for curve-plotting
│   └── trajectory_template_test.py     # plot trajectory curve
└── spline.h                            # generate spline
```

```/littleGuyPlotter/trajectory_generator.py``` is manily used for generating the trajectory. It can be paused and resumed through outside signal. For walking precision, the knee trajectory slope is not at 0 when hip trajectory slope is 0. However, the trajectory slope for two knees and two hips, respectively, will reach 0 at the same time. My implementing method is to always let the knee stop first, after a little while the hip slope will reach 0, then let the hip also stop.

To show this in software, I enabled a keyboard pausing mechanism through the same interface. Run ```ExoPlotter.py```, then you can press "p" on the keyboard to make the little guy stop. Note that the little guy will not stop immediately, rather, it will choose to stop at a suitable time, as described above.

### Trajectory Generation
I used 3-rd order spline to generate the trajectory. In order to generate a desirable shape, I added redundant points on the graph to ensure a good performance. This method is very flexible and robust, though it might require a little tuning(but once tuned, you are good for any change in other parameters, plus I actually tuned it only once, so there is not really any major trade-off here).

For a previous version, I also implemented a _4-th order + 3-rd_ order version, with all 13 coefficients pre-solved manually. However, over-fitting is inevitable under certain circumstances. Also, the solution is only feasible for normal walking, and cannot be adjusted to any other trajectory, which is not really portable.

### Plotting
The plotting for the little guy is designed such that the little guy looks like to be walking on a treadmill. The result looks good. The idea is to

* make sure that the guy walks on a flat surface
* make sure that the guy do not do "flashmove"

The best way to do this is to set the origin with y direction at the lowest of all points(which is natural, since the guy is walking and he cannot penetrate the ground), and x direction right in the middle of the guy's hip(which is natural again, since the person's CoM would appear static relative to the ground).

### Discussion
There is one major deficiency with this exo model: that the ankle angle is always 90 degrees. This differs from actual human model, therefore, double-stance only happens for an instant, as opposed to the actual human walking. 

In fact, there is no workaround - we cannot ensure a period of double-stance unless we generate the trajectory by **math equation** instead of **spline**. Nevertheless, we can rely on the fact that the actual exo foot is not as long as 0.11 body height, and the patient's foot actually exceeds that length. Human feet are soft and flexible, and the patient is able to have an actual double stance with his forefeet(or shoes, to be precise). Also, from the animation we can see that the foot is not lifted far from the floor after the instant "double-stance", therefore this approximation should be feasible.

### Acknowledgements
Note that as the file is just circulated inside our group, these guys listed will not get rewarded. However, they are warmly wished happy Thanksgiving.

* **Raghid Mardini**, Software and Controls Engineer Lead @ [SuitX](http://www.suitx.com)
* **Michael McKinley**, Unknown Title @ [SuitX](http://www.suitx.com)
* **Emily Stednitz** @ 102B group control squad
* **Blake Hamid, Ennzhi Chew, Serhad Katzermanian** @ 102B group mechanical design squad
* **Kazerooni**, professor at UC Berkeley, but more of a CEO @ [SuitX](http://www.suitx.com)