#ifndef _FRAME_BUFFER_H_
#define _FRAME_BUFFER_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "vector3f.h"

typedef struct {
	v3f*	memory;
	size_t	size;
} frame_buffer_type;

static inline void frame_buffer_write(frame_buffer_type fb, v3f color, size_t index)
{
	fb.memory[index] = color;
}

int frame_buffer_init(frame_buffer_type* fb, size_t element_count);
void frame_buffer_destory(frame_buffer_type* fb);

#endif

