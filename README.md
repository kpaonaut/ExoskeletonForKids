## Exoskeleton Control
### Introduction
This repository contains all codes for exoskeleton control for children with *cerebral palsy* (CP). We have an exoskeleton designed with two actuators, for the hip and the knee joint, respectively. The task is to control both two joints and let them follow desirable trajectories and/or generate desirable torque.

### Code Architecture
We use C++ to carry out the calculation(for **speed**) while python to do the plotting(for **convenience**). An interface between two languages is established using [swig](www.swig.org).

To build the project, first go to ```/py``` then use command ```make```. This will generate a folder ```/build``` where warped C++ files for python will be created.

In folder ~~~/py~~~ run
```
python trajectory_template_test.py
```
to see a plot of two trajectories, of the hip angle and knee angle, respectively. The x-axis is time while y-axis is the angle of two joints.

For better illustration, apart from the trajectory, we also included a file that plots a little guy who walks according to the trajectory we generated for his both two joints.

Go to /littleGuyPlotter run
```
python ExoPlotter.py
```
This will generate a dynamic graph where a little guy is walking according to the parameters we assigned him.