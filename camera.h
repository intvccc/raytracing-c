#ifndef _CAMERA_H_
#define _CAMERA_H_

#include <stdint.h>
#include "vector3f.h"
#include "misc_math.h"
#include "ray_tracing_primitive.h"
#include "options.h"

typedef struct {
	v3f position;
	v3f view_direction;
	v3f upward_direction;	
	float focal_length;
} camera_type;

static inline camera_type camera_create(v3f position, v3f view_direction, v3f upward_direction, float focal_length)
{
	camera_type result = {
		.position = position, 
		.view_direction = view_direction,
		.upward_direction = upward_direction,
		.focal_length = focal_length
	};
	return result;
}

ray_type compute_view_ray(camera_type*, size_t, size_t, int64_t, int64_t);

#endif
