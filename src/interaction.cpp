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

#include "interaction.h"

void interactions_heat(Particles *particles)
{
    unsigned int N = particles->N;
    for (size_t i = 0; i < N; i++)
    {
        float3_t pi = particles->pos[i];   // position of particle i
        float_t Ti = particles->T[i];      // temperature of particle i
        float_t cpi = particles->cp[i];    //  specific heat capacity of particle i
        float_t ki = particles->k[i];      // thermal conductivity of particle i
        float_t rhoi = particles->rho[i];  // density of particle i
        float_t hi = particles->h[i];      // smoothing length of particle i
        float_t mass = particles->mass[i]; // mass of particle
        float_t T_ti = 0.;                 // time derivative of temperature for particle i

        // iterate over neighboring particles for particle i
        for (size_t j = 0; j < N; j++)
        {
            float3_t pj = particles->pos[j];  // position of particle j
            float_t Tj = particles->T[j];     // temperature of particle j
            float_t cpi = particles->cp[j];   // specific heat capacity of particle j
            float_t kj = particles->k[j];     // thermal conductivity of particle j
            float_t rhoj = particles->rho[j]; //

            float_t w2_pse = lapl_pse(pi, pj, hi); // Laplacian by PSE-method

            T_ti += ((4 * ki * kj) / (ki + kj)) * (mass / rhoj) * (Tj - Ti) * w2_pse;
        }

        float_t alpha = 1.0 / (rhoi * cpi); //   thermal diffusivity of particle i
        particles->T_t[i] = alpha * T_ti;   // time derivative of temperature for particle i
    }
}
