%module trajectory_template
%include typemaps.i
%apply float *OUTPUT { float *traj_value };

%{
#include <stdlib.h>
#include <iostream>
#include "../../trajectory_template.h"
%}

%include "../trajectory_template.h"

