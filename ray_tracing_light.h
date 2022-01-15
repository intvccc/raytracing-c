#ifndef _RAY_TRACING_LIGHT_H_
#define _RAY_TRACING_LIGHT_H_

#include <stdint.h>
#include "vector3f.h"
/*
typedef struct {
	void* light_object;
} light_type;
*/
typedef struct {
	v3f position;
	v3f intensity;
	float attenuation;
} light_type;

/*
typedef struct {
	
} spot_light_type;

typedef struct {

} directional_light_type;
*/

/*
typedef struct {
	
} plane_light_type;
*/

static inline light_type point_light_create(v3f position, v3f intensity, float attenuation)
{
	light_type result = {
		.position = position, 
		.intensity = intensity,
		.attenuation = attenuation
	};
	return result;
}

#endif
