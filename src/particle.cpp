#include "particle.h"

Particles::Particles(unsigned int N)
{
    this->N = N;
    pos = new float3_t[N];
    h = new float_t[N];
    rho = new float_t[N];
    T = new float_t[N];
    T_t = new float_t[N];
    cp = new float_t[N];
    k = new float_t[N];
    mass = new float_t[N];
}

Particles::~Particles()
{
    delete[] pos;
    delete[] h;
    delete[] rho;
    delete[] T;
    delete[] T_t;
    delete[] cp;
    delete[] k;
    delete[] mass;
}

void Particles::set_properties(std::vector<float3_t> pos_vec, std::vector<float_t> T_vec, std::vector<float_t> cp_vec, std::vector<float_t> k_vec, std::vector<float_t> rho_vec, std::vector<float_t> h_vec, std::vector<float_t> mass_vec)
{
    for (size_t i = 0; i < N; i++)
    {
        pos[i] = pos_vec[i];
        cp[i] = cp_vec[i];
        k[i] = k_vec[i];
        rho[i] = rho_vec[i];
        T[i] = T_vec[i];
        T_t[i] = 0.;
        h[i] = h_vec[i];
        mass[i] = mass_vec[i];
    }
}


