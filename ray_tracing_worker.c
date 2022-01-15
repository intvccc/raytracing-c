#include "ray_tracing_worker.h"

void* ray_tracing_worker(const ray_tracing_worker_args* args)
{
	size_t frame_buffer_index = args->render_start_row * (args->screen_size_x + 1);
	for (size_t i = args->render_start_row; 
		i < args->render_start_row + args->render_row_count; ++i) {
		for (size_t j = 0; j < args->screen_size_x; ++j) {
			ray_type view_ray = compute_view_ray(args->scene->camera, args->screen_size_x, 
				args->screen_size_y, j, i);
			v3f color = ray_color(&view_ray, args->scene, MAX_REFLECT_COUNT);
			//v3f color = v3f_create(0.0f, 1.0f, 0.0f);
			frame_buffer_write(args->frame_buffer, color, frame_buffer_index++);
		}
	}
	return NULL;
}
