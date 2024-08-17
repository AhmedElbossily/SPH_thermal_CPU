
#ifndef PARTICLE
#define PARTICLE

#include "type.h"
#include <vector>

struct Particles
{

	// position, velocity and velocity at boundary condition

	float3_t *pos = 0;
	float3_t *vel = 0;
	float3_t *vel_bc = 0;

	// smoothing length, density, pressure
	float_t *h = 0;
	float_t *rho = 0;
	float_t *mass = 0;
	float_t *p = 0;

	// deviatoric stress state, artificial stress
	mat3x3_t *S = 0;
	mat3x3_t *R = 0;

	// contact forces, friction forces and normals at contact
	float3_t *fc = 0;
	float3_t *ft = 0;
	float3_t *n = 0;

	// flags
	float_t *fixed = 0;	  // particle is fixed in space
	float_t *blanked = 0; // particle is deactivated

	// plastic state (equivalent)
	float_t *eps_pl;
	float_t *eps_pl_dot;

	// thermal state
	float_t *T = 0;

	// temporal ders
	float3_t *pos_t = 0;
	float3_t *vel_t = 0;
	float_t *rho_t = 0;
	mat3x3_t *S_t = 0;
	float_t *T_t = 0;

	// spatial ders
	mat3x3_t *S_der = 0;
	mat3x3_t *v_der = 0;

	// debug
	int *num_nbh = 0;

	// hashing
	int *idx = 0;  // unsigned int should be avoided on gpu
	int *hash = 0; //		see best practices guide

	// count on host (!)
	unsigned int N;

	float_t *cp;
	float_t *k;

	Particles(unsigned int N);
	~Particles();
	void set_properties(std::vector<float3_t> pos_vec, std::vector<float_t> T_vec, std::vector<float_t> cp_vec, std::vector<float_t> k_vec, std::vector<float_t> rho_vec, std::vector<float_t> h_vec, std::vector<float_t> mass_vec);
};

#endif /* PARTICLE */
