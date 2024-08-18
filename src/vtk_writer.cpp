// SPH_thermal_CPU - Copyright Ahmed Elbossily

// This program is free software: you can redistribute it and/or modify it
// under the terms of the GNU General Public License as published by the Free Software Foundation,
// either version 3 of the License, or (at your option) any later version.

// SPH_thermal_CPU is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License
// for more details.

// You should have received a copy of the GNU General Public License along with this program.
// If not, see <http://www.gnu.org/licenses/>.

#include "vtk_writer.h"
void vtk_writer_write(Particles *particles, unsigned int step)
{
    // number of particles in the simulation
    unsigned int N_particles = particles->N;

    char buf[256];
    // output file name
    sprintf(buf, "../results/output_%012d.vtk", step);
    FILE *fp = fopen(buf, "w+");

    // write vtk file header
    fprintf(fp, "# vtk DataFile Version 2.0\n");
    fprintf(fp, "mfree iwf\n");
    fprintf(fp, "ASCII\n");
    fprintf(fp, "\n");

    fprintf(fp, "DATASET UNSTRUCTURED_GRID\n");
    fprintf(fp, "POINTS %d float\n", N_particles);
    for (unsigned int i = 0; i < N_particles; i++)
    {
        fprintf(fp, "%f %f %f\n", particles->pos[i].x,
                particles->pos[i].y, particles->pos[i].z);
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

    // Current particle temperature
    fprintf(fp, "SCALARS Temperature float 1\n");
    fprintf(fp, "LOOKUP_TABLE default\n");
    for (unsigned int i = 0; i < N_particles; i++)
    {
        fprintf(fp, "%f\n", particles->T[i]);
    }
    fprintf(fp, "\n");

    fclose(fp);
}
