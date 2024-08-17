#include <iostream>
#include <vector>
#include <memory>
#include "particle.h"
#include "type.h"
#include <vtk_writer.h>
#include <interaction.h>
#include <chrono>
#include <sys/stat.h>
#include <sys/types.h>

void update(Particles *particles, float_t dt)
{
    for (size_t i = 0; i < particles->N; i++)
    {
        particles->T[i] += particles->T_t[i] * dt;
    }
}

void initialize_particles(Particles *particles, int nx, int ny, int nz, float_t dx, float_t dy, float_t dz, float_t hf)
{
    float_t thermal_cp = 850.; // units: gmms
    float_t thermal_k = 157.;
    float_t rho = 2830.; // units: gmms
    float_t mass = 2830. * dx * dy * dz;
    float_t h = hf * dx;
    float_t T = 20.;
    float_t T_boundary = 500.;

    std::vector<float3_t> pos_vec;
    std::vector<float_t> T_vec;
    std::vector<float_t> cp_vec;
    std::vector<float_t> k_vec;
    std::vector<float_t> rho_vec;
    std::vector<float_t> h_vec;
    std::vector<float_t> mass_vec;

    for (size_t i = 0; i < nx; i++)
    {
        for (size_t j = 0; j < ny; j++)
        {
            for (size_t k = 0; k < nz; k++)
            {
                pos_vec.push_back(make_float3_t(i * dx, j * dx, k * dx));
                cp_vec.push_back(thermal_cp);
                k_vec.push_back(thermal_k);
                rho_vec.push_back(rho);
                mass_vec.push_back(mass);
                h_vec.push_back(h);
                T_vec.push_back(i == 0 ? T_boundary : T);
            }
        }
    }

    particles->set_properties(pos_vec, T_vec, cp_vec, k_vec, rho_vec, h_vec, mass_vec);
}

void run_simulation(Particles *particles, float_t total_time, float_t dt)
{
    float_t percent_increment = 0.01;
    float_t next_percent = percent_increment;
    unsigned int step = 0;

    vtk_writer_write(particles, step);

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

    // make results directoy if not present
    struct stat st = {0};
    if (stat("../results", &st) == -1)
    {
        mkdir("../results", 0777);
    }
    // clear files from result directory
    int ret;
    ret = system("rm ../results/*.vtk");

    // Domain size
    float_t lx = 0.1;
    float_t ly = 0.1;
    float_t lz = 0.1;
    // Space between particles
    float_t dx = .005;
    float_t dy = dx;
    float_t dz = dx;
    // number of particles in each direction
    int nx = lx / dx;
    int ny = ly / dy;
    int nz = lz / dz;
    // total number of particles
    int N = nx * ny * nz;
    // smoothing length factor
    float_t hf = 1.2;

    Particles *particles = new Particles(N);

    initialize_particles(particles, nx, ny, nz, dx, dy, dz, hf);

    float_t total_time = 10;
    float_t dt = 0.01;

    auto start_time = std::chrono::high_resolution_clock::now();

    run_simulation(particles, total_time, dt);

    auto end_time = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::seconds>(end_time - start_time);

    std::cout << "Simulation time:" << total_time << " seconds" << std::endl;
    std::cout << "Time step:" << dt << " seconds" << std::endl;
    std::cout << "Time used: " << duration.count() << " seconds" << std::endl;

    delete particles;
    return 0;
}