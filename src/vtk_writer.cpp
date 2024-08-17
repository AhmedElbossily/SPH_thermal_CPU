#include "vtk_writer.h"
void vtk_writer_write(Particles *particles, unsigned int step)
{
    unsigned int N_particles = particles->N;

    char buf[256];
    sprintf(buf, "../results/output_%012d.vtk", step);
    FILE *fp = fopen(buf, "w+");

    fprintf(fp, "# vtk DataFile Version 2.0\n");
    fprintf(fp, "mfree iwf\n");
    fprintf(fp, "ASCII\n");
    fprintf(fp, "\n");

    fprintf(fp, "DATASET UNSTRUCTURED_GRID\n"); // Particle positions
    fprintf(fp, "POINTS %d float\n", N_particles);
    for (unsigned int i = 0; i < N_particles; i++)
    {
        fprintf(fp, "%f %f %f\n", particles->pos[i].x, particles->pos[i].y, particles->pos[i].z);
    }
    fprintf(fp, "\n");

    fprintf(fp, "CELLS %d %d\n", N_particles, 2 * N_particles);
    for (unsigned int i = 0; i < N_particles; i++)
    {

        fprintf(fp, "%d %d\n", 1, i);
    }
    fprintf(fp, "\n");

    fprintf(fp, "CELL_TYPES %d\n", N_particles);
    for (unsigned int i = 0; i < N_particles; i++)
    {

        fprintf(fp, "%d\n", 1);
    }
    fprintf(fp, "\n");

    fprintf(fp, "POINT_DATA %d\n", N_particles);

    fprintf(fp, "SCALARS Temperature float 1\n"); // Current particle temperature
    fprintf(fp, "LOOKUP_TABLE default\n");
    for (unsigned int i = 0; i < N_particles; i++)
    {
        fprintf(fp, "%f\n", particles->T[i]);
    }
    fprintf(fp, "\n");

    fclose(fp);
}
