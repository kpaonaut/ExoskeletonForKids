%module hip
%include typemaps.i
%apply float *OUTPUT { float *traj_value };

%{
#include <stdlib.h>
#include <iostream>
#include "../../hip.h"
%}

%include "../hip.h"