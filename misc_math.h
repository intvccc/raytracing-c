#ifndef _MISC_MATH_H_
#define _MISC_MATH_H_

#include "vector3f.h"

#define MAX(a,b) ((a>b)?a:b)
#define MIN(a,b) ((a<b)?a:b)

static inline float lmapf(float t, float domain_min, float domain_max, float range_min, float range_max)
{
	return range_min + (t - domain_min) * (range_max - range_min) / (domain_max - domain_min);
}

static inline float lerpf(float t, float domain_min, float domain_max)
{
	return t * domain_min + (1 - t) * domain_max;
}

static inline float clampf(float t, float domain_min, float domain_max)
{
	const float temp = t < domain_min ? domain_min : t;
	return temp > domain_max ? domain_max : temp;
}

// Object frame u, v, w (in x, y, z) with origin (translation) e (in x, y, z) and object coord p (in u, v, w)
static inline v3f object_world_transform(v3f u_xyz, v3f v_xyz, v3f w_xyz, v3f e_xyz, v3f p_uvw)
{
	return v3f_create(u_xyz.x * p_uvw.x + v_xyz.x * p_uvw.y + w_xyz.x * p_uvw.z + e_xyz.x,
					  u_xyz.y * p_uvw.x + v_xyz.y * p_uvw.y + w_xyz.y * p_uvw.z + e_xyz.y,
					  u_xyz.z * p_uvw.x + v_xyz.z * p_uvw.y + w_xyz.z * p_uvw.z + e_xyz.z);
}

#endif
