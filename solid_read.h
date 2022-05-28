#pragma once
#ifndef S_READ
#define S_READ
#include "solid_basic.h"
#include "solid_symbols.h"
#include "solid_mem.h"

int solid_read()
{
    char buff[255];
    FILE *inpf;
    inpf = fopen("./input/input.txt", "r");
    fscanf(inpf, "%d", &totdot);
    fgets(buff, 255, inpf);

    fscanf(inpf, "%lf,%lf,%lf,%lf",
           &LEN, &WID, &HEI, &spadel);
    fgets(buff, 255, inpf);
    // printf("%lf\n", spadel);

    fscanf(inpf, "%lf", &rho);
    fgets(buff, 255, inpf);

    fscanf(inpf, "%lf", &fiedel);
    fgets(buff, 255, inpf);

    fscanf(inpf, "%lf", &timdel);
    fgets(buff, 255, inpf);
    fclose(inpf);

    solidmemset();

    FILE *mesf;
    mesf = fopen("./input/mesh.txt", "r");

    for (int i = 0; i < totdot; i++)
    {
        fscanf(mesf, "%lf,%lf,%lf,%lf",
               &coord[i3x(i)], &coord[i3y(i)], &coord[i3z(i)], &vol[i]);
        fgets(buff, 255, mesf);
        // printf("%d %d %lf\n", i, totdot, coord[i3x(i)]);
    }
    fclose(mesf);
    return 0;
}

#endif
