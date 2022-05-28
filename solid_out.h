#pragma once
#ifndef S_OUT
#define S_OUT
#include "solid_basic.h"
#include "solid_symbols.h"
#include <string.h>

int solid_out(int sort)
{
    FILE *outf;
    char outnam[255], str1[10];
    strcpy(outnam, "./output/coord");
    itoa(sort, str1, 10);
    strcat(outnam, str1);
    strcat(outnam, ".vtk");
    outf = fopen(outnam, "w");

    fprintf(outf, "# vtk DataFile Version 3.0\n"
                  "vtk output\n"
                  "ASCII\n"
                  "DATASET UNSTRUCTURED_GRID\n"
                  "POINTS %d float\n",
            totdot);

    for (int i = 0; i < totdot; i++)
    {
        fprintf(outf, "%lf %lf %lf\n",
                coord[i3x(i)], coord[i3y(i)], coord[i3z(i)]);
    }

    fprintf(outf, "\nPOINT_DATA %d\n"
                  "SCALARS volume float \n"
                  "LOOKUP_TABLE default\n",
            totdot);

    for (int i = 0; i < totdot; i++)
    {
        fprintf(outf, "%lf\n", vol[i]);
    }
    fclose(outf);
    return 0;
}
#endif
