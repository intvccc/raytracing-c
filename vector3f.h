#ifndef _VECTOR3F_H_
#define _VECTOR3F_H_

#include <math.h>

#define USE_QUICK_SQRT

#define EPSILON 1e-4

typedef struct {
	float x, y, z;
} v3f;

static inline v3f v3f_create(const float x, const float y, const float z)
{
	v3f result = {
		.x = x, .y = y, .z = z
	};	
	return result;
}

static inline v3f v3f_add(const v3f v1, const v3f v2)
{
	return v3f_create(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);
}

static inline v3f v3f_neg(const v3f v)
{
	return v3f_create(-v.x, -v.y, -v.z);
}

static inline v3f v3f_mul(const v3f v1, const v3f v2)
{
	return v3f_create(v1.x * v2.x, v1.y * v2.y, v1.z * v2.z);
}

static inline v3f v3f_scale(const v3f v, const float scale)
{
	return v3f_create(v.x * scale, v.y * scale, v.z * scale);
}

static inline v3f v3f_sub(const v3f v1, const v3f v2)
{
	return v3f_create(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
}

static inline float v3f_dot_prod(const v3f v1, const v3f v2)
{
	return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

static inline v3f v3f_cross_prod(const v3f v1, const v3f v2)
{
	return v3f_create(v1.y * v2.z - v1.z * v2.y,
					  v1.z * v2.x - v1.x * v2.z,
					  v1.x * v2.y - v1.y * v2.x);
}

static inline float v3f_norm_sq(const v3f v)
{
	return v3f_dot_prod(v, v);
}

static inline float v3f_norm(const v3f v)
{
	return sqrtf(v3f_norm_sq(v));
}

static inline void v3f_normalize(v3f* v)
{
	float norm = v3f_norm(*v);
	v->x /= norm;
	v->y /= norm;
	v->z /= norm;
}

static inline v3f v3f_direction(const v3f v)
{
	return v3f_scale(v, 1.0f / v3f_norm(v));
}

#endif
