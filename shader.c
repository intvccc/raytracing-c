#include "shader.h"

v3f shader(const material_type* material, const ray_type* incident, const ray_type* normal, const light_type* pl)
{
	v3f normal_to_light = v3f_sub(pl->position, normal->origin);
	float light_distance_sq = v3f_norm_sq(normal_to_light);
	normal_to_light = v3f_direction(normal_to_light);
	v3f half = v3f_direction(v3f_add(v3f_neg(incident->direction), normal_to_light));
	float illuminance = 1.0f / (light_distance_sq * pl->attenuation);
	float diffuse_factor = MAX(0.0f, v3f_dot_prod(normal->direction, normal_to_light));
	float specular_factor = powf(MAX(0.0f, v3f_dot_prod(normal->direction, half)), 1000.0f);
	v3f diffuse_color = v3f_scale(v3f_mul(pl->intensity, material->diffuse), diffuse_factor * illuminance);
	v3f specular_color = v3f_scale(v3f_mul(pl->intensity, material->specular), specular_factor * illuminance);
	v3f color = v3f_add(diffuse_color, specular_color);
	return color;
	
	//return v3f_create(1.0f, 1.0f, 1.0f); 
}
