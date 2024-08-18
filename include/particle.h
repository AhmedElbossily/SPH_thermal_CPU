
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
