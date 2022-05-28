#pragma once
#ifndef _SOLID_BASIC
#define _SOLID_BASIC

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define i2(i, j, ndim) (((i) * (ndim)) + (j))
#define i2x(i) ((i)*2)
#define i2y(i) (((i)*2) + 1)

#define i3x(i) ((i)*3)
#define i3y(i) (((i)*3) + 1)
#define i3z(i) (((i)*3) + 2)

#define i3(i, j, k, mdim, ndim) ((i) * (mdim) * (ndim) + (j) * (ndim) + k)
#define square(k) ((k) * (k))
#define cube(k) ((k) * (k) * (k))

double getdis3d(double x1, double y1, double z1,
                double x2, double y2, double z2)
{
    double dis = 0;
    dis += square(x1 - x2) + square(y1 - y2) + square(z1 - z2);
    return sqrt(dis);
}

int checkpn_d(double x)
{
    if (x > 0)
        return 1;
    if (x < 0)
        return -1;
    return 0;
}

#endif