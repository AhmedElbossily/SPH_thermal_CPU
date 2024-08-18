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

#include "kernel.h"
float_t lapl_pse(float3_t posi, float3_t posj, float_t hi)
{
    // corrdinates of particle i
    float_t xi = posi.x;
    float_t yi = posi.y;
    float_t zi = posi.z;

    // corrdinates of particle j
    float_t xj = posj.x;
    float_t yj = posj.y;
    float_t zj = posj.z;

    // distance between particle i and j
    float_t xij = xi - xj;
    float_t yij = yi - yj;
    float_t zij = zi - zj;
    float_t xx = sqrt_t(xij * xij + yij * yij + zij * zij);

    // Too close, or out of concern
    if (xx < 1.e-6 || xx > 2 * hi)
        return 0;

    // calculate weight
    float_t h2 = hi * hi;
    float_t h4 = h2 * h2;
    float_t h5 = hi * h4;
    float_t w2_pse = +4. / (h5 * M_PI * sqrt(M_PI)) * exp(-xx * xx / (h2));

    return w2_pse;
}
