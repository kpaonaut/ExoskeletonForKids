#!/bin/bash
cd ../py
make
cd ../littleGuyPlotter
python ../py/trajectory_template_test.py
python ExoPlotter.py