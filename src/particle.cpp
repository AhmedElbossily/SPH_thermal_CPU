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

void Particles::set_properties(std::vector<float3_t> pos_vec, std::vector<float_t> T_vec,
                               std::vector<float_t> cp_vec, std::vector<float_t> k_vec,
                               std::vector<float_t> rho_vec, std::vector<float_t> h_vec,
                               std::vector<float_t> mass_vec)
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
