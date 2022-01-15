#ifndef _QUATERNION_H_
#define _QUATERNION_H_

#include <math.h>
#include <stdio.h>
#include "vector3f.h"

typedef struct {
	float s;
	v3f v;
} q4f;

static inline q4f q4f_create(float s, v3f v)
{
	q4f result = {
		.s = s,
		.v = v
	};
	
	return result;
}

static inline q4f q4f_scale(q4f q, float scale)
{
	return q4f_create(q.s * scale, v3f_scale(q.v, scale));
}

static inline q4f q4f_add(q4f q1, q4f q2)
{
	return q4f_create(q1.s + q2.s, v3f_add(q1.v, q2.v));
}

static inline q4f q4f_sub(q4f q1, q4f q2)
{
	return q4f_create(q1.s - q2.s, v3f_sub(q1.v, q2.v));
}

static inline q4f q4f_mul(q4f q1, q4f q2)
{	
	return q4f_create(q1.s * q2.s - v3f_dot_prod(q1.v, q2.v), 
		v3f_add(v3f_add(v3f_scale(q1.v, q2.s), v3f_scale(q2.v, q1.s)), v3f_cross_prod(q1.v, q2.v)));
}

static inline q4f q4f_conj(q4f q)
{
	return q4f_create(q.s, v3f_scale(q.v, -1.0f));
}

static inline float q4f_dot_prod(q4f q1, q4f q2)
{
	return q1.s * q2.s + v3f_dot_prod(q1.v, q2.v);
}

static inline float q4f_norm(q4f q)
{
	return sqrtf(q4f_dot_prod(q, q));
}

static inline void q4f_normalize(q4f *q)
{
	float norm = q4f_norm(*q);
	
	q->s /= norm;
	q->v.x /= norm;
	q->v.y /= norm;
	q->v.z /= norm;
}

static inline q4f q4f_inv(q4f q)
{
	return q4f_scale(q4f_conj(q), 1.0f / q4f_dot_prod(q, q));
}

static inline q4f q4f_rotor(float theta, v3f axis)
{
	return q4f_create(cosf(theta / 2.0f), v3f_scale(axis, sinf(theta / 2.0f))); 
}

static inline v3f v3f_rotate(v3f v, q4f rotor)
{
	return q4f_mul(rotor, q4f_mul(q4f_create(0.0f, v), q4f_inv(rotor))).v;
}

#endif
