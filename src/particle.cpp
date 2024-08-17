#include "particle.h"

Particles::Particles(unsigned int N)
{
    this->N = N;
    pos = new float3_t[N];
    vel = new float3_t[N];
    vel_bc = new float3_t[N];
    h = new float_t[N];
    rho = new float_t[N];
    p = new float_t[N];
    S = new mat3x3_t[N];
    R = new mat3x3_t[N];
    fc = new float3_t[N];
    ft = new float3_t[N];
    n = new float3_t[N];
    fixed = new float_t[N];
    blanked = new float_t[N];
    eps_pl = new float_t[N];
    eps_pl_dot = new float_t[N];
    T = new float_t[N];
    pos_t = new float3_t[N];
    vel_t = new float3_t[N];
    rho_t = new float_t[N];
    S_t = new mat3x3_t[N];
    T_t = new float_t[N];
    S_der = new mat3x3_t[N];
    v_der = new mat3x3_t[N];
    num_nbh = new int[N];
    idx = new int[N];
    hash = new int[N];
    cp = new float_t[N];
    k = new float_t[N];
    mass = new float_t[N];
}

Particles::~Particles()
{
    delete[] pos;
    delete[] vel;
    delete[] vel_bc;
    delete[] h;
    delete[] rho;
    delete[] p;
    delete[] S;
    delete[] R;
    delete[] fc;
    delete[] ft;
    delete[] n;
    delete[] fixed;
    delete[] blanked;
    delete[] eps_pl;
    delete[] eps_pl_dot;
    delete[] T;
    delete[] pos_t;
    delete[] vel_t;
    delete[] rho_t;
    delete[] S_t;
    delete[] T_t;
    delete[] S_der;
    delete[] v_der;
    delete[] num_nbh;
    delete[] idx;
    delete[] hash;
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
        h[i] = h_vec[i];
        mass[i] = mass_vec[i];
    }
}


