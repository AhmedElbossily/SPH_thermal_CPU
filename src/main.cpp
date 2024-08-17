#include <iostream>
#include <vector>
#include <memory>
#include "particle.h"
#include "type.h"
#include <vtk_writer.h>
#include <interaction.h>

void update(Particles *particles, float_t dt)
{
    for (size_t i = 0; i < particles->N; i++)
    {
        particles->T[i] += particles->T_t[i] * dt;
    }
}

std::unique_ptr<Particles> initialize_particles(float_t lx, float_t ly, float_t lz, float_t dx, float_t dy, float_t dz, float_t hf)
{
    float_t nx = lx / dx;
    float_t ny = ly / dy;
    float_t nz = lz / dz;
    int N = static_cast<int>(nx * ny * (lz / dx));

    std::vector<float3_t> pos_vec;
    std::vector<float_t> T_vec;
    std::vector<float_t> cp_vec;
    std::vector<float_t> k_vec;
    std::vector<float_t> rho_vec;
    std::vector<float_t> h_vec;
    std::vector<float_t> mass_vec;

    pos_vec.reserve(N);
    T_vec.reserve(N);
    cp_vec.reserve(N);
    k_vec.reserve(N);
    rho_vec.reserve(N);
    h_vec.reserve(N);
    mass_vec.reserve(N);

    for (size_t i = 0; i < nx; i++)
    {
        for (size_t j = 0; j < ny; j++)
        {
            for (size_t k = 0; k < nz; k++)
            {
                pos_vec.push_back(make_float3_t(i * dx, j * dx, k * dx));
                cp_vec.push_back(850.);
                k_vec.push_back(157);
                rho_vec.push_back(2830.);
                mass_vec.push_back(2830. * dx * dx * dx);
                h_vec.push_back(hf * dx);
                T_vec.push_back(i == 0 ? 100. : 20.);
            }
        }
    }

    auto particles = std::make_unique<Particles>(N);
    particles->set_properties(pos_vec, T_vec, cp_vec, k_vec, rho_vec, h_vec, mass_vec);

    return particles;
}

void run_simulation(Particles *particles, float_t total_time, float_t dt)
{
    float_t percent_increment = 0.01;
    float_t next_percent = percent_increment;
    unsigned int step=0;

    for (float_t t = 0; t < total_time; t += dt)
    {
        interactions_heat(particles);
        update(particles, dt);

        float_t current_percent = t / total_time;

        if (current_percent >= next_percent)
        {
            std::cout << "Completion: " << int(current_percent * 100) << "%" << std::endl;
            next_percent += percent_increment;
            vtk_writer_write(particles, step);
        }
        step++;
    }
}

int main(int argc, char const *argv[])
{
    float_t lx = 1.0;
    float_t ly = 0.5;
    float_t lz = 0.5;
    float_t dx = 0.05;
    float_t dy = 0.05;
    float_t dz = 0.05;
    float_t hf = 1.2;

    auto particles = initialize_particles(lx, ly, lz, dx, dy, dz, hf);

    float_t total_time = 60;
    float_t dt = 0.1;

    run_simulation(particles.get(), total_time, dt);

    return 0;
}