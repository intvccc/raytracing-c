#ifndef _RAY_TRACING_PRIMITIVE_H_
#define _RAY_TRACING_PRIMITIVE_H_

#include <stdbool.h>
#include "vector3f.h"

typedef struct {
	v3f origin;
	v3f direction;	// Must be unit vector
} ray_type;

typedef struct {
	v3f ambient; 
	v3f diffuse;
	v3f specular;
	v3f reflect;
} material_type;

typedef struct {
	ray_type normal;
	float t;
	material_type material;
	// v2f tex_coord;
} hit_record_type;

struct traceable_object_type_;
typedef bool (*hit_function_type)(const ray_type*, const struct traceable_object_type_*, float, float, hit_record_type*);

typedef struct traceable_object_type_{
	material_type material;
	void* primitive_object;
	hit_function_type hit_function;
} traceable_object_type;

typedef struct {
	v3f center;
	float radius;
} sphere_primitive_type;

typedef struct {
	v3f center;
	v3f normal;
} plane_primitive_type;

typedef struct {	// Axis aligned box, vertex1.x < vertex2.x, ..., vertex1.z < vertex2.z
	v3f vertex1;
	v3f vertex2;
} aabox_primitive_type;

static inline ray_type ray_create(v3f origin, v3f direction)
{
	ray_type result = {
		.origin = origin,
		. direction = direction
	};
	return result;
}

static inline sphere_primitive_type sphere_create(v3f center, float radius)
{
	sphere_primitive_type result = {
		.center = center,
		.radius = radius
	};
	return result;
}

static inline plane_primitive_type plane_create(v3f center, v3f normal)
{
	plane_primitive_type result = {
		.center = center,
		.normal = normal
	};
	return result;
}

static inline traceable_object_type 
traceable_object_create(material_type material, void* primitive_object, hit_function_type hit_function)
{
	traceable_object_type result = {
		.material = material,
		.primitive_object = primitive_object,
		.hit_function = hit_function,
	};
	return result;
}

static inline material_type material_create(v3f ambient, v3f diffuse, v3f specular, v3f reflect)
{
	material_type result = {
		.ambient = ambient,
		.diffuse = diffuse,
		.specular = specular,
		.reflect = reflect
	};
	return result;
}

#endif
