## Exoskeleton Control
### Introduction
This repository contains all codes for exoskeleton control for children with *cerebral palsy* (CP). We have an exoskeleton designed with two actuators, for the hip and the knee joint, respectively. The task is to control both two joints and let them follow desirable trajectories and/or generate desirable torque.

### See it Running!
We use C++ to carry out the calculation(for **speed**) while python to do the plotting(for **convenience**). An interface between two languages is established using [swig](www.swig.org).

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