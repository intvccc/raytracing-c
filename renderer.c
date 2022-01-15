#include "renderer.h"

void renderer(void)
{
	const size_t scene_traceable_object_count = 3;
	const size_t scene_light_count = 3;
	const size_t screen_size_x = BITMAP_WIDTH;
	const size_t screen_size_y = BITMAP_HEIGHT;
	scene_type scene;
	
	scene.light_count = scene_light_count;
	scene.traceable_object_count = scene_traceable_object_count;
	
	camera_type scene_camera = camera_create(v3f_create(0.0f, 2.0f, 0.0f),
							    			 v3f_create(0.0f, 0.0f, -1.0f),
							    			 v3f_create(0.0f, 1.0f, 0.0f),
							    			 FOCAL_LENGTH);
	scene.camera = &scene_camera;
	
	sphere_primitive_type sp1 = sphere_create(v3f_create(-5.0f, 0.0f, -15.0f), 5.0f);
	sphere_primitive_type sp2 = sphere_create(v3f_create(5.0f, -0.5f, -15.0f), 4.0f);			
	plane_primitive_type p = plane_create(v3f_create(0.0f, -5.0f, 0.0f), v3f_create(0.0f, 1.0f, 0.0f));						
	scene.traceable_object = (traceable_object_type*) malloc(scene_traceable_object_count * sizeof(traceable_object_type));
	scene.traceable_object[0] = traceable_object_create(material_create(v3f_create(1.0f, 1.0f, 1.0f),
																		v3f_create(0.0f, 0.78f, 1.0f),
																		v3f_create(1.0f, 1.0f, 1.0f),
																		v3f_create(0.5f, 0.5f, 0.5f)),
														&sp1,
														ray_sphere_hit);
														
	scene.traceable_object[1] = traceable_object_create(material_create(v3f_create(1.0f, 1.0f, 1.0f),
																		v3f_create(1.0f, 0.0f, 0.68f),
																		v3f_create(1.0f, 1.0f, 1.0f),
																		v3f_create(0.5f, 0.5f, 0.5f)),
														&sp2,
														ray_sphere_hit);													
	
	scene.traceable_object[2] = traceable_object_create(material_create(v3f_create(1.0f, 1.0f, 1.0f),
																		v3f_create(0.2f, 0.2f, 0.2f),
																		v3f_create(1.0f, 1.0f, 1.0f),
																		v3f_create(0.0f, 0.0f, 0.0f)),
														&p,
														ray_plane_hit);
													
	scene.light = (light_type*) malloc(scene_light_count * sizeof(light_type));
	scene.light[0] = point_light_create(v3f_create(-30.0f, 20.0f, 0.0f),
										v3f_create(1.0f, 1.0f, 1.0f),
										0.0025f);
	scene.light[1] = point_light_create(v3f_create(40.0f, 10.0f, 0.0f),
										v3f_create(1.0f, 1.0f, 1.0f),
										0.0025f);
	scene.light[2] = point_light_create(v3f_create(0.0f, 15.0f, -35.0f),
										v3f_create(1.0f, 1.0f, 1.0f),
										0.0015f);
									
	frame_buffer_type frame_buffer;
	frame_buffer_init(&frame_buffer, BITMAP_PIXEL_COUNT);
									
	ray_tracing_worker_args args = {
		.scene = &scene,
		.render_start_row = 0,
		.render_row_count = screen_size_y,
		.screen_size_x = screen_size_x,
		.screen_size_y = screen_size_y,
		.frame_buffer = frame_buffer
	};
	
	ray_tracing_worker(&args);

	assert((bmp_write(frame_buffer.memory, BITMAP_WIDTH, BITMAP_HEIGHT, "out.bmp")) 
		&& "ERROR: Create BMP file failed.\n");

																						
	free(scene.traceable_object);
	free(scene.light);
	frame_buffer_destory(&frame_buffer);
} 

scene_type scene_create(camera_type* camera, traceable_object_type* traceable_object, light_type* light, size_t traceable_object_count, size_t light_count)
{
	scene_type result = {
		.camera = camera,
		.traceable_object = traceable_object,
		.light = light,
		.traceable_object_count = traceable_object_count,
		.light_count = light_count
	};
	return result;
}
