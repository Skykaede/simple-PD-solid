#pragma once
#ifndef S_KERNEL
#define S_KERNEL
#include "solid_basic.h"
#include "solid_symbols.h"
#include "solid_out.h"

int ini_boudary()
{
    for (int i = 0; i < totdot; i++)
    {
        vel[i3x(i)] = -1;
    }
    return 0;
}

int solid_boundary(int is, int totstep)
{
    double dt = 0.01;

    for (int i = 0; i < totdot; i++)
    {
        // force[i3x(i)] += -0.01;

        vel[i3x(i)] += force[i3x(i)] * dt;
        vel[i3y(i)] += force[i3y(i)] * dt;
        vel[i3z(i)] += force[i3z(i)] * dt;

        if (coord[i3x(i)] < -5.5)
        {
            vel[i3x(i)] = checkpn_d(vel[i3x(i)]) * vel[i3x(i)] * 0.1;
            coord[i3x(i)] = -5.5;
        }
        if (coord[i3x(i)] > 5.5)
        {
            vel[i3x(i)] = -checkpn_d(vel[i3x(i)]) * vel[i3x(i)] * 0.1;
            coord[i3x(i)] = 5.5;
        }
    }

    for (int i = 0; i < totdot; i++)
    {
        disp[i3x(i)] = vel[i3x(i)] * dt;
        disp[i3y(i)] = vel[i3y(i)] * dt;
        disp[i3z(i)] = vel[i3z(i)] * dt;
    }

    for (int i = 0; i < totdot; i++)
    {
        if (coord[i3x(i)] < -5.0 + 1e-6)
        {
            // disp[i3x(i)] = 0;
            // disp[i3y(i)] = 0;
            // disp[i3z(i)] = 0;
        }
        if (coord[i3x(i)] > 4.0 - 1e-6)
        {
            // disp[i3x(i)] = 0;
            // disp[i3y(i)] = 1.0 / double(1000);
            //  disp[i3y(i)] = 0;
            // disp[i3z(i)] = 0;
        }
    }

    for (int i = 0; i < totdot; i++)
    {
        coord[i3x(i)] += disp[i3x(i)];
        coord[i3y(i)] += disp[i3y(i)];
        coord[i3z(i)] += disp[i3z(i)];
    }

    return 0;
}
int get_ini_dis()
{
    for (int i = 0; i < totdot; i++)
    {
        numfam[i] = 0;
        pointfam[i] = 0;
    }

    double realh = fiedel * spadel;
    for (int i = 0; i < totdot; i++)
    {
        numfam[i] = 0;
        if (i == 0)
            pointfam[i] = 0;
        else
            pointfam[i] = pointfam[i - 1] + numfam[i - 1];

        double xi = coord[i3x(i)];
        double yi = coord[i3y(i)];
        double zi = coord[i3z(i)];

        for (int j = 0; j < totdot; j++)
        {
            if (i == j)
                continue;
            double xj = coord[i3x(j)];
            double yj = coord[i3y(j)];
            double zj = coord[i3z(j)];

            double idist = getdis3d(xi, yi, zi,
                                    xj, yj, zj);

            if (idist > realh)
                continue;

            // printf("%lf ", idist);
            nodefam[pointfam[i] + numfam[i]] = j;
            idistfam[pointfam[i] + numfam[i]] = idist;
            ++numfam[i];
        }
    }

    for (int i = 0; i < totdot; i++)
    {
        // printf("%d\n", numfam[i]);
    }
    // exit(0);
    return 0;
}
int cal_force()
{
    double k = 10;
    double realh = fiedel * spadel;
    for (int i = 0; i < totdot; i++)
    {
        double xi = coord[i3x(i)];
        double yi = coord[i3y(i)];
        double zi = coord[i3z(i)];

        force[i3x(i)] = 0;
        force[i3y(i)] = 0;
        force[i3z(i)] = 0;

        for (int j = 0; j < numfam[i]; j++)
        {
            int nj = nodefam[pointfam[i] + j];
            double idist = idistfam[pointfam[i] + j];

            double xj = coord[i3x(nj)];
            double yj = coord[i3y(nj)];
            double zj = coord[i3z(nj)];

            double ndist = getdis3d(xi, yi, zi,
                                    xj, yj, zj);

            double ratio = (ndist - idist) / ndist;
            // printf("%lf\n", idist);
            double delx = xj - xi;
            double dely = yj - yi;
            double delz = zj - zi;
            force[i3x(i)] += k * delx / ndist * ratio;
            force[i3y(i)] += k * dely / ndist * ratio;
            force[i3z(i)] += k * delz / ndist * ratio;
        }
    }
    // exit(0);
    return 0;
}

int solid_kernel()
{
    ini_boudary();
    get_ini_dis();
    int totstep = 2000;
    int interval = 10;
    for (int i = 0; i < totstep; i++)
    {

        printf("%d / %d\r", i, totstep);
        solid_boundary(i, totstep);
        if (i % interval == 0)
        {
            solid_out(i);
            // get_ini_dis();
        }
        cal_force();
    }

    return 0;
}

#endif