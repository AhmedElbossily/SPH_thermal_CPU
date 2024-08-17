#include "interaction.h"

void interactions_heat(Particles *particles)
{

    unsigned int N = particles->N;
    for (size_t i = 0; i < N; i++)
    {
        float3_t pi = particles->pos[i];
        float_t Ti = particles->T[i];
        float_t cpi = particles->cp[i];
        float_t ki = particles->k[i];
        float_t rhoi = particles->rho[i];
        float_t hi = particles->h[i];
        float_t mass = particles->mass[i];
        float_t alpha = 1.0 / (rhoi * cpi);

        float_t T_ti = 0.;

        // iterate over neighboring boxes
        for (size_t j = 0; j < N; j++)
        {
            float3_t pj = particles->pos[j];
            float_t Tj = particles->T[j];
            float_t cpi = particles->cp[j];
            float_t kj = particles->k[j];
            float_t rhoj = particles->rho[j];

            float_t w2_pse = lapl_pse(pi, pj, hi); // Laplacian by PSE-method

            T_ti += ((4 * ki * kj) / (ki + kj)) * (mass / rhoj) * (Tj - Ti) * w2_pse;
        }

        particles->T_t[i] = alpha * T_ti;
    }
}
