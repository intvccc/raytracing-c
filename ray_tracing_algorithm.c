#include "ray_tracing_algorithm.h"

v3f ray_color(const ray_type* r, const scene_type* s, size_t recursion_counter)
{
	hit_record_type rec;
	bool in_shadow = false;
	v3f color = v3f_create(0.0f, 0.0f, 0.0f);
	size_t object_count = s->traceable_object_count;
	
	if (get_hit_object(r, s, &rec)) {
		for (size_t i = 0; i < s->light_count; ++i) {
			light_type current_light = s->light[i];
			ray_type hit_to_light = ray_create(rec.normal.origin, 
				v3f_direction(v3f_sub(current_light.position, rec.normal.origin)));
				
			for (size_t j = 0; j < object_count; ++j) {
				if ((in_shadow = ray_object_hit(&hit_to_light, &(s->traceable_object[j]), 
					EPSILON, FLT_MAX, NULL))) {
					break;		
				}
			}
			
			if (!in_shadow) 
				color = v3f_add(color, shader(&(rec.material), r, &(rec.normal), &current_light));
		}
		
		if (recursion_counter > 0) {
			ray_type reflect = ray_create(rec.normal.origin, 
										  v3f_sub(r->direction, 
										  v3f_scale(rec.normal.direction, 
										  2.0f * v3f_dot_prod(r->direction, rec.normal.direction))));
			// reflect.origin = v3f_add(reflect.origin, v3f_scale(reflect.direction, EPSILON));
			color = v3f_add(color, v3f_mul(rec.material.reflect, 
				ray_color(&reflect, s, recursion_counter - 1)));	
		}
	}
	return color;
}

bool get_hit_object(const ray_type* r, const scene_type* s, hit_record_type* rec)
{
	bool hit = false;
	float t_max = FLT_MAX;
	const size_t object_count = s->traceable_object_count;
	hit_record_type rec_temp[object_count];
	
	size_t hit_object_index = 0;
	for (size_t i = 0 ; i < object_count; ++i) {
		if (ray_object_hit(r, &(s->traceable_object[i]), EPSILON, t_max, &rec_temp[i])) {			
			hit = true;
			hit_object_index = i;
			t_max = rec_temp[i].t; 			
		}		
	}
	
	if (hit)
		*rec = rec_temp[hit_object_index];
		
	return hit;
}

bool ray_sphere_hit(const ray_type* r, const traceable_object_type* obj, const float t_min, const float t_max, hit_record_type* rec) 
{
	sphere_primitive_type* sph = obj->primitive_object;
	v3f center_to_eye = v3f_sub(r->origin, sph->center);		
	float temp = v3f_dot_prod(r->direction, center_to_eye);	
	float discriminant = temp * temp 
		- (v3f_norm_sq(center_to_eye) - sph->radius * sph->radius);

	if (discriminant < 0.0f) 
		return false;
		
	float t = - v3f_dot_prod(r->direction, center_to_eye) - sqrtf(discriminant);
	
	if ((t < t_min) | (t > t_max))
		return false;
		
	if (rec == NULL)
		return true;
		
	v3f hit_point = v3f_add(r->origin, v3f_scale(r->direction, t));
	rec->normal.origin = hit_point;
	rec->normal.direction = v3f_scale(v3f_sub(hit_point, sph->center), 1.0f / sph->radius);
	rec->t = t;	
	rec->material = obj->material;	
	return true;
}

bool ray_plane_hit(const ray_type* r, const traceable_object_type* obj, const float t_min, const float t_max, hit_record_type* rec)
{
	plane_primitive_type* p = obj->primitive_object;
	float den = v3f_dot_prod(r->direction, p->normal);
	
	if (fabsf(den) < EPSILON)
		return false;
		
	float num = v3f_dot_prod(p->normal, v3f_sub(p->center, r->origin));
	float t = num / den;
	
	if ((t < t_min) | (t > t_max))
		return false;
		
	if (rec == NULL)
		return true;
		
	rec->normal.direction = p->normal;
	rec->normal.origin = v3f_add(r->origin, v3f_scale(r->direction, t));
	rec->t = t;
	rec->material = obj->material;
	return true;
}

bool ray_aabox_hit(const ray_type* r, const traceable_object_type* obj, const float t_min, const float t_max, hit_record_type* rec)
{	
	return false;
}

