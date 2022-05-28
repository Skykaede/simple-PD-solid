#pragma once
#ifndef S_MEM
#define S_MEM

#include "solid_basic.h"
#include "solid_symbols.h"

int solidmemset()
{
    coord = (double *)calloc(totdot * 3, sizeof(double));
    disp = (double *)calloc(totdot * 3, sizeof(double));
    vel = (double *)calloc(totdot * 3, sizeof(double));
    force = (double *)calloc(totdot * 3, sizeof(double));
    vol = (double *)calloc(totdot, sizeof(double));

    numfam = (int *)calloc(totdot, sizeof(int));
    pointfam = (int *)calloc(totdot, sizeof(int));
    idistfam = (double *)calloc(totdot * MAXFAM, sizeof(double));
    nodefam = (int *)calloc(totdot * MAXFAM, sizeof(int));
    return 0;
}
#endif
