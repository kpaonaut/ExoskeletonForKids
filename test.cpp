#include <cstdio>
#include <cstdlib>
#include <vector>
#include "spline.h"
#include <iostream>
using namespace std;

void foo(int* x)
{
    *x = *x+1;
}

int main(int argc, char** argv)
{
    int x = 10;
    foo(&x);

    cout<<x<<endl;
    return 0;
}
