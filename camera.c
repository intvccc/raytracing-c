#include "camera.h"

ray_type compute_view_ray(camera_type* cam, size_t screen_size_x, size_t screen_size_y, int64_t pixel_index_x, int64_t pixel_index_y)
{
	int64_t pixel_coord_x = pixel_index_x - screen_size_x / 2;
	int64_t pixel_coord_y = pixel_index_y - screen_size_y / 2;	
	
	v3f camera_w_axis = v3f_scale(cam->view_direction, -1.0f);
	v3f camera_u_axis = v3f_cross_prod(cam->upward_direction, camera_w_axis);
	
	ray_type view_ray;
	view_ray.origin = cam->position;
	view_ray.direction = v3f_direction(v3f_create(pixel_coord_x * PIXEL_SIZE, 
												  pixel_coord_y * PIXEL_SIZE, 
												  -cam->focal_length));
								   
	view_ray.direction = object_world_transform(camera_u_axis, 
												cam->upward_direction, 
												camera_w_axis,
												v3f_create(0.0f, 0.0f, 0.0f), 
												view_ray.direction);	
	return view_ray;
}


