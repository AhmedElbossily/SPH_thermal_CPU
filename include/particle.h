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

#ifndef PARTICLE
#define PARTICLE

#include "type.h"
#include <vector>

struct Particles
{
	// position of particles in 3D x,y,z
	float3_t *pos = 0;
	float_t *T = 0;	   // current temperature
	float_t *k;		   // thermal conductivity
	float_t *rho = 0;  // density of particles
	float_t *mass = 0; // mass of particles
	float_t *cp;	   // specific heat capacity
	float_t *h = 0;	   // smoothing length
	float_t *T_t = 0;  // time derivative of temperature
	unsigned int N;	   // count number of patricles

	// class constructor and destructor
	Particles(unsigned int N);
	~Particles();
	// set properties of particles
	void set_properties(std::vector<float3_t> pos_vec, std::vector<float_t> T_vec,
						std::vector<float_t> cp_vec, std::vector<float_t> k_vec,
						std::vector<float_t> rho_vec, std::vector<float_t> h_vec,
						std::vector<float_t> mass_vec);
};

#endif /* PARTICLE */
