#ifndef _RENDERER_H_
#define _RENDERER_H_

#include <assert.h>
#include <stdint.h>
#include <stdlib.h>
#include "scene.h" 
#include "frame_buffer.h"
#include "ray_tracing_algorithm.h"
#include "ray_tracing_worker.h" 
#include "ray_tracing_primitive.h"
#include "ray_tracing_light.h"
#include "camera.h"
#include "options.h"
#include "bmp.h"

void renderer(void);

scene_type scene_create(camera_type*, traceable_object_type*, light_type*, size_t, size_t);

#endif

