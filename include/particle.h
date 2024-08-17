
#ifndef PARTICLE
#define PARTICLE

#include "type.h"
#include <vector>

struct Particles
{

	// position

	float3_t *pos = 0;

	// smoothing length, density, ..etc
	float_t *h = 0;
	float_t *rho = 0;
	float_t *mass = 0;
	float_t *cp;
	float_t *k;

	// thermal state
	float_t *T = 0;

	// temporal ders
	float_t *T_t = 0;

	// count on host
	unsigned int N;

	Particles(unsigned int N);
	~Particles();
	void set_properties(std::vector<float3_t> pos_vec, std::vector<float_t> T_vec, std::vector<float_t> cp_vec, std::vector<float_t> k_vec, std::vector<float_t> rho_vec, std::vector<float_t> h_vec, std::vector<float_t> mass_vec);
};

#endif /* PARTICLE */
