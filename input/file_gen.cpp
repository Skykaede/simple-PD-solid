#include <iostream>

int main()
{
    FILE *inpf = fopen("ctrl.txt", "r");

    double Len, Wid, Hei, del, rho, hlen, timed;
    char buff[255];

    fscanf(inpf, "%lf %lf %lf %lf;",
           &Len, &Wid, &Hei, &del, &hlen);
    // printf("%lf %lf %lf %lf;", Len, Wid, Hei, del);
    fgets(buff, 255, inpf);
    fscanf(inpf, "%lf;", &rho);
    fgets(buff, 255, inpf);
    fscanf(inpf, "%lf;", &hlen);
    fgets(buff, 255, inpf);
    fscanf(inpf, "%lf;", &timed);
    // printf("%lf", rho);

    FILE *meshf = fopen("mesh.txt", "w");
    int dsum = 0;
    for (double ix = -Len / 2; ix < Len / 2; ix += del)
    {
        for (double iy = -Wid / 2; iy < Wid / 2; iy += del)
        {
            for (double iz = -Hei / 2; iz < Hei / 2; iz += del)
            {
                dsum++;
                fprintf(meshf, "%.8e,%.8e,%.8e,%.8e\n",
                        ix, iy, iz, del * del);
            }
        }
    }

    FILE *inputf = fopen("input.txt", "w");
    fprintf(inputf, "%d\n%.8e,%.8e,%.8e,%.8e\n%.8e\n%.8e\n%.8e", dsum, Len, Wid, Hei, del, rho, hlen, timed);

    return 0;
}