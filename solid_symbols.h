#pragma once
#ifndef S_SYMBOL
#define S_SYMBOL
#include "solid_basic.h"

double
    *coord,
    *disp,
    *vel,
    *force;

int totdot;
double rho;
double *vol;
double fiedel;
double timdel;
int itstep;
double spadel;
double kmod = 80e9;
int MAXFAM = 200;

int *numfam;
int *pointfam;
double *idistfam;
int *nodefam;

double LEN, WID, HEI;

#endif
