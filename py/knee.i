%module knee
%include typemaps.i
%apply float *OUTPUT { float *traj_value };

%{
#include <stdlib.h>
#include <iostream>
#include "../../knee.h"
%}

%include "../knee.h"