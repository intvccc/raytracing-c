#ifndef _RAY_TRACING_WORKER_H_
#define _RAY_TRACING_WORKER_H_

#include "camera.h"
#include "ray_tracing_light.h"
#include "ray_tracing_algorithm.h"
#include "scene.h"
#include "frame_buffer.h"

typedef struct {
	scene_type*					scene;
	size_t 						render_start_row;
	size_t 						render_row_count;
	size_t 						screen_size_x;
	size_t 						screen_size_y;
	frame_buffer_type			frame_buffer;
} ray_tracing_worker_args;

void* ray_tracing_worker(const ray_tracing_worker_args*);

#endif

