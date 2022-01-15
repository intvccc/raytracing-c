#ifndef _RAY_TRACING_ALGORITHM_H_
#define _RAY_TRACING_ALGORITHM_H_

#include <float.h>
#include "shader.h"
#include "camera.h"
#include "scene.h"
#include "frame_buffer.h"
#include "ray_tracing_primitive.h"
#include "ray_tracing_light.h"

static inline bool ray_object_hit(const ray_type* r, const traceable_object_type* o, float t_min, float t_max, hit_record_type* rec)
{
	return o->hit_function(r, o, t_min, t_max, rec);
}

bool get_hit_object(const ray_type*, const scene_type*, hit_record_type*);
v3f ray_color(const ray_type* r, const scene_type* s, size_t recursion_counter);

bool ray_sphere_hit(const ray_type*, const traceable_object_type*, const float, const float, hit_record_type*);
bool ray_plane_hit(const ray_type*, const traceable_object_type*, const float, const float, hit_record_type*);

#endif
