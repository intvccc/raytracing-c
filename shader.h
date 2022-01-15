#ifndef _SHADER_H_
#define _SHADER_H_

#include "options.h"
#include "misc_math.h"
#include "ray_tracing_primitive.h"
#include "ray_tracing_light.h"

v3f shader(const material_type*, const ray_type*, const ray_type*, const light_type*);

#endif
