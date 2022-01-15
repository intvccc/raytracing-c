#ifndef _SCENE_H_
#define _SCENE_H_

#include "camera.h"
#include "ray_tracing_light.h"
#include "ray_tracing_primitive.h"

typedef struct {
	camera_type* 				camera;
	traceable_object_type* 		traceable_object;
	light_type* 				light;
	size_t 						traceable_object_count;
	size_t 						light_count;
} scene_type;

#endif
