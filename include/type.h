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

#ifndef TYPES_H_
#define TYPES_H_

#include <stdio.h>
#include <glm/glm.hpp>

#define USE_DOUBLE

#ifdef USE_DOUBLE
// built-in vector types
#define float_t double
#define float2_t glm::dvec2
#define float3_t glm::dvec3
#define float4_t glm::dvec4

#define make_float2_t glm::dvec2
#define make_float3_t glm::dvec3
#define make_float4_t glm::dvec4

// mathematical functions
#define sqrt_t sqrt
#define exp_t exp
#define log_t log

#else

// built-in vector types
#define float_t float
#define float2_t glm::vec2
#define float3_t glm::vec3
#define float4_t glm::vec4

#define make_float2_t glm::vec2
#define make_float3_t glm::vec3
#define make_float4_t glm::vec4

// mathematical functions
#define sqrt_t sqrtf
#define exp_t expf
#define log_t logf
#endif

#endif /* TYPES_H_ */